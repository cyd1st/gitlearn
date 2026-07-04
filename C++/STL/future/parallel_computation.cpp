#include <chrono> // 添加时间测量头文件
#include <future>
#include <iostream>
#include <numeric>
#include <vector>

const int DATA_SIZE = 1'000'000'000;
const int NUM_THREADS = 4;

long long calculateSum(const std::vector<long long> &data, size_t start, size_t end)
{
    long long sum = 0;
    for (size_t i = start; i < end; ++i) {
        sum += data[i];
    }
    return sum;
}

int main()
{
    std::vector<long long> data(DATA_SIZE);
    std::iota(data.begin(), data.end(), 1LL);

    // 单线程计算
    auto start_single = std::chrono::high_resolution_clock::now();
    long long single_sum = calculateSum(data, 0, DATA_SIZE);
    auto end_single = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_single = end_single - start_single;

    // 多线程计算
    std::vector<std::future<long long>> futures;
    size_t chunk_size = DATA_SIZE / NUM_THREADS;
    auto start_multi = std::chrono::high_resolution_clock::now(); // 多线程开始时间

    for (int i = 0; i < NUM_THREADS; ++i) {
        size_t start = i * chunk_size;
        size_t end = (i == NUM_THREADS - 1) ? DATA_SIZE : start + chunk_size;

        futures.push_back(std::async([=, &data]() { return calculateSum(data, start, end); }));
    }

    long long total = 0;
    for (auto &future : futures) {
        total += future.get();
    }

    auto end_multi = std::chrono::high_resolution_clock::now(); // 多线程结束时间
    std::chrono::duration<double> duration_multi = end_multi - start_multi;

    // 输出结果对比
    std::cout << "Single thread sum: " << single_sum << " (" << duration_single.count() << "s)"
              << std::endl;
    std::cout << "Multi thread sum: " << total << " (" << duration_multi.count() << "s)"
              << std::endl;
    std::cout << "Speedup: " << duration_single.count() / duration_multi.count() << "x"
              << std::endl;

    return 0;
}