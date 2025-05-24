/*
 * 类似 lock_guard 的线程安全 guard 类。
 */
#ifndef THREAD_GUARD_H
#define THREAD_GUARD_H

#include <thread>

class ThreadGuard {
private:
    std::thread &t;

public:
    // 构造函数，接受一个 std::thread 引用
    explicit ThreadGuard(std::thread &t_) : t(t_) {}

    // 析构函数，自动 join 线程
    ~ThreadGuard()
    {
        if (t.joinable()) {
            t.join();
        }
    }

    // 禁用拷贝构造和赋值运算符
    ThreadGuard(const ThreadGuard &) = delete;
    ThreadGuard &operator=(const ThreadGuard &) = delete;
};

#endif // THREAD_GUARD_H