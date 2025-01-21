#include <cstdio>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>

void func1()
{
    std::fstream file;
    file.open("fstream_t.cpp", std::ios_base::in);

    std::string line;
    while (getline(file, line)) {
        std::cout << line << std::endl;
    }
}

void func2()
{
    std::fstream file("fstream_t.cpp");

    std::string line;
    while (getline(file, line)) {
        std::cout << line << std::endl;
    }
}

void func3()
{
    std::fstream file;
    file.open("example.txt", std::ios::trunc | std::ios::out);
}

void func4()
{
    std::fstream file;
    file.open("example.txt", std::ios::app | std::ios::in);

    std::string line;
    getline(file, line);
    std::cout << line << std::endl;

    file << "-----" << std::endl;

    getline(file, line);
    std::cout << std::unitbuf;
    std::cout << line << std::endl;
    std::cout << std::nounitbuf;
}

void func5()
{
    std::ifstream in("example.txt");
    std::string line;
    while (std::getline(in, line)) {
        std::cout << line << std::endl;
    }
}

int main()
{
    // func3();
    // func4();
    func5();
    return 0;
}