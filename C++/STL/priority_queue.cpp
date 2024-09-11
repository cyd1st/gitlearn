#include <iostream>
#include <queue>
#include <vector>

int main() {
    // 创建一个大顶堆
    std::priority_queue<int> maxHeap;

    // 向大顶堆中添加元素
    maxHeap.push(10);
    maxHeap.push(30);
    maxHeap.push(20);
    maxHeap.push(5);
    maxHeap.push(1);

    // 输出大顶堆的顶部元素（最大元素）
    std::cout << "大顶堆的顶部元素（最大元素）: " << maxHeap.top() << std::endl;

    // 创建一个小顶堆
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

    // 向小顶堆中添加元素
    minHeap.push(10);
    minHeap.push(30);
    minHeap.push(20);
    minHeap.push(5);
    minHeap.push(1);

    // 输出小顶堆的顶部元素（最小元素）
    std::cout << "小顶堆的顶部元素（最小元素）: " << minHeap.top() << std::endl;

    return 0;
}

