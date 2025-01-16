#include <chrono>
#include <iostream>

std::string generateUniqueId()
{
    // 获取当前的系统时间戳，单位为毫秒
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = now.time_since_epoch();
    long long timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

    return std::to_string(timestamp);
}

int main()
{
    std::cout << "Unique ID: " << generateUniqueId() << std::endl;
    return 0;
}