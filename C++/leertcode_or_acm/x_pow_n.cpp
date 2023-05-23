/*
	calculate x to the nth power.
	from:https://programmercarl.com/%E5%89%8D%E5%BA%8F/%E9%80%9A%E8%BF%87%E4%B8%80%E9%81%93%E9%9D%A2%E8%AF%95%E9%A2%98%E7%9B%AE%EF%BC%8C%E8%AE%B2%E4%B8%80%E8%AE%B2%E9%80%92%E5%BD%92%E7%AE%97%E6%B3%95%E7%9A%84%E6%97%B6%E9%97%B4%E5%A4%8D%E6%9D%82%E5%BA%A6%EF%BC%81.html
	function1: O(logn)
	function2: O(n)
*/

#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

long long function1(int x, int n){
	if (n == 0) return 1;
	long long t = function1(x, n/2);
	if (n%2 == 1) {
		return t * t * x;
	}
	return t * t;
}

long long function2(int x, int n) {
	if (n == 0) {
		return 1; // return 1 同样是因为0次方是等于1的
	}
	return function2(x, n - 1) * x;
}

int main()
{
	milliseconds start_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	int n = 10000000;
	while (n--) {
		long long a = function1(2, 10);
	}
	
//	cout << "结果：" << a << endl;
	milliseconds end_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	
	cout << "耗时：" << milliseconds(end_time).count() - milliseconds(start_time).count() << " ms" << endl;
	
	return 0;
}
