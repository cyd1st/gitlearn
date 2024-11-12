/*
 In-order traversal of binaray search tree.
*/

#include <iostream>
#include <queue>

using namespace std;

struct TreeNode {
    int value;
    TreeNode *left, *right;
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

void InOrderTraversal(TreeNode *root)
{
    if (root == nullptr)
        return;
    InOrderTraversal(root->left);
    cout << root->value << " ";
    InOrderTraversal(root->right);
}

void LevelOrderTraversal(TreeNode *root)
{
    if (root == nullptr)
        return;
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode *t = q.front();
        cout << t->value << " ";
        if (t->left)
            q.push(t->left);
        if (t->right)
            q.push(t->right);
        q.pop();
    }
    cout << endl;
}

TreeNode *Search(TreeNode *root, int key)
{
    if (root == nullptr || root->value == key) {
        return root;
    }
    if (root->value < key) {
        return Search(root->right, key);
    }
    return Search(root->left, key);
}

// post-order traversal actually
void FreeTree(TreeNode *root)
{
    if (root == nullptr)
        return;
    FreeTree(root->left);
    FreeTree(root->right);
    delete root;
}

int main()
{
    // create bst
    TreeNode *root = new TreeNode(25);
    root->left = new TreeNode(15);
    root->right = new TreeNode(50);
    root->left->left = new TreeNode(10);
    root->left->right = new TreeNode(20);
    root->right->left = new TreeNode(35);
    root->right->right = new TreeNode(70);

    // in-order traversal
    InOrderTraversal(root);
    cout << endl;
    // level order traversal
    LevelOrderTraversal(root);

    TreeNode *target = Search(root, 10);
    cout << target->value << endl;

    // free the tree
    FreeTree(root);

    return 0;
}