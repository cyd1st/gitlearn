#include <stdio.h>

int main()
{
	int data = 15;
	size_t size = sizeof(++data);
	
	printf("%d, %zu\n", data, size);
	
	return 0;
}
