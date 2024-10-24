#include <iostream>
#include <sstream>
#include <streambuf>

// 重定向输出到字符串
void testcase1()
{
    std::ostringstream buffer;                // 创建一个字符串输出流
    std::streambuf *sbuf = std::cout.rdbuf(); // 备份cout的缓冲区原始指针
    std::cout.rdbuf(buffer.rdbuf());          // 将cout的缓冲区替换为buffer的缓冲区

    // 使用cout，实际上输出到了buffer
    std::cout << "This will go to string stream." << std::endl;

    std::cout.rdbuf(sbuf); // 恢复cout的原始缓冲区

    // 输出buffer中的内容
    std::cout << "Buffer contains: " << buffer.str() << std::endl;
}

// 手动刷新缓冲区
void testcase2()
{
    std::cout << "Hello, World!";
    std::cout.flush(); // 这实际上调用了rdbuf()->pubsync()

    std::cout.rdbuf()->pubsync(); // 手动刷新缓冲区
}

class uppercase_streambuf : public std::streambuf {
public:
    virtual int_type overflow(int_type c) override
    {
        if (c != EOF && std::islower(c)) {
            c = std::toupper(static_cast<char>(c));
        }
        return std::streambuf::overflow(c);
    }
};

void testcase3() {}

int main()
{
    testcase1();
    testcase2();
    // testcase3();
    return 0;
}