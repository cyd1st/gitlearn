#include <atomic>
#include <iostream>

void fetch_add(int val)
{
    std::atomic<int> a{0};
    int excepted = a.load();
    while (!a.compare_exchange_weak(excepted, excepted + val))
        ;
    std::cout << a << std::endl;
}
int main()
{
    std::atomic<int> a{0};

    int expected = a.load();
    int desired = expected + 1;
    bool success = a.compare_exchange_weak(expected, desired);
    // may fail
    if (success) {
        std::cout << "success" << std::endl;
    } else {
        std::cout << "fail" << std::endl;
    }

    std::cout << a << std::endl;
    fetch_add(5);
    return 0;
}