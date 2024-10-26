//: C04:Locale.cpp {-g++}{-bor}{-edg} {RunByHand}
// Illustrates effects of locales.
#include <iostream>
#include <locale>
using namespace std;

int main()
{
    locale def;
    cout << def.name() << endl; // C
    locale current = cout.getloc();
    cout << current.name() << endl; // C

    float val = 1234.56;
    cout << val << endl;
    // Change to French/France

    /*
     系统可能不支持
     使用 locale -a 查看，如果没有
     使用 sudo locale-gen fr_FR.UTF-8s 添加
     */
    cout.imbue(locale("fr_FR.utf8"));
    current = cout.getloc();
    cout << current.name() << endl; // fr_FR.utf8
    cout << val << endl;            // 1 234,56

    cout << "Enter the literal 7890,12: "; // 测试输入
    cin.imbue(cout.getloc());
    cin >> val;
    cout << val << endl; // 7 890,12
    cout.imbue(def);     // 恢复地区设置
    cout << val << endl; // 7890.12
} ///:~