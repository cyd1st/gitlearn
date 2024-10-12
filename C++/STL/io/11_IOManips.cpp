//: C04:Manips.cpp
// Format.cpp using manipulators.
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

int main()
{
    ofstream trc("./out/trace.out");
    int i = 47;
    float f = 2300114.414159;
    const char *s = "Is there any more?";

    // 设置即时输出，显示进制（十进制自然不变），大写进制，显示正号
    trc << setiosflags(ios::unitbuf | ios::showbase | ios::uppercase | ios::showpos);
    trc << i << endl;                            // +47
    trc << hex << i << endl << oct << i << endl; // 0X2F, 057
    trc.setf(ios::left,
             ios::adjustfield); // 设置左对齐，adjustfield 只是限定 left 的作用域为对齐方式
    trc << resetiosflags(ios::showbase) << dec
        << setfill('0'); // 不显示进制，设置十进制，且设置填充0
    trc << "fill char: " << trc.fill() << endl; // 打印填充的字符
    trc << setw(10) << i << endl;               // 设置输出最小宽度为10， +470000000
    trc.setf(ios::right, ios::adjustfield);
    trc << setw(10) << i << endl;
    trc.setf(ios::internal, ios::adjustfield); // 设置填充在符号后面，数值之前
    trc << setw(10) << i << endl;              // +000000047
    trc << i << endl;                          // Without setw(10)

    trc << resetiosflags(ios::showpos) << setiosflags(ios::showpoint)
        << "prec = " << trc.precision() << endl; // 不显示正号，显示小数点，输出精度
    trc.setf(ios::scientific, ios::floatfield); // 
    trc << f << resetiosflags(ios::uppercase) << endl;
    trc.setf(ios::fixed, ios::floatfield);
    trc << f << endl;
    trc << f << endl;
    trc << setprecision(20);
    trc << "prec = " << trc.precision() << endl;
    trc << f << endl;
    trc.setf(ios::scientific, ios::floatfield);
    trc << f << endl;
    trc.setf(ios::fixed, ios::floatfield);
    trc << f << endl;
    trc << f << endl;

    trc << setw(10) << s << endl;
    trc << setw(40) << s << endl;
    trc.setf(ios::left, ios::adjustfield);
    trc << setw(40) << s << endl;
} ///:~