#include <iostream>
#include "thread_guard.h"

int main()
{
    // 使用自创的线程guard
    std::thread t([]() {
        std::cout << "[Thread] start" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "[Thread] end" << std::endl;
    });

    try {
        ThreadGuard tg(t);
        std::cout << "[Main] 模拟抛出异常..." << std::endl;
        throw std::runtime_error("Oops! 发生了意外情况.");
    } catch (const std::runtime_error &e) {
        std::cout << "[Mian] 捕获到异常：" << e.what() << std::endl;
    }

    std::cout << "[Mian] thread end" << std::endl;
    return 0;
}