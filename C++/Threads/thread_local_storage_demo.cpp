#include <iostream>
#include <memory>
#include <thread>
#include <vector>

// 线程局部计数器
thread_local int thread_counter = 0;

// 线程局部缓冲区（避免频繁内存分配）
thread_local std::unique_ptr<std::vector<int>> buffer;

void thread_func()
{
    // 首次访问初始化
    ++thread_counter;
    buffer = std::make_unique<std::vector<int>>(100, 42);
    std::cout << "Thread " << std::this_thread::get_id() << " Counter: " << thread_counter
              << " Buffer size: " << buffer->size() << std::endl;
}

int main()
{
    std::vector<std::thread> threads;
    for (int i = 0; i < 3; ++i) {
        threads.emplace_back(thread_func);
    }
    for (auto &t : threads) {
        t.join();
    }
    // 主线程的thread_counter仍为0（除非显式调用thread_func）
}