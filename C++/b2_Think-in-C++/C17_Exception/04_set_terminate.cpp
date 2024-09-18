/*自定义异常终止函数*/

#include <exception>
#include <iostream>

using namespace std;

void terminator() {
    cout << "I'll be back!" << endl;
    exit(0);
}

void (*old_terminate)() = set_terminate(terminator);

class Botch {
public:
    class Fruit {};
    void f() {
        cout << "Botch::f()" << endl;
        throw Fruit();
    }
    ~Botch() {
        // 编译会告警，是故意构造的，因为析构函数不应该抛出异常
        // 所以运行时会异常终止
        throw 'C';
    }
};

int main()
{
    try {
        Botch b;
        b.f();
    } catch (...) {
        // 这里捕获的是第一个异常，即 b.f();
        cout << "inside catch(...)" <<endl;
    }
    // 这里触发第二个异常 Botch 的析构
    return 0;
}