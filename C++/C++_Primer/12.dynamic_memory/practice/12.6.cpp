#include <vector>
#include <iostream>
using namespace std;

vector<int> *create_vector_int()
{
	vector<int> *vi = new vector<int>(10);
	return vi;
}

void input_vector(vector<int> *vi)
{
	int i, j = 0;
	while (cin >> i) {
		(*vi)[j++] = i;
	}
}

void print_vector(vector<int> *vi)
{
	for (auto i : *vi) {
		cout << i << " ";
	}
	cout << endl;
}

int main()
{
	auto p = create_vector_int();
	input_vector(p);
	print_vector(p);
	return 0;
}
