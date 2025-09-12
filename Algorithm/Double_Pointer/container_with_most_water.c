/*
最大盛水容器
*/

#include <stdio.h>

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a > b ? b : a)

int MaxWater(int *array, int n)
{
    int area = 0;
    int left = 0, right = n - 1;
    while (left < right) {
        int curArea = (right - left) * MIN(array[left], array[right]);
        area = MAX(curArea, area);
        if (array[left] < array[right]) {
            left += 1;
        } else {
            right -= 1;
        }
    }
    return area;
}

/*--------------------------------------------------------------*/
// 测试用例结构
typedef struct {
    int *array;
    int n;
    int expected;
    const char *description;
} TestCase;

void runTest(TestCase test)
{
    int result = MaxWater(test.array, test.n);
    printf("测试: %s\n", test.description);
    printf("输入: [");
    for (int i = 0; i < test.n; i++) {
        printf("%d", test.array[i]);
        if (i < test.n - 1)
            printf(", ");
    }
    printf("]\n");
    printf("预期输出: %d, 实际输出: %d ", test.expected, result);
    if (result == test.expected) {
        printf("-> PASS\n\n");
    } else {
        printf("-> FAIL\n\n");
    }
}

int main()
{
    // 测试用例1: 标准示例
    int arr1[] = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    TestCase test1 = {arr1, 9, 49, "LeetCode示例 [1,8,6,2,5,4,8,3,7]"};

    // 测试用例2: 小数组
    int arr2[] = {1, 1};
    TestCase test2 = {arr2, 2, 1, "小数组 [1,1]"};

    // 测试用例3: 等高
    int arr3[] = {2, 2, 2};
    TestCase test3 = {arr3, 3, 4, "等高柱子 [2,2,2]"};

    // 测试用例4: 递减
    int arr4[] = {5, 4, 3, 2, 1};
    TestCase test4 = {arr4, 5, 6, "递减柱子 [5,4,3,2,1]"};

    // 测试用例5: 递增
    int arr5[] = {1, 2, 3, 4, 5};
    TestCase test5 = {arr5, 5, 6, "递增柱子 [1,2,3,4,5]"};

    // 测试用例6: 边际情况 - 小于2个元素
    int arr6[] = {5};
    TestCase test6 = {arr6, 1, 0, "单个元素 [5]"};

    // 测试用例7: 全零
    int arr7[] = {0, 0, 0};
    TestCase test7 = {arr7, 3, 0, "全零柱子 [0,0,0]"};

    // 运行测试
    runTest(test1);
    runTest(test2);
    runTest(test3);
    runTest(test4);
    runTest(test5);
    runTest(test6);
    runTest(test7);

    return 0;
}
