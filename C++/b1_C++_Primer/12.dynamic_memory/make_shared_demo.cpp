#include <iostream>
#include <memory>
#include <vector>

using namespace std;

int main()
{
    shared_ptr<int> p1 = make_shared<int>(12); // 12
    shared_ptr<string> p2 = make_shared<string>(10, '9'); // 10个9
    shared_ptr<int> p3 = make_shared<int>();              // 0
    auto p4 = make_shared<vector<string>>();
}