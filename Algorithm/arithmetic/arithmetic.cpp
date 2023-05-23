#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// Reverse Polish notation
string rpn(const string &in)
{
	string rpn;
	vector<char> vc;
	unordered_map<char, int> opr_pri;
	opr_pri['('] = 0;
	opr_pri[')'] = 10;
	opr_pri['+'] = 1;
	opr_pri['-'] = 1;
	opr_pri['*'] = 2;
	opr_pri['/'] = 2;
	
	for (auto &c : in) {
		if (isspace(c)) { // 空格跳过
			continue;
		}
		if (isdigit(c)) {
			rpn.push_back(c);
			continue;
		}
		if (vc.empty()) {
			vc.push_back(c);
			continue;
		}
		if (c == '(') {
			vc.push_back(c);
			continue;
		}
		if (c == ')') {
			while (vc.back() != '(') {
				rpn.push_back(vc.back());
				vc.pop_back();
			}
			if (vc.back() == '(') {
				vc.pop_back();
			}
			continue;
		}
		while (!vc.empty() && opr_pri[vc.back()] >= opr_pri[c]) {
			rpn.push_back(vc.back());
			vc.pop_back();
		}
		vc.push_back(c);
	}
	while (!vc.empty()) {
		rpn.push_back(vc.back());
		vc.pop_back();
	}
	return rpn;
}

int main()
{
	string test1 = "2 *9+3-2*(10-3)/14";
	string rest1 = rpn(test1);
	cout << rest1 << endl;
	return 0;
}
