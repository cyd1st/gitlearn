#include <iostream>
#include <string>

using namespace std;


template <class T1, class T2>
class Pair
{
private:
    T1 key;
    T2 val;
    static int count;
public:
    Pair() { ++count; }
    Pair(T1 k, T2 v): key(k), val(v) {
        ++count;
    };
    ~Pair() { --count; }
    bool operator< (const Pair<T1, T2> &p) const;

    /*
      这里只是声明，放在这个模板中。但这个模板生成得函数不属于这个模板，
      而是属于 ostream 类的。所以不能使用这个模板的类型声明<class T1, class T2>，
      而需要自己声明一个模板，只不过也是<class T1, class T2>这种格式，因为是给参数
      Pair 类使用的。
      理解的顺序是：
        1. 先外部定义 ostream 类的 << 重载全局函数模板。
        2. 再将这个模板声明到此类作为友元，使能够访问私有成员。
      核心就是：operator< 是此类的成员，但是 operator<< 不是此类的成员，
      而是 ostream 类的成员，所以不能使用此类的模板，也就是外面的 template
      <class T1, class T2>。
     */ 
    template <class T3, class T4>
    friend ostream &operator<< (ostream &o, 
                     const Pair<T3, T4> &p);
    
    static void PrintCount() { cout << count << endl; }
};

template <class T1, class T2>
int Pair<T1, T2>::count = 0;

template <class T1, class T2>
bool Pair<T1, T2>::operator< (const Pair<T1, T2> &p) const
{
    return key < p.key;
}

template <class T1, class T2>
ostream & operator<< (ostream &o, const Pair<T1, T2> &p)
{
    o << '(' << p.key << ',' << p.val << ')';
    return o;
}

int main()
{
    Pair<string, int> stu1("Tom", 18);
    Pair<string, int> stu2("jane", 20);

    cout << (stu1 < stu2) << endl; // (Tom,18)
    cout << stu1 << endl;

    Pair<double, int> p1(23.21, 8);
    cout << p1 << endl; // (23.21,8)

    Pair<string, int>::PrintCount(); // 2
    Pair<double, int>::PrintCount(); // 1
    Pair<int, string>::PrintCount(); // 0

    return 0;
} 