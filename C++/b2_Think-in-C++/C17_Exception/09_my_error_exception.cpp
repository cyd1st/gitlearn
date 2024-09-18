/* 本例由 runtime_error 类派生出自己的异常类。
 * runtime_error 一般指运行时无法预料的错误，比如
 * 资源不足等。
 *
 * 一般异常类都提供 string 类型为入参的构造函数，然后
 * 通过 what 成员函数获取。
 */

#include <iostream>
#include <stdexcept>

using namespace std;

class MyError: public runtime_error {
public:
    MyError(const string& msg = ""): runtime_error(msg) {}
};

int main()
{
    try {
        throw MyError("my error message");
    } catch (MyError& e) {
        cout << e.what() << endl;
    }
}