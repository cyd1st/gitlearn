#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("malloc(0): %p, malloc(-1): %p", malloc(0), malloc(-1));
	return 0;
}
