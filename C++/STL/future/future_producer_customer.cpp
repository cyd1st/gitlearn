// 基于 future 的生产者消费者模型示例demo
#include <future>
#include <iostream>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>

std::queue<int> data_queue;
std::mutex mtx;
std::condition_variable cv;

void producer(int id, int num_items) {
    for (int i = 0; i < num_items; ++i) {
        std::lock_guard<std::mutex> lock(mtx);
        data_queue.push(i);
        std::cout << "Producer " << id << " produced " << i << std::endl;
        cv.notify_one();
    }
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, []{ return !data_queue.empty(); });
        int data = data_queue.front();
        data_queue.pop();
        lock.unlock();
        
        if (data == -1) break; // 停止信号
        
        std::cout << "Consumer processed " << data << std::endl;
    }
}

int main() {
    std::vector<std::future<void>> producers;
    
    // 启动生产者
    for (int i = 0; i < 3; ++i) {
        producers.push_back(std::async(std::launch::async, producer, i, 5));
    }
    
    // 启动消费者
    std::future<void> consumer_future = std::async(std::launch::async, consumer);
    
    // 等待所有生产者完成
    for (auto& f : producers) {
        f.wait();
    }
    
    // 发送停止信号
    {
        std::lock_guard<std::mutex> lock(mtx);
        data_queue.push(-1);
        cv.notify_one();
    }
    
    consumer_future.wait();
    return 0;
}