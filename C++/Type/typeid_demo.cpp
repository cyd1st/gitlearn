#include <iostream>
#include <typeinfo>

class Base {
    virtual void f() {}
};

class Derived : public Base {
    void f() override {}
};

int main()
{
    Base *b = new Derived();
    // 输出：Derived类型的名称: 7Derived。由编译器决定。
    std::cout << typeid(*b).name() << std::endl; 
    return 0;
}