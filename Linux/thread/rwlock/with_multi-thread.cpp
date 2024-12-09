#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <vector>

using namespace std;

int g_counter = 0; // 模拟共享资源
shared_mutex g_mutex;

void reader(int tid)
{
    // 尝试获取共享锁
    shared_lock<shared_mutex> lock(g_mutex);
    // Tips：多线程下并发输出会导致顺序混乱。和 endl 与 \n 没有关系。
    cout << "Reader " << tid << " get value: " << g_counter << endl;
    // cout << "Reader " << tid << " get value: " << g_counter << "\n";
}

void writer(int tid, int value)
{
    // 尝试获取独占锁
    unique_lock<shared_mutex> lock(g_mutex);
    g_counter = value;
    cout << "Writer " << tid << " set value: " << g_counter << endl;
    // cout << "Writer " << tid << " set value: " << g_counter << "\n";
}

int main()
{
    vector<thread> threads;

    // 创建多个读取线程
    int i;
    for (i = 0; i < 10; ++i) {
        threads.emplace_back(reader, i);
    }
    // 创建写线程
    threads.emplace_back(writer, i, 1435);

    for (auto &th : threads) {
        if (th.joinable()) {
            th.join();
        }
    }

    return 0;
}