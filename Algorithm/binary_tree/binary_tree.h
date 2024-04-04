/*
 * 
 */

 // 定义二叉树结点
typedef struct BinaryTreeNode {
    int data;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
} BTreeNode;

// 创建二叉树节点
BTreeNode *CreateBTreeNode(int data);
// 释放二叉树节点
void FreeBTreeNode(BTreeNode *node);
// 创建二叉树
BTreeNode *CreateBTree(int arr[], int size);
// 释放二叉树
void FreeBTree(BTreeNode *root);
// 层次遍历二叉树
void LevelOrderTraversal(BTreeNode *root);
// 先序遍历二叉树
void PreorderTraversal(BTreeNode *root);