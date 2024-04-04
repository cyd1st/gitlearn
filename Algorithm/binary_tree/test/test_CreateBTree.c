#include <stdio.h>
#include <stdlib.h>
#include "../binary_tree.h"


void Test_CreateBTree() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(arr) / sizeof(arr[0]);

    BTreeNode* root = CreateBTree(arr, size);
    LevelOrderTraversal(root);
    printf("\n");
    return;
}

void Test_PreorderTraversal() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int size = sizeof(arr) / sizeof(arr[0]);

    BTreeNode* root = CreateBTree(arr, size);
    PreorderTraversal(root);
    printf("\n");
    return;
}

int main() {
    Test_CreateBTree();
    Test_PreorderTraversal();
    return 0;
}