#include <future>
#include <iostream>
#include <stdexcept>

// 异步任务函数
int throwing_task()
{
    throw std::runtime_error("Future异常测试");
    return 42; // 不可达
}

int main()
{
    // 创建异步任务
    std::future<int> fut = std::async(std::launch::async, throwing_task);
    try {
        // 获取结果时会重新抛出异常
        int result = fut.get();
    } catch (const std::exception &e) {
        std::cerr << "捕获到异常: " << e.what() << std::endl;
    }

    return 0;
}