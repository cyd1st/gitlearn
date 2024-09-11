/*AI生成，略作修改*/
#include <iostream>
#include <new>
#include <stdexcept>
#include <vector>
#include <algorithm> // For std::swap

class MaxHeap {
public:
    MaxHeap() {}

    // 插入元素到堆中
    void push(int value) {
        heap.push_back(value); // 先将新元素添加到数组末尾
        siftUp(heap.size() - 1); // 调整堆，使新元素处于正确的位置
    }

    // 获取并移除堆顶元素
    int pop() {
        if (heap.empty())
            throw std::out_of_range("Heap is empty."); // 错误标记或抛出异常
        int root = heap.front();
        std::swap(heap.front(), heap.back()); // 交换堆顶元素与最后一个元素
        heap.pop_back(); // 移除最后一个元素
        siftDown(0); // 调整堆，使新堆顶元素处于正确的位置
        return root;
    }

    // 获取堆顶元素
    int top() const {
        if (heap.empty()) 
            throw std::out_of_range("Heap is empty."); // 错误标记或抛出异常
        return heap.front();
    }

    // 层次遍历打印堆
    void levelOrderTraversal() const {
        for (size_t i = 0; i < heap.size(); ++i) {
            std::cout << heap[i] << " ";
        }
        std::cout << std::endl;
    }

private:
    std::vector<int> heap;

    // 向上调整元素，以确保堆的性质
    void siftUp(size_t index) {
        while (index > 0) { // 当前节点不是根节点
            size_t parent = (index - 1) / 2; // 计算父节点的索引
            if (heap[parent] >= heap[index]) break; // 如果父节点大于等于当前节点，则不需要交换
            std::swap(heap[parent], heap[index]); // 否则交换当前节点与父节点
            index = parent; // 更新当前节点为父节点
        }
    }

    // 向下调整元素，以确保堆的性质
    void siftDown(size_t index) {
        size_t largest = index; // 初始化当前节点为最大值
        size_t leftChild = 2 * index + 1; // 计算左子节点的索引
        size_t rightChild = 2 * index + 2; // 计算右子节点的索引 

        // 检查左节点是否存在，并且是否比当前节点大
        if (leftChild < heap.size() && heap[leftChild] > heap[largest])
            largest = leftChild;

        // 检查右子节点是否存在，并且是否比当前节点大
        if (rightChild < heap.size() && heap[rightChild] > heap[largest])
            largest = rightChild;

        // 如果当前节点（index）不是最大值，则交换，并继续向下调整
        if (largest != index) {
            std::swap(heap[index], heap[largest]);
            siftDown(largest);
        }
    }
};

int main() {
    MaxHeap maxHeap;
    maxHeap.push(3);
    maxHeap.push(1);
    maxHeap.push(5);
    maxHeap.push(2);
    maxHeap.push(2);
    maxHeap.push(4);

    std::cout << "Initial Heap: ";
    maxHeap.levelOrderTraversal(); // 打印层次遍历结果

    std::cout << "Pop top element: " << maxHeap.top() << std::endl;
    maxHeap.pop();
    std::cout << "After pop: ";
    maxHeap.levelOrderTraversal(); // 打印层次遍历结果

    return 0;
}