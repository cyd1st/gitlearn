#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	int a, b;
	while (cin >> a >> b) {
		try {
			if (b == 0) {
				throw runtime_error("can't devide zero.");
			}
			cout << "a / b = " << a / b << endl;
		} catch (runtime_error err) {
			cout << err.what() << "\ninput again(yes or not)? " << endl;
			string again;
			cin >> again;
			if (again != "yes") break;
		}
	}
	
	return 0;
}