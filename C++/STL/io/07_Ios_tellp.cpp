#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ofstream file("./out/example.txt", std::ios::out | std::ios::trunc);

    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    // 写入数据
    file << "First line." << std::endl;

    // 获取当前写入位置
    std::streampos currentPosition = file.tellp();
    std::cout << "Current position after writing first line: " << currentPosition << std::endl;

    // 写入更多数据
    file << "Second line." << std::endl;

    // 获取新的写入位置
    std::streampos newPosition = file.tellp();
    std::cout << "Current position after writing second line: " << newPosition << std::endl;

    file.close();
    return 0;
}