#include <cassert>

int main()
{
    assert(0 > 1);
    return 0;
}

/*
开启assert：g++ 11_assert.cpp -o ../out/11 && ../out/11
关闭assert：g++ 11_assert.cpp -o ../out/11 -NDEBUG && ../out/11
*/