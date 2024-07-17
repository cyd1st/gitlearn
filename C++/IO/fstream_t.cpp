#include <cstdio>
#include <ios>
#include <iostream>
#include <fstream>
#include <string>

void func1() {
    std::fstream file;
    file.open("fstream_t.cpp", std::ios_base::in);

    std::string line;
    while (getline(file, line)) {
        std::cout << line << std::endl;
    }
}

void func2() {
    std::fstream file("fstream_t.cpp");

    std::string line;
    while (getline(file, line)) {
        std::cout << line << std::endl;
    }
}

void func3() {
    std::fstream file;
    file.open("example.txt", std::ios::trunc | std::ios::out);
}

void func4() {
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
int main() {
    
    func3();
    func4();
    return 0;
}