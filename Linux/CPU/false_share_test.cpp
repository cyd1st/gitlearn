#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

const int NUM_THREADS = 2;
const long long ITERATIONS = 1'000'000'00;

// 正确模拟虚假共享
void test_false_sharing()
{
    struct Data {
        std::atomic<int> x{0}; // 使用atomic避免编译器过度优化
        std::atomic<int> y{0};
    } data;

    std::vector<std::thread> threads;
    threads.reserve(NUM_THREADS);

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back([&data, i] {
            // 分支移出循环外
            if (i % 2 == 0) {
                for (long long j = 0; j < ITERATIONS; ++j) {
                    data.x.fetch_add(1, std::memory_order_relaxed);
                }
            } else {
                for (long long j = 0; j < ITERATIONS; ++j) {
                    data.y.fetch_add(1, std::memory_order_relaxed);
                }
            }
        });
    }

    for (auto &t : threads)
        t.join();

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "False sharing: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms (x=" << data.x << ", y=" << data.y << ")\n";
}

// 正确的缓存行对齐
void test_aligned()
{
    struct alignas(64) Data {
        std::atomic<int> x{0};
        char padding[64 - sizeof(std::atomic<int>)];
        std::atomic<int> y{0};
    } data;

    std::vector<std::thread> threads;
    threads.reserve(NUM_THREADS);

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back([&data, i] {
            if (i % 2 == 0) {
                for (long long j = 0; j < ITERATIONS; ++j) {
                    data.x.fetch_add(1, std::memory_order_relaxed);
                }
            } else {
                for (long long j = 0; j < ITERATIONS; ++j) {
                    data.y.fetch_add(1, std::memory_order_relaxed);
                }
            }
        });
    }

    for (auto &t : threads)
        t.join();

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Cache aligned: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms (x=" << data.x << ", y=" << data.y << ")\n";
}

int main()
{
    // 多次测试消除冷启动影响
    for (int i = 0; i < 5; i++) {
        test_false_sharing();
        test_aligned();
        std::cout << "-------------------\n";
    }
    return 0;
}