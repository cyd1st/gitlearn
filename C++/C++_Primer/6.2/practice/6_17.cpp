#include <iostream>
#include <string>

using namespace std;
bool isUpperCase(const string &s);
void toLowerCase(string &s);

int main()
{
	string s;
	cin >> s;
	if (isUpperCase(s)) {
		cout << "r: ";
		toLowerCase(s);
	}
	cout << s << endl;
	return 0;
}

bool isUpperCase(const string &s)
{
	for (auto c : s) {
		if (isupper(c)) {
			return true;
		}
	}
	return false;
}

void toLowerCase(string &s)
{
	for (auto &c : s) {
		c = tolower(c);
	}
}
