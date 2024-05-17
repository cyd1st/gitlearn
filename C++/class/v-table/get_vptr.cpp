#include <iostream>
using namespace std;

class Base {
public:
    virtual void a() { cout << "Base a()" << endl; }
    virtual void b() { cout << "Base b()" << endl; }
    virtual void c() { cout << "Base c()" << endl; }
};

class Derive : public Base {
public:
    virtual void b() { cout << "Derive b()" << endl; }
    virtual void d() { cout << "Derive d()" << endl; }
};

int main() {
    Base* q = new Base;
    long* tmp1 = (long*)q;
    long* vptr1 = (long*)(*tmp1);
    cout << "Base vptr:" << endl;
    for (int i = 0; i < 3; ++i) {
        printf("vptr[%d]: %p\n", i, (void *)vptr1[i]);
    }

    Derive* p = new Derive;
    long* tmp = (long*)p;
    long* vptr = (long*)(*tmp);
    cout << "Derive vptr:" << endl;
    for (int i = 0; i < 4; ++i) {
        printf("vptr[%d]: %p\n", i, (void *)vptr[i]);
    }

    return 0;
}   