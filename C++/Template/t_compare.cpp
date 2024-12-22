#include <iostream>
#include <cstring>
#include <functional>

template<typename T>
int Compare(const T &a, const T &b)
{
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

// 可能会和前一个函数模板产生二义性，比如main函数中的char 数组比较。
template<unsigned N, unsigned M>
int Compare(const char (&s1)[N], const char (&s2)[M])
{
    return strcmp(s1, s2);
}

int main()
{
    int a = 10, b = 20;
    std::cout << Compare(a, b) << std::endl;

    double c = 12.45, d = 12.45;
    std::cout << Compare(c, d) << std::endl;

    // 不能比较相同长度的字符数组，因为这个函数模板会和前一个函数模板产生二义性。
    // 是因为下面的字符数组会被当做 char *类型
    const char s1[] = "hello", s2[] = "world-";
    std::cout << Compare(s1, s2) << std::endl;

    return 0;
}