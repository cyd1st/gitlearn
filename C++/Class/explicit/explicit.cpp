// explicit 在 C++20 有新含义。
// 1. 指定的构造函数不能隐私转换和复制初始化。
// 2. 只能用在类的内部的构造函数或者转换函数。

// 以下代码来自 cpprefrence
struct A {
    A(int) {} // 转换构造函数
    A(int, int) {}
    operator bool() const { return true; }
};

struct B {
    explicit B(int) {}
    explicit B(int, int) {}
    explicit operator bool() const { return true; }
};

int main()
{
    /*------- 正常组 ------*/
    A a1 = 1;
    A a2(2);
    A a3{4, 5};
    A a4 = {4, 5};
    A a5 = (A)1;

    if (a1) {
    };
    bool na1 = a1;
    bool na2 = static_cast<bool>(a1);

    /*------- 对照组 ------*/
    // B b1 = 1;        // Error: 复制初始化，调用的B(int)不支持隐式
    B b2(2);    // OK: 直接初始化
    B b3{4, 5}; // OK: 直接列表初始化
    // B b4 = {4, 5};   // Error: 复制列表初始化，调用B(int, int)
    B b5 = (B)1; // OK: 显式转换，调用 static_cast
    // if (b1) {};      // Error: 隐式转换，调用 B::operator bool
    // bool nb1 = b2;   // Error: 同上
    bool nb2 = static_cast<bool>(b2); // OK: 显式转换，调用 static_cast

    [](...) {}(a4, a5, na1, na2, b5, nb2); // 消除“未使用变量”警告
}