#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<int> vi{1,2,3,4,5,6,7,8,9,10,11};
	for(auto &i : vi) {
		if (i % 2) {
			cout << i << " ";
			i *= 2;
		}
	}
	cout << endl;
	for (auto j : vi) {
		cout << j << " ";
	}
	cout << endl;
	
	return 0;
}