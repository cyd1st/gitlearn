#include <condition_variable>
#include <functional>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <thread>
#include <vector>

class ThreadPool {
public:
    explicit ThreadPool(size_t num_threads);
    ~ThreadPool();

    // 提交任务，返回 future 用于获取结果
    template <typename T>
    std::future<typename std::result_of<T()>::type> submit(T task);

private:
    // 工作线程主循环
    void worker();

    // 停止标志
    bool stop;

    // 任务队列
    std::queue<std::function<void()>> tasks;

    // 同步机制
    std::mutex mtx;
    std::condition_variable cv;

    // 线程池
    std::vector<std::thread> workers;
};

template <typename T>
std::future<typename std::result_of<T()>::type> ThreadPool::submit(T task)
{
    using return_type = typename std::result_of<T()>::type;

    auto *packaged_task = new std::packaged_task<return_type()>(std::forward<T>(task));
    std::future<return_type> result = packaged_task->get_future();

    {
        std::unique_lock<std::mutex> lock(mtx);
        tasks.emplace([packaged_task]() {
            (*packaged_task)();
            delete packaged_task;
        });
    }

    cv.notify_one();
    return result;
}