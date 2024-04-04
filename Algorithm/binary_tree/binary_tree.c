#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>

BTreeNode *CreateBTreeNode(int data) {
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    if (node == NULL) {
        fprintf(stderr, "Memoray allocate failed.\n");
        return NULL;
    }
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void FreeBTreeNode(BTreeNode *node) {
    free(node);
    node = NULL;
}

BTreeNode *CreateBTree(int arr[], int size) {
    if (arr == NULL || size <= 0) return NULL;

    // 创建队列, 并初始化
    BTreeNode **queue = (BTreeNode **)malloc(size * sizeof(BTreeNode *));
    if (queue == NULL) {
        fprintf(stderr, "Memory allocate faield.\n");
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        queue[i] = CreateBTreeNode(arr[i]);
        if (queue[i] == NULL) {
            // 如果节点创建失败，释放已分配的资源并返回NULL
            for (int j = 0; j < i; j++) {
                free(queue[j]);
            }
            return NULL;
        }
    }

    for (int i = 0; i < size; i++) {
        if (i * 2 + 1 >= size) break;
        if (i * 2 + 1 < size) {
            queue[i]->left = queue[i * 2 + 1];
        }
        if (i * 2 + 2 < size) {
            queue[i]->right = queue[i * 2 + 2];
        }
    }

    // 保存根节点
    BTreeNode *root = queue[0];
    // 释放节点队列指针，注意不要释放节点。
    free(queue);
    return root;
}

/**
 * 释放二叉树的所有节点内存。
 * @param root 指向二叉树根节点的指针。
 * 
 * 后序遍历二叉树。
 */
void FreeBTree(BTreeNode *root) {
    if (root == NULL) return;

    FreeBTree(root->left);
    FreeBTree(root->right);
    free(root);

    return;
}

/**
 * 层次遍历二叉树
 * @param root 二叉树的根节点
 * 
 * 二叉树最大节点数为 1000。
 *
 * 风险和可改进点：
 *  - 队列大小固定为 1000，不够通用。可优化为使用链表保存和记录节点。
 *  - 边界条件处理。通过if (queue[i] == NULL) break;来判断是否遍历结束，
 *    虽然在大多数情况下有效，但这种做法依赖于队列中的空节点作为循环终止条件，
 *    可能不够直观和健壮。
 *  - 数据打印方式。在遍历过程中直接打印数据，这可能不是最佳实践。
 *    在某些情况下，可能需要将结果收集起来，然后统一处理（如按键入文件、网络发送等）。
 */
void LevelOrderTraversal(BTreeNode *root) {
    if (root == NULL) return;

#define BTREE_MAX_NODES 1000
    BTreeNode **queue = (BTreeNode **)malloc(BTREE_MAX_NODES * sizeof(BTreeNode));
    if (queue == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return;
    }
    for (int i = 0; i < BTREE_MAX_NODES; i++) {
        queue[i] = NULL;
    }

    queue[0] = root;
    int index = 0;

    for (int i = 0; i < BTREE_MAX_NODES; i++) {
        if (queue[i] == NULL) break;
        
        if (queue[i]->left) queue[++index] = queue[i]->left;
        if (queue[i]->right) queue[++index] = queue[i]->right;

        printf("%d ", queue[i]->data);
    }

    free(queue);
    return;
#undef BTREE_MAX_NODES
}

void PreorderTraversal(BTreeNode *root) {
    if (root == NULL) return;

    printf("%d ", root->data);
    PreorderTraversal(root->left);
    PreorderTraversal(root->right);

    return;
}