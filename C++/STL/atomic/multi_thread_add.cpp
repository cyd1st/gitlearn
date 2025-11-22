#include <atomic>
#include <iostream>
#include <thread>

// -------- atomic add
std::atomic<int> count{0};

void increment1()
{
    for (int i = 0; i < 1000000; i++) {
        count.fetch_add(1); // equivalent to count++
    }
}

int case1()
{
    std::thread t1(increment1);
    std::thread t2(increment1);

    t1.join();
    t2.join();

    std::cout << "Fetch add count: " << count.load() << std::endl;

    return 0;
}

// --------- non-atomic add

int count2 = 0;

void increment2()
{
    for (int i = 0; i < 1000000; i++) {
        count2++; // equivalent to count++
    }
}

int case2()
{
    std::thread t1(increment2);
    std::thread t2(increment2);

    t1.join();
    t2.join();

    std::cout << "add count: " << count2 << std::endl;

    return 0;
}

// ----------

int main()
{
    case1();
    case2();

    return 0;
}

// run result:
// Fetch add count: 2000000
// add count: 1041423