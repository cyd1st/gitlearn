#include <cstddef>
#include <iostream>
#include <mutex>
#include <random>
#include <set>
#include <thread>

using namespace std;

int main()
{
    set<int> int_set;
    mutex mtx;
    auto f = [&int_set, &mtx]() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dis(1, 1000);

        for (size_t i = 0; i < 10000; ++i) {
            // 注释掉下面这行，再多次运行看输出结果，前后对比
            lock_guard<mutex> lock(mtx);
            int_set.insert(dis(gen));
        }
    };

    thread t1(f), t2(f);
    t1.join();
    t2.join();

    cout << int_set.size() << endl;

    return 0;
}