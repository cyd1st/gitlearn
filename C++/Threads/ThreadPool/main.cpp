#include <chrono>
#include <iostream>
#include <mutex>
#include "thread_pool.h"

std::mutex cout_mtx;

int main()
{
    ThreadPool pool(4); // 创建 4 个线程的线程池

    std::vector<std::future<int>> results;

    for (int i = 0; i < 8; ++i) {
        results.emplace_back(pool.submit([i]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            {
                std::lock_guard<std::mutex> lock(cout_mtx);
                std::cout << "Task " << i << " done by thread " << std::this_thread::get_id()
                          << std::endl;
            }
            return i * i;
        }));
    }

    for (auto &result : results) {
        {
            // std::lock_guard<std::mutex> lock(cout_mtx);
            std::cout << "Result: " << result.get() << std::endl;
        }
    }
    return 0;
}