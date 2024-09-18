#include <iostream>
#include <memory>
#include "class_StrBlob.h"


using namespace std;

void test1()
{
	shared_ptr<string> p1;
	if (!p1) {
		*p1 = "Hello world.";
		cout << "p1 is null ptr." << endl;
	}
	if (p1->empty()) {
		cout << "p1 is empty ptr." << endl;
	}

}

void test2()
{
	shared_ptr<int> sp = make_shared<int>(42);
	shared_ptr<string> sps = make_shared<string>(10, '9');
	shared_ptr<int> p3 = make_shared<int>();
	auto p5 = make_shared<string>();
	cout << *sps << endl;
	cout << *sp << endl;
}

void test3()
{
	auto r = make_shared<string>("hello");
	auto q = make_shared<string>("World");
	r = q;
}

void test4()
{
	StrBlob sb;
	sb.push_back("hello world.");
	cout << sb.front() << endl;
	sb.pop_back();
	sb = {"ni", "hao"};
	cout << sb.back() << endl;
}

int main()
{
//	test1();
//	test2();
	test4();
	return 0;
}
