#include <iostream>
#include <type_traits>

typedef char *pstring;

template <typename T, typename U> void check_type_equality()
{
    if (std::is_same<T, U>::value) {
        std::cout << "Types are equal." << std::endl;
    } else {
        std::cout << "Types are NOT equal." << std::endl;
    }
}

int main()
{
    const pstring p1 = nullptr;
    const pstring *p2 = nullptr;
    pstring const *p3 = nullptr;

    check_type_equality<decltype(p1), char *const>();

    check_type_equality<decltype(p2), char *const *>();

    check_type_equality<decltype(p3), char *const *>();

    return 0;
}