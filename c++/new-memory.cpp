/*
 * @Descripttion: new的使用
 * @Author: cyd
 * @Date: 2021-07-28 17:44:04
 * @LastEditTime: 2021-07-28 18:16:15
 */
#include <iostream>
using namespace std;

int main()
{
    /*c语言方法仍可以使用*/
    int *p = (int *)malloc(sizeof(int) * 10);
    *(p+9) = 100;
    printf("*(p+9) = %d\n", *(p+9));
    free(p);
    printf("*(p+9) = %d\n", *(p+9));

    /*分配一个int大小的空间*/
    p = new int;   //C++使用new和delete
    *p = 200;
    cout<<*p<<endl;
    delete p;

    /*分配10个char大小空间*/
    char *str = new char[10];    //这里不能再使用p，因为p是int指针，(char *)强转也不行
    cin>>str;                    //输入字符可以超过10，可能造成内存泄露
    cout<<str<<endl;
    delete[] str;

    return 0;
}