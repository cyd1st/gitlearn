/*
 * @Descripttion: 删除排序数组中的重复项
 * @Author: cyD
 * @Date: 2021-08-05 00:43:31
 * @LastEditTime: 2021-08-05 00:47:19
 */

#include <stdio.h>

int removeDuplicates(int *nums, int numsSize);

int main()
{
	int numarray[8] = {1, 2, 3, 3, 4, 5, 5, 5};
	int size = 0;
	size = removeDuplicates(numarray, 8);

	printf("%d\n", size);
	for (int i = 0; i < size; i++) {
		printf("%d ", numarray[i]);
	}
}

int removeDuplicates(int *nums, int numsSize)
{
	if (numsSize == 0)
		return numsSize;
	int *p1 = nums, *p2 = nums + 1;
    int num = 1;
	for (int i = 0; i < numsSize - 1; i++, p2++) {
		if (*p1 == *p2) {
			continue;
		} else {
			p1++;
            *p1 = *p2;
            num++;
		}
	}
	
	return num;
}
 
/**
 *  重点是双指针法，想到就简单
 */