#include <iostream>
#include "thread_guard.h"

int main()
{
    // 使用自创的线程guard
    std::thread t([]() {
        std::cout << "thread start" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "thread end" << std::endl;
    });
    ThreadGuard tg(t);

    std::cout << "main thread end" << std::endl;
    return 0;
}