// 测试 std::getline 函数遇到末尾没有换行符的情况

#include <fstream>
#include <iostream>
#include <string>

const char filename[] = "tempfile.txt";

int main()
{
    std::ofstream createFile(filename);
    if (!createFile.is_open()) {
        std::cerr << "Failed to create file.\n";
        return 1;
    }
    createFile << "First line\nSecond line\nLast line without newline";
    createFile.close();

    // open the file just written
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file.\n";
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << '\n';
    }

    // check if end of file
    if (file.eof()) {
        std::cout << "Reached end of file.\n";
    } else {
        std::cout << "An error occurred other than EOF.\n";
    }

    // check if last read succeeded
    if (file.fail()) {
        std::cout << "The last read operation failed.\n";
    } else {
        std::cout << "The last read operation was successfil.\n";
    }

    file.close();
    return 0;
}