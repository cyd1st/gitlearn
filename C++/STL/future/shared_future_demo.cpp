#include <chrono>
#include <future>
#include <iostream>
#include <thread>
#include <vector>

// 展示多线程共享访问能力
void threadSharedAccess()
{
    std::promise<int> p;
    std::shared_future<int> sf = p.get_future();

    // 创建多个线程共享访问
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(
            [sf, i]() { std::cout << "Thread " << i << " got value: " << sf.get() << std::endl; });
    }

    p.set_value(12345);
    for (auto &t : threads)
        t.join();
}

// 验证多次获取结果的能力
void multipleGet() {
    std::promise<std::string> p;
    std::shared_future<std::string> sf = p.get_future();

    // 先设置值再获取
    p.set_value("Hello World"); // 提前设置值

    // 在同一线程多次get
    std::cout << "First get: " << sf.get() << std::endl;
    std::cout << "Second get: " << sf.get() << std::endl; // 合法
}

// 演示跨线程同步能力
void crossThreadSync()
{
    std::promise<void> p;
    std::shared_future<void> sf = p.get_future();

    // 多个线程等待同一事件
    std::thread t1([sf]() {
        sf.wait();
        std::cout << "T1 released\n";
    });
    std::thread t2([sf]() {
        sf.wait();
        std::cout << "T2 released\n";
    });

    std::this_thread::sleep_for(std::chrono::seconds(1));
    p.set_value(); // 触发所有等待线程

    t1.join();
    t2.join();
}

// 演示从普通future转换而来
void futureToShared()
{
    std::future<int> f = std::async([] { return 42; });
    std::shared_future<int> sf = f.share();

    // 转换后可多线程访问
    std::thread t1([sf]() { std::cout << "T1: " << sf.get() << std::endl; });
    std::thread t2([sf]() { std::cout << "T2: " << sf.get() << std::endl; });

    t1.join();
    t2.join();
}

int main()
{
    std::cout << "=== 多线程共享访问 ===" << std::endl;
    threadSharedAccess();

    std::cout << "\n=== 多次获取结果 ===" << std::endl;
    multipleGet();

    std::cout << "\n=== 跨线程同步 ===" << std::endl;
    crossThreadSync();

    std::cout << "\n=== 普通future转换 ===" << std::endl;
    futureToShared();

    return 0;
}