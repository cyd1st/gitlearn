#include <cstddef>
#include <cstring>
#include <iostream>
#include <utility>

using namespace std;

/**
 * 只有在管理资源，性能敏感时才有必要移动构造。
 */
class MyLargeBuffer {
private:
    char *data;
    size_t size;

public:
    // 默认构造函数，有了下面的自定义构造函数，就必须手动创建默认构造函数才行了
    MyLargeBuffer() : size(0), data(nullptr) {
        cout << "MyLargeBuffer()" << endl;
    }
    MyLargeBuffer(size_t sz) : size(sz), data(new char[sz]) {
        cout << "MyLargeBuffer(" << sz << ")" << endl;
    }
    ~MyLargeBuffer() {
        delete[] data;
        cout << "~MyLargeBuffer()" << endl;
    }

    // 移动构造函数
    MyLargeBuffer(MyLargeBuffer &&other) noexcept {
        data = other.data;
        size = other.size;
        other.data = nullptr; // 转移所有权：注意清除原有的指针
        other.size = 0;
        cout << "MyLargeBuffer(MyLargeBuffer &&other) " << endl;
    }

    // 移动复制运算符重载（不创建编译器会默认创建的）
    MyLargeBuffer& operator=(MyLargeBuffer&& other) noexcept {
        cout << "MyLargeBuffer& operator=(MyLargeBuffer&& other)" << endl;
        if (this != &other) {
            delete[] data; // 切记注意释放当前指向的内存，否则内存泄漏
            this->data = other.data;
            this->size = other.size;
            other.data = nullptr; // 资源所有权转义，不然也会有大问题
            other.size = 0;
        }
        return *this;
    }

    // 拷贝构造函数
    MyLargeBuffer(MyLargeBuffer &other) noexcept {
        size = other.size;
        data = new char[size];
        std::memcpy(data, other.data, size);
        cout << "MyLargeBuffer(MyLargeBuffer &other)" << endl;
    }

    // 拷贝运算符重载
    MyLargeBuffer& operator=(MyLargeBuffer &other) noexcept {
        if (this != &other) {
            size = other.size;
            data = new char[size];
            std::memcpy(data, other.data, size);
        }
        cout << "MyLargeBuffer& operator=(MyLargeBuffer &other)" << endl;
        return *this;
    }

};

int main()
{
    MyLargeBuffer buf1; // 默认构造函数
    // MyLargeBuffer buf2(); // warnning: buf2 is a function, not a object
    MyLargeBuffer buf3(1024); // 自定义构造函数
    MyLargeBuffer buf4 = MyLargeBuffer(); // 默认构造函数
    MyLargeBuffer buf5 = buf3; // 赋值构造函数
    MyLargeBuffer buf6 = std::move(buf3); // 移动构造函数
    buf4 = std::move(buf3); // 移动赋值语句
    buf1 = MyLargeBuffer(100); // 构造函数 + 移动赋值
    buf5 = buf4; // 拷贝构造函数
    
    return 0;
}