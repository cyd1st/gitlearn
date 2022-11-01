#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

long long fib1(int i) {
	if (i <= 0) return 0;
	if (i == 1) return 1;
	return fib1(i - 1) + fib1(i - 2);
}

long long fib2(long long first, long long second, int n) {
	if (n <= 0) return 0;
	if (n <= 2) return 1;
	if (n == 3) return first + second;
	return fib2(second, first + second, n - 1);
}

int main()
{
	int n;
	cin >> n;
	milliseconds start_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	while (n--) {
		fib2(1, 1, n);
//		fib1(n);
	}
	milliseconds end_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

	cout << "耗时：" << milliseconds(end_time).count() - milliseconds(start_time).count() << " ms" << endl;

	return 0;
}
