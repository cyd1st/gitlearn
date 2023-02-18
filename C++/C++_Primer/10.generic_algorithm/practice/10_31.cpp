#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

void sort_and_unique()
{
    istream_iterator<int> input(cin);
    istream_iterator<int> eof;
    vector<int> vi;
    while (input != eof)
        vi.push_back(*input++);
    
    sort(vi.begin(), vi.end());
    auto it_end = unique(vi.begin(), vi.end());

    ostream_iterator<int> out(cout, " ");
    for (auto it = vi.begin(); it != it_end; ++it)
        *out++ = *it;

    cout << endl;
}

int main()
{
    sort_and_unique();
    return 0;
}