#include <iostream>

using namespace std;

int main()
{
	char ch;
	unsigned int aCnt = 0;
	unsigned int eCnt = 0;
	unsigned int iCnt = 0;
	unsigned int oCnt = 0;
	unsigned int uCnt = 0;

	while (cin >> ch) {
		switch (ch) {
		case 'a': case 'A':
			++aCnt;
			break;
		case 'e': case 'E':
			++eCnt;
			break;
		case 'i': case 'I':
			++iCnt;
			break;
		case 'o': case 'O':
			++oCnt;
			break;
		case 'u': case 'U':
			++uCnt;
			break;
			default:
				break;
		}
	}
	cout << "aCnt = " << aCnt << endl;
	cout << "eCnt = " << eCnt << endl;
	cout << "iCnt = " << iCnt << endl;
	cout << "oCnt = " << oCnt << endl;
	cout << "uCnt = " << uCnt << endl;
	return 0;
}