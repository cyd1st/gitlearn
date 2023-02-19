#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

void sort_number()
{
    istream_iterator<int> input(cin);
    istream_iterator<int> eof;
    vector<int> vi;
    while (input != eof)
        vi.push_back(*input++);
    
    sort(vi.begin(), vi.end());
    ostream_iterator<int> output(cout, " ");
    for (auto i : vi)
        *output++ = i;
    cout << endl;
}
int main()
{
    sort_number();
    return 0;
}