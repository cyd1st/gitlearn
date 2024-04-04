#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARR_LEN 15
#define MAX_NUM 21

int insert_sort(int* arr, int n)
{
	int i, j, temp;
	for(i = 1; i < n; i++) {
		temp = arr[i];
		for(j = i - 1; temp < arr[j] && j >= 0; j--)
		{
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = temp;
		
	}
	return 0;
}

int make_int_array(int int_arr[], int n, int m)
{
	srand((unsigned)time(NULL));
	for(int i = 0; i < n; i++) {
		int_arr[i] = rand() % m;
	}
	
	return 0;
}

int main()
{
	int rand_arr[ARR_LEN] = {0};
	int i = 0;
	
	make_int_array(rand_arr, ARR_LEN, MAX_NUM);
	
	printf("Before: [");
	for(i = 0; i < ARR_LEN; i++) {
		printf("%-4d", rand_arr[i]);
	}
	printf("]\n");
	
	insert_sort(rand_arr, ARR_LEN);
	
	printf(" After: [");
	for(i = 0; i < ARR_LEN; i++) {
		printf("%-4d", rand_arr[i]);
	}
	printf("]\n");
	
	return 0;
}

