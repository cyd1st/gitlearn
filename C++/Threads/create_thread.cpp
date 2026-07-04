#include <iostream>
#include <string>
#include <thread>

void process_data(std::unique_ptr<int> data) { std::cout << "Data: " << *data << std::endl; }

void modify_value(int &value) { value = 100; }

void print_string(const std::string &s)
{
    // s = s + "  World";
    std::cout << s << std::endl;
}

int main()
{
    // 移动语义传递线程参数
    auto data = std::make_unique<int>(42);
    std::thread t(process_data, std::move(data)); // 移动 data 到线程中
    // *data = 0;                                    // 运行报错 Segmentation fault
    t.join();

    // 引用传递线程参数
    int val = 0;
    std::thread t2(modify_value, std::ref(val)); // 传递引用
    // std::thread t2(modify_value, val); // 报错
    t2.join();
    std::cout << "Modified value: " << val << std::endl; // 输出 100

    // 常量支持右值引用
    std::string str = "t3";
    std::thread t3(print_string, str); // str 被拷贝进线程
    t3.join();

    std::thread t4([](const std::string &s) { std::cout << "Hello " << s << std::endl; }, "Jack");
    t4.join();
}