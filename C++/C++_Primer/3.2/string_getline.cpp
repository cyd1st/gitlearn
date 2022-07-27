#include <iostream>

// using std::string;

int main(void) {
    std::string line;

    while (getline(std::cin, line)) {
        if (!line.empty()) {
            std::cout << line.size() << std::endl;
            std::cout << line << std::endl; 
        }
    }

    return 0;
} 
