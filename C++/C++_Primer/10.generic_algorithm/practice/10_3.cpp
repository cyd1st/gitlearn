/* practice 10.3 & 10.4 & 10.5 */
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

/* p 10.3 */
void func1()
{
    vector<int> vi = {1,2,3,4,5,6,7,8,9};
    int res = accumulate(vi.cbegin(), vi.cend(), 0);
    cout << res << endl;
}
/* p 10.4 */
void func2()
{
    vector<double> vi = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
    double res = accumulate(vi.cbegin(), vi.cend(), 0);  // the double data will be convert to int type.
    cout << res << endl;
}
void func3()
{
    vector<double> vi = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
    double res = accumulate(vi.cbegin(), vi.cend(), 0.0);
    cout << res << endl;
}
/* p 10.5 */
void func4()
{
    vector<const char *> roster1 = {
        "Alice",
        "Bob",
        "Claier",
        "Dave"
    };
    vector<const char *> roster2 = {
        "Alice",
        "Bob",
        "Claier",
        "Dave",
        "Elia"
    };
    bool res = equal(roster1.cbegin(), roster1.cend(), roster2.cbegin());
    cout << res << endl;
}
int main()
{
    func1();
    func2();
    func3();
    func4();
    return 0;
}