//: C04:Format.cpp
// Formatting Functions.
#include <fstream>
#include <iostream>
#include "../../b2_Think-in-C++/lib/require.h"
using namespace std;
#define D(A)                                                                                       \
    T << #A << endl;                                                                               \
    A

int main()
{
    ofstream T(".\\out\format.out");
    assure(T, "open failed.");
    D(int i = 47;)
    D(float f = 2300114.414159;)
    D(const char *s = "Is there any more?");

    D(T.setf(ios::unitbuf);)                  // 即时缓冲
    D(T.setf(ios::showbase);)                 // 显示进制
    D(T.setf(ios::uppercase | ios::showpos);) // 十六进制使用大写表示，并且显式正负号

    D(T << i << endl;) // Default is dec // +47

    D(T.setf(ios::hex, ios::basefield);) //  清除其他进制的设置，并设置输出位16进制
    D(T << i << endl;)                   // 0X2F

    D(T.setf(ios::oct, ios::basefield);) // 清除其他进制的设置，并设置输出位8进制
    D(T << i << endl;)                   // 057

    D(T.unsetf(ios::showbase);)          // 清除显示进制的设置
    D(T.setf(ios::dec, ios::basefield);) // 清除其他进制的设置，并设置输出位10进制

    D(T.setf(ios::left,
             ios::adjustfield);) // 设置对齐方式，第二参数指定第一个参数的作用领域，其实可以省略。
    D(T.fill('0');)                            // 填充字符0
    D(T << "fill char: " << T.fill() << endl;) // 获取填充的字符
    D(T.width(10);)                            // 设置输出宽度为
    T << i << endl;                            // +470000000

    D(T.setf(ios::right, ios::adjustfield);)
    D(T.width(10);)
    T << i << endl; // 0000000+47

    D(T.setf(ios::internal, ios::adjustfield);) // internal 将填充字符放在正负号与数值之间
    D(T.width(10);)
    T << i << endl;    // +000000047
    D(T << i << endl;) // Without width(10)

    D(T.unsetf(ios::showpos);)                   // 清除设置正负号
    D(T.setf(ios::showpoint);)                   // 生成十进制的小数点
    D(T << "prec = " << T.precision() << endl;)  // 获取小数点精度大小，此处为 6
    D(T.setf(ios::scientific, ios::floatfield);) // 输出浮点数的科学计算法
    D(T << endl << f << endl;)                   // 2.300114E+06
    D(T.unsetf(ios::uppercase);)                 // 取消设置大小写
    D(T << endl << f << endl;)                   // 2.300114e+06
    D(T.setf(ios::fixed, ios::floatfield);)
    D(T << f << endl;)

    D(T.precision(20);)                         // 精度设置为 20
    D(T << "prec = " << T.precision() << endl;) // 获取小数点后精度大小，此处为 20
    D(T << endl << f << endl;) // 之前设置的科学计数法已经失效。2300114.50000000000000000000
    D(T.setf(ios::scientific, ios::floatfield);) // 再次设置科学计数，且为浮点数
    D(T << endl << f << endl;)                   // 2.30011450000000000000e+06
    D(T.setf(ios::fixed, ios::floatfield);)      // 使用定点法表示数字
    D(T << f << endl;)                           // 2300114.50000000000000000000

    D(T.width(10);) // 设置最小输出宽度为10
    T << s << endl; // Is there any more?
    D(T.width(40);) // 设置最小输出宽度为40
    T << s << endl; // 0000000000000000000000Is there any more?
    D(T.setf(ios::left, ios::adjustfield);)
    D(T.width(40);)
    T << s << endl;
} ///:~