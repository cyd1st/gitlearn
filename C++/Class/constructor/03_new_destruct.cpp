/* new 出来的对象是不会自动析构的 */
#include <iostream>

class MyClass {
public:
    MyClass() { std::cout << "MyClass()" << std::endl; }
    ~MyClass() { std::cout << "~MyClass()" << std::endl; }
};

int main() {
    MyClass *a = new MyClass();
    // MyClass b;
}