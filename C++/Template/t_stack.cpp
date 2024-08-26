/*实现简易Stack模板类的demo*/

#include <stdexcept>
#include <vector>

template <typename T>
class MyStack {
    std::vector<T> elements;

public:
    void push(const T& item) {
        elements.push_back(item);
    }

    T pop() {
        if (elements.empty()) {
            throw std::out_of_range("Stack is empty");
        }
        T top = elements.back();
        elements.pop_back();
        return top;
    }

    bool empty() {
        return elements.empty();
    }

    T peak() {
        return elements.back();
    }
};