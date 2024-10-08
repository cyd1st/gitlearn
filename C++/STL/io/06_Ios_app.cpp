#include <iostream>
#include <fstream>

int main()
{
    std::ofstream file("./out/test.txt", std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Failed open file." << std::endl;
    }

    file << "First line" << std::endl;
    file.seekp(0);
    file << "Second line" << std::endl;

    file.close();
    return 0;
}


