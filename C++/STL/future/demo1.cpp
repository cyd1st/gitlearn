// future 的基本使用demo
#include <chrono>
#include <future>
#include <iostream>
#include <thread>
using namespace std;

int main()
{
    auto f = async(std::launch::async, []() {
        cout << "future  started" << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cout << "future  finished" << endl;
        return 42;
    });

    cout << "main thread waiting" << endl;
    cout << f.get() << endl;
    return 0;
}