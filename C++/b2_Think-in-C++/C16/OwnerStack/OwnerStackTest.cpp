//{L} AutoCounter
#include "OwnerStack.h"
#include <iostream>
#include "../../lib/require.h"
#include "../TPStash/AutoCounter.h"
using namespace std;

// 该案例需要和 TPStash 对比，可以看出所有权的效果
int main()
{
    Stack<AutoCounter> ac;         // Ownership on
    Stack<AutoCounter> ac2(false); // Turn it off
    AutoCounter *ap;
    for (int i = 0; i < 10; i++) {
        ap = AutoCounter::create();
        ac.push(ap);
        if (i % 2 == 0)
            ac2.push(ap);
    }
    while (ac2)
        cout << ac2.pop() << endl;
    // No destruction necessary since
    // ac "owns" all the objects
} ///:~