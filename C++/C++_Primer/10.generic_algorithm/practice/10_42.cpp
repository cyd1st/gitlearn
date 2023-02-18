#include <algorithm>
#include <iostream>
#include <list>
#include <string>

using namespace std;

void list_unique()
{
    list<string> ls = {
        "list",
        "vector",
        "list",
        "forward_list",
        "array",
        "string",
        "string",
        "array"
    };
    ls.sort();
    ls.unique();
    for (auto &s : ls) {
        cout << s << endl;
    }
    cout << endl;
}
int main()
{
    list_unique();
    return 0;
}