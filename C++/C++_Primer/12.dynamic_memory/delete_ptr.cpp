#include <iostream>

using namespace std;

void deletePtr()
{
	double *dm = new double(10.01);
	double *dm2 = dm;
	int *im = nullptr;
	
	delete dm;
	delete dm2; // 未定义行为
	delete im;
}

int main()
{
	deletePtr();
	return 0;
}
