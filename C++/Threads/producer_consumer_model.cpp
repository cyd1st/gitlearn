/**
* 生产者-消费者模型的代码示例。
*/
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

std::mutex mtx;
std::condition_variable cv;
std::queue<int> data_queue;
bool done = false;

void consumer() {
    std::unique_lock<std::mutex> lock(mtx);
    while (!done || !data_queue.empty()) {
        cv.wait(lock, []{ return !data_queue.empty() || done; });
        while (!data_queue.empty()) {
            int value = data_queue.front();
            data_queue.pop();
            std::cout << "Consumed: " << value << std::endl;
        }
    }
}

void producer() {
    for (int i = 0; i < 5; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::unique_lock<std::mutex> lock(mtx);
        data_queue.push(i);
        std::cout << "Produced: " << i << std::endl;
        cv.notify_one();
    }
    {
        std::unique_lock<std::mutex> lock(mtx);
        done = true;
    }
    cv.notify_all();
}

int main() {
    std::thread t1(consumer);
    std::thread t2(producer);

    t2.join();
    t1.join();

    return 0;
}