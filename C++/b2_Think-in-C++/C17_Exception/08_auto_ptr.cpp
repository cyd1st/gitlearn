/** auto_ptr 在 c++11 中被标记废弃，c++17中正式移除。
本案例使用 auto_ptr 展示 RAII 特性 */

#include <memory>
#include <iostream>

using namespace std;

class TraceHeap {
    int i;
public:
    static void *operator new(size_t size) {
        void *p = ::operator new(size);
        cout << "Allocating TraceHeap object on the heap "
             << "at addreee " << p << endl;
        return p;
    }

    static void operator delete(void *p) {
        cout << "Deleting TraceHeap object on the heap "
             << "at addreee " << p << endl;
        ::operator delete(p);
    }

    TraceHeap(int i): i(i) {}
    int getVal() const { return i; }
};

int main() {
    auto_ptr<TraceHeap> p(new TraceHeap(6));
    cout << p->getVal() << endl;
    // 离开作用域智能指针会自动调用 delete
}