#include <bitset>
#include <chrono>
#include <iostream>
#include <random>

class SnowflakeIdGenerator {
public:
    SnowflakeIdGenerator(int nodeId) : nodeId(nodeId) {}

    long long generateUniqueId()
    {
        auto now = std::chrono::high_resolution_clock::now();
        auto duration = now.time_since_epoch();
        long long timestamp
            = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

        return (timestamp << 22) | (nodeId << 12) | (random() & 0xFFF);
    }

private:
    int nodeId; // 机器ID
    std::random_device rd;

    int random()
    {
        std::uniform_int_distribution<int> dist(0, 4095);
        return dist(rd);
    }
};

int main()
{
    SnowflakeIdGenerator generator(1); // 机器ID为1
    std::cout << "Generated Unique ID: " << generator.generateUniqueId() << std::endl;
    return 0;
}