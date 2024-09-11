#include <iostream>
#include <memory>
#include <stdexcept>

class MyClassUnsafe {
  public:
    MyClassUnsafe() {
        std::cout << "MyClassUnsafe()" << std::endl;
        data = new int[100]; // 动态分配内存
        throw std::runtime_error("Error during construction");
    }
    ~MyClassUnsafe() {
        std::cout << "~MyClassUnsafe()" << std::endl;
        delete[] data;
    }

  private:
    int *data;
};

class MyClassSafe {
  public:
    MyClassSafe() {
        std::cout << "MyClassSafe()" << std::endl;
        data = std::make_unique<int[]>(100); // 动态分配内存
        throw std::runtime_error("Error during construction");
    }
    ~MyClassSafe() {
        std::cout << "~MyClassSafe()" << std::endl;
        // delete[] data;
    }

  private:
    std::unique_ptr<int[]> data;
};

int main() {
    try {
        MyClassUnsafe a;
    } catch (std::runtime_error &e) {
        std::cout << e.what() << std::endl;
    }

    MyClassSafe b;
}