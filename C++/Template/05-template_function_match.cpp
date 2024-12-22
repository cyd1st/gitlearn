#include <iostream>

using namespace std;

template <class T> 
T Max( T a, T b)
{
    cout << "TemplateMax" <<endl; return 0;
}

// template <class T,class T2> 
// T Max( T a, T2 b) {
//     cout << "TemplateMax2" <<endl; return 0;
// }

double Max(double a, double b)
{
    cout << "MyMax" << endl;
    return 0;
}

int main()
{
    int i=4, j=5;
    Max( 1.2,3.4); // 输出MyMax
    Max(i, j); //输出TemplateMax

    // 如果将 template <class T, class T2> 注释掉就会输出 MyMax
    Max( 1.2, 3); //输出TemplateMax2, 
    
    return 0; 
}