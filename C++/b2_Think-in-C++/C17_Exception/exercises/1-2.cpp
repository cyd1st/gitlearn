
#include <iostream>
#include <stdexcept>

class MyClass {
public:
    // 嵌套异常类
    class MyException : public std::runtime_error {
    public:
        MyException(const char *whatArg) : std::runtime_error(whatArg) {}
    };

    // 成员函数，模拟某种操作并抛出异常
    void doSomethingThatThrows()
    {
        // 模拟某种条件下的异常
        bool condition = true; // 假设这个条件导致异常
        if (condition) {
            throw MyException("This is a custom exception message.");
        }
    }
};

int main()
{
    MyClass myObject;

    try {
        myObject.doSomethingThatThrows();
    } catch (const MyClass::MyException &ex) {
        // 捕获并处理异常
        std::cerr << "Caught exception: " << ex.what() << std::endl;
    }

    return 0;
}