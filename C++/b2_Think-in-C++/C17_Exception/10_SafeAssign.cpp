#include <cstddef>
#include <cstring>
#include <iostream>
#include <new> //为了抛出异常bad_alloc

using namespace std;

class HasPointers {
    // 这里设置一个句柄类来管理我们的数据
    struct MyData {
        const char *theString;
        const int *theInts;
        size_t numInts;

        MyData(const char *pString, const int *pInts, size_t nInts)
            : theString(pString), theInts(pInts), numInts(nInts)
        {
        }
    } *theData;

    // 这里为了安全的分配内存，我们使用一个clone静态函数
    static MyData *clone(const char *otherString, const int *otherInts, size_t nInts)
    {
        char *newChars = new char[strlen(otherString) + 1];
        int *newInts;

        try {
            newInts = new int[nInts];
        } catch (bad_alloc &) {
            delete[] newChars;
            throw;
        }

        try {
            strcpy(newChars, otherString);
            for (size_t i = 0; i < nInts; ++i)
                newInts[i] = otherInts[i];
        } catch (...) {
            delete[] newInts;
            delete[] newChars;
            throw;
        }
        return new MyData(newChars, newInts, nInts);
    }

    // 一个重载的clone,拷贝构造函数
    static MyData *clone(const MyData *otherData)
    {
        return clone(otherData->theString, otherData->theInts, otherData->numInts);
    }
    // 内存清理
    static void cleanup(const MyData *theData)
    {
        // 回收全部内存,只要使用了指针的，都要把指针指向的内存回收掉
        delete theData->theString;
        delete theData->theInts;
        delete theData;
    }

public:
    HasPointers(const char *someString, const int *someInts, size_t numInts)
    {
        theData = clone(someString, someInts, numInts);
    }
    // 拷贝构造函数
    HasPointers(const HasPointers &source) { theData = clone(source.theData); }
    // 赋值拷贝运算符
    HasPointers &operator=(const HasPointers &rhs)
    {
        // 避免自赋值
        if (this != &rhs) {
            MyData *newData =
                clone(rhs.theData->theString, rhs.theData->theInts, rhs.theData->numInts);
            cleanup(theData);
            theData = newData;
        }
        return *this;
    }
    // 析构函数
    ~HasPointers() { cleanup(theData); }
    // 友元函数
    friend ostream &operator<<(ostream &os, const HasPointers &obj)
    {
        os << obj.theData->theString << " : ";
        for (size_t i = 0; i < obj.theData->numInts; ++i)
            os << obj.theData->theInts[i] << ' ';
        return os;
    }
};

int main()
{
    int someNums[] = {1, 2, 3, 4};
    size_t someCount = sizeof(someNums) / sizeof(someNums[0]);

    int someMoreNums[] = {5, 6, 7};
    size_t someMoreCount = sizeof(someMoreNums) / sizeof(someMoreNums[0]);

    HasPointers h1("Hello", someNums, someCount);
    HasPointers h2("Goodbye", someMoreNums, someMoreCount);
    cout << h1 << endl;
    h1 = h2;
    cout << h1 << endl;

    return 0;
}
