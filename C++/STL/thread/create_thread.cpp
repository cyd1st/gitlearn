#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

class foo {
public:
    void f(int a) { cout << "foo::f: " << a << endl; }
};

int main()
{
    // e.g: 并非一定要函数作为入参，只需要是可调用对象就行。
    int index = 0;
    thread t1(
        [&index](int a, int b) {
            // std::this_thread::sleep_for(std::chrono::seconds(2));
            // note: 直接输入时长
            std::this_thread::sleep_for(2000ms);
            cout << ++index << " thread id: " << this_thread::get_id() << " -> " << a + b << endl;
        },
        100,
        200);
    // t1.detach();

    // e.g: 类成员函数在新线程执行，并传入参数
    foo f;
    thread t2(&foo::f, &f, 1000);

    t2.join();
    t1.join();
    return 0;
}