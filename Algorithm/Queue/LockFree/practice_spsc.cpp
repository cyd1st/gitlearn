#include <atomic>
#include <cstddef>
#include <iostream>
#include <thread>

template <typename T, size_t Size>
class LockFreeQueueSPSC {
    T array[Size];
    std::atomic<size_t> head;
    std::atomic<size_t> tail;

public:
    LockFreeQueueSPSC() : head(0), tail(0) {}

    bool enqueue(T val)
    {
        size_t old_tail = tail.load();
        size_t next_tail = (old_tail + 1) % Size;
        if (next_tail == head.load()) {
            return false;
        }

        // 先赋值再+1，这是单生产单消费的核心，因为在生产者+1之前，消费者获取不到最新数据
        array[old_tail] = val;
        // ++tail; // 错误。环形队列下标不能直接++，--

        // tail.store(next_tail);  // 和下面的 compare_exchange_weak一样

        // SPSC 模型事实上不需要CAS，杀鸡用牛刀。
        if (tail.compare_exchange_weak(old_tail, next_tail)) {
            return true;
        }

        return false;
    }

    bool dequeue(T &result)
    {
        size_t old_head = head.load();
        size_t old_taild = tail.load();

        if (old_head == old_taild) {
            return false;
        }

        result = array[old_head];
        size_t next_head = (old_head + 1) % Size;

        // ++head; // 错误。注意下标不能直接++，--
        // head.store(next_head); // 和下面的 compare_exchange_weak结果一样
        // SPSC 模型事实上不需要CAS，杀鸡用牛刀。
        if (head.compare_exchange_weak(old_head, next_head)) {
            return true;
        }
        return false;
    };
};

// ========== 测试代码 ==========
void producer(LockFreeQueueSPSC<int, 10> &queue)
{
    for (int i = 0; i < 100;) {
        if (queue.enqueue(i)) {
            ++i; // 只有成功才递增！
        }
        // 如果失败（队列满），会重试（忙等待）
    }
}

void consumer(LockFreeQueueSPSC<int, 10> &queue)
{
    int value;
    for (int i = 0; i < 100;) {
        if (queue.dequeue(value)) {
            std::cout << "Got: " << value << std::endl;
            ++i; // 只有成功才递增！
        }
        // 如果失败（队列空），会重试（忙等待）
    }
}

int main()
{
    LockFreeQueueSPSC<int, 10> queue;

    std::thread p(producer, std::ref(queue));
    std::thread c(consumer, std::ref(queue));

    p.join();
    c.join();

    std::cout << "All done!" << std::endl;
    return 0;
}