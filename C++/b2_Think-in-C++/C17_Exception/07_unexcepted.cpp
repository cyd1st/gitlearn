#include <iostream>
#include <stdexcept>
// #include <setjmp.h>

// 自定义 unexpected 函数
void my_unexpected() {
    std::cerr << "An unexpected exception was thrown from a catch block.\n";
    std::abort();  // 也可以在这里做其他处理，比如写日志等
}

int main() {
    std::set_unexpected(my_unexpected);

    try {
        try {
            // 抛出一个异常
            throw std::runtime_error("First error");
        } catch (const std::runtime_error& e) {
            std::cerr << "Caught runtime_error: " << e.what() << '\n';
            // 在 catch 块中再次抛出一个异常
            throw std::runtime_error("Second error");
        }
    } catch (...) {
        // 这里不会被捕获，因为上层已经调用了 unexpected
    }

    return 0;
}

