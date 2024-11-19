#include <iostream>
#include <thread>

using namespace std;

int main()
{
    int index = 0;
    // note: 并非一定要函数作为入参，只需要是可调用对象就行。
    thread t1(
        [&index](int a, int b) {
            cout << ++index << ": " << this_thread::get_id() << ": " << a + b << endl;
        },
        100,
        200);

    t1.join();
    return 0;
}