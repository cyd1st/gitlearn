#include <variant>
#include <iostream>
#include <string>

int main() {
    std::variant<int, double, std::string> v; // 定义一个 std::variant 对象
    v = 10; // 存储 int 类型的值
    std::cout << "Stored int value: " << std::get<int>(v) << std::endl;

    v = 3.14; // 存储 double 类型的值
    std::cout << "Stored double value: " << std::get<double>(v) << std::endl;

    v = "hello"; // 存储 std::string 类型的值
    std::cout << "Stored string value: " << std::get<std::string>(v) << std::endl;

    // 使用 std::visit 访问不同类型的值
    std::visit([](auto&& value) { // 使用一个可以接受多种类型的lambda表达式作为访问者
        std::cout << "Visited value: " << value << std::endl;

        // 通常不推荐，应该不符合 visit 的设计原则。
        std::cout << "handling type: " << typeid(value).name() << std::endl;
    }, v);

    return 0;
}