/**
 * 在构造函数中发生异常，不会触发析构函数。
 */

#include <iostream>
 
using namespace std;

class Cat {
public:
    Cat() {
        cout << "Cat()" << endl;
    }
    ~Cat() {
        cout << "~Cat()" << endl;
    }
};

class Dog {
public:
    void *operator new(size_t sz) {
        cout << "allocating a Dog" << endl;
        throw 47; // 模拟内存耗尽抛出错误。
    }

    void operator delete(void *p) {
        cout << "deallocating a Dog" << endl;
        ::operator delete(p); // 因为已经重载了 delete 函数，所以需要调用全局的。
    }
};

class UseResources {
    Cat *bp;
    Dog *op;
public:
    UseResources(int count = 1) {
        cout << "UseResources()" << endl;
        bp = new Cat[count];
        op = new Dog;
    }

    ~UseResources() {
        cout << "~UseResources()" << endl;
        delete[] bp;
        delete op;
    }
};

int main()
{
    try {
        UseResources ur(3);
    } catch (int) {
        cout << "inside handler" << endl;
    }

    return 0;
}

/*
执行结果：
UseResources()
Cat()
Cat()
Cat()
allocating a Dog
inside handler
*/