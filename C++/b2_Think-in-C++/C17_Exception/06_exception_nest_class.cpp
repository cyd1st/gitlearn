/*解决在构造函数发生异常的问题
 *(对比05案例)
 * 
 * 真正解决的不是发生异常的那个对象及链路上无法析构的问题，
 * 而是使其他正常构造的对象不会被波及，能够正常析构。
 *
 * 原理就是嵌套封装一层，使两个不同的要构造的对象隔离开，
 * 单独构造。发生异常时不会影响平行的对象。如下示例中的 Dog
 * 发生异常时不会影响 Cat 析构。
 */

#include <iostream>

using namespace std;

template<class T, int sz = 1> class PWrap {
    T *ptr;
public:
    class RangeError {}; // 自定义的异常对象
    PWrap() {
        ptr = new T[sz];
        cout << "PWrap constructor" << endl;
    }
    ~PWrap() {
        delete[] ptr;
        cout << "PWrap destructor" << endl;
    }

    T& operator[](int i) {
        if (i >= 0 && i < sz) return ptr[i];
        throw RangeError();
    }

};

class Cat {
public:
    Cat() {
        cout << "Cat()" << endl;
    }
    ~Cat() {
        cout << "~Cat()" << endl;
    }
    void g() {}
};

class Dog {
public:
    void *operator new[](size_t sz) {
        cout << "allocating a Dog" << endl;
        throw 47; // 模拟内存耗尽抛出错误。
    }

    void operator delete[](void *p) {
        cout << "deallocating a Dog" << endl;
        ::operator delete[](p); // 因为已经重载了 delete 函数，所以需要调用全局的。
    }
};

class UseResources {
    PWrap<Cat, 3> cats;
    PWrap<Dog> dog;

public:
    UseResources() {
        cout << "UseResources()" << endl;
    }

    ~UseResources() {
        cout << "~UseResources()" << endl;
    }

    void f() {
        cats[1].g();
    }
};

int main()
{
    try {
        UseResources ur;
    } catch (int) {
        cout << "inside handler" << endl;
    } catch(...) {
        cout << "inside catch(...)" << endl;
    }

    return 0;
}

/*
执行结果：
Cat()
Cat()
Cat()
PWrap constructor
allocating a Dog
~Cat()
~Cat()
~Cat()
PWrap destructor
inside handler
*/