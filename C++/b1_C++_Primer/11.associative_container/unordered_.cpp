#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

typedef struct salseDataStruct{
	int count;
	string isbn;
} Sale_data;

size_t hasher(const Sale_data &sd)
{
	return hash<string>() (sd.isbn);
}

bool eqOp(const Sale_data &sd1, const Sale_data &sd2)
{
	return sd1.isbn > sd2.isbn;
}

void custom_set()
{
	using sd_multiset = unordered_set<Sale_data, decltype(hasher)*, decltype(eqOp)*>;
	sd_multiset bookstore(42, hasher, eqOp);
}

void test_unordered_map()
{
	unordered_map<int, string> um;
	um[1] = "1";
	um[2] = "2";
	um[3] = "3";
	um[4] = "4";
	um[5] = "5";
	cout << "正在使用的桶的数量:" << um.bucket_count() << endl;
	cout << "容器能容纳的最多桶数量:" << um.max_bucket_count() << endl;
	cout << "第1个桶中有多少元素:" << um.bucket_size(1) << endl;
}
int main()
{
	test_unordered_map();
	return 0;
}
