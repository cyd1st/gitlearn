#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <atomic>
#include <iomanip>
#include <algorithm>
#include <numeric>

// 使用互斥锁的计数器类
class MutexCounter {
private:
    mutable std::mutex mtx_;
    long long count_;

public:
    MutexCounter() : count_(0) {}

    void increment() {
        std::lock_guard<std::mutex> lock(mtx_);
        ++count_;
    }

    long long getCount() const {
        std::lock_guard<std::mutex> lock(mtx_);
        return count_;
    }
    
    void reset() {
        std::lock_guard<std::mutex> lock(mtx_);
        count_ = 0;
    }
};

// 使用原子操作的无锁计数器类
class AtomicCounter {
private:
    std::atomic<long long> count_;

public:
    AtomicCounter() : count_(0) {}

    void increment() {
        ++count_;
    }

    long long getCount() const {
        return count_.load();
    }
    
    void reset() {
        count_.store(0);
    }
};

// 测试模板函数
template<typename CounterType>
long long runBenchmark(CounterType& counter, int numThreads, int incrementsPerThread) {
    auto startTime = std::chrono::high_resolution_clock::now();
    
    std::vector<std::thread> threads;
    threads.reserve(numThreads);
    
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back([&counter, incrementsPerThread]() {
            for (int j = 0; j < incrementsPerThread; ++j) {
                counter.increment();
            }
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    
    return duration.count();
}

template<typename CounterType>
long long benchmarkMultipleRuns(CounterType& counter, const std::string& testName, 
                               int numRuns, int numThreads, int incrementsPerThread) {
    std::vector<long long> durations(numRuns);
    
    for (int i = 0; i < numRuns; ++i) {
        counter.reset();
        durations[i] = runBenchmark(counter, numThreads, incrementsPerThread);
    }
    
    std::sort(durations.begin(), durations.end());
    
    long long sum = std::accumulate(durations.begin(), durations.end(), 0LL);
    long long average = sum / numRuns;
    long long median = durations[numRuns/2];
    
    std::cout << std::setw(15) << std::left << testName << ": " 
              << "Avg: " << std::setw(8) << std::right << average << " μs, "
              << "Med: " << std::setw(8) << std::right << median << " μs"
              << " [Min: " << std::setw(6) << std::left << durations[0] << "μs, "
              << "Max: " << std::setw(6) << std::left << durations.back() << "μs]"
              << std::endl;
              
    return median;
}

void runBenchmarkSuite(int numThreads, int incrementsPerThread, int numRuns) {
    const int totalIncrements = numThreads * incrementsPerThread;
    
    std::cout << "\n=== Benchmark with " << numThreads << " threads ===" << std::endl;
    std::cout << "Each thread performs " << incrementsPerThread 
              << " increments (" << totalIncrements << " total)" << std::endl;
    std::cout << std::string(70, '-') << std::endl;
    
    // 测试互斥锁计数器
    MutexCounter mutexCounter;
    long long mutexMedian = benchmarkMultipleRuns(mutexCounter, "Mutex Counter", 
                                                  numRuns, numThreads, incrementsPerThread);
    
    // 测试原子计数器
    AtomicCounter atomicCounter;
    long long atomicMedian = benchmarkMultipleRuns(atomicCounter, "Atomic Counter", 
                                                   numRuns, numThreads, incrementsPerThread);
    
    double speedup = (double)mutexMedian / atomicMedian;
    
    std::cout << std::string(70, '-') << std::endl;
    std::cout << "Atomic counter is " << std::fixed << std::setprecision(2) 
              << speedup << "x faster than mutex counter (median values)" << std::endl;
}

int main() {
    const int incrementsPerThread = 100000;
    const int numRuns = 10;
    
    std::cout << "Counter Performance Benchmark" << std::endl;
    std::cout << "============================" << std::endl;
    
    // 在不同的线程数量下进行测试
    std::vector<int> threadCounts = {1, 2, 4, 8, 16};
    
    for (int numThreads : threadCounts) {
        runBenchmarkSuite(numThreads, incrementsPerThread, numRuns);
    }
    
    std::cout << "\n=== Summary ===" << std::endl;
    std::cout << "As the number of threads increases, contention for the mutex increases," << std::endl;
    std::cout << "making the atomic counter increasingly more advantageous." << std::endl;
        
    return 0;
}