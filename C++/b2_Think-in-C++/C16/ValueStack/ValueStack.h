//: C16:ValueStack.h
// Holding objects by value in a Stack
#ifndef VALUESTACK_H
#define VALUESTACK_H
#include "../../lib/require.h"

template <class T, int ssize = 100>
class Stack {
    // Default constructor performs object
    // initialization for each element in array:
    T stack[ssize];
    int top;

public:
    Stack() : top(0) {}
    // Copy-constructor copies object into array:
    void push(const T &x)
    {
        require(top < ssize, "Too many push()es");
        stack[top++] = x;
    }
    T peek() const { return stack[top]; }
    // Object still exists when you pop it;
    // it just isn't available anymore:
    T pop()
    {
        require(top > 0, "Too many pop()s");
        return stack[--top];
    }
};
#endif // VALUESTACK_H ///:~