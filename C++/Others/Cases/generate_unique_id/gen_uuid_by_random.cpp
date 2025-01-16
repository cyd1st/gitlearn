#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>

std::string generateUUID()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 15);

    std::stringstream ss;
    ss << std::hex;
    for (int i = 0; i < 8; ++i) {
        ss << dist(gen);
    }
    ss << "-";
    for (int i = 0; i < 4; ++i) {
        ss << dist(gen);
    }
    ss << "-";
    for (int i = 0; i < 4; ++i) {
        ss << dist(gen);
    }
    ss << "-";
    for (int i = 0; i < 4; ++i) {
        ss << dist(gen);
    }
    ss << "-";
    for (int i = 0; i < 12; ++i) {
        ss << dist(gen);
    }

    return ss.str();
}

int main()
{
    std::cout << "Generated UUID: " << generateUUID() << std::endl;
    return 0;
}