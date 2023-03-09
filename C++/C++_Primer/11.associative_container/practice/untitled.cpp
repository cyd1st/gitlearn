#include <iostream>
#include <map>

using namespace std;

void map_add()
{
	map<int, int> m = {{1, 3},
		{2, 5},
		{4, 6}};
	map<int, int>::iterator it = m.begin();
	it->second = 1;
	cout << m[1] << endl;
}
int main()
{
	map_add();
	return 0;
}
