#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	vector<string> vs;
	vector<string>::const_iterator it;
	string s;
	for (int i = 0 ; i < 5; i++) {
		cin >> s;
		vs.push_back(s);
	}
	it = vs.cbegin();
	for (;it != vs.cend();++it) {
#ifndef NDEBUG
		cout << it->size() << endl;
#endif
	}
	return 0;
}