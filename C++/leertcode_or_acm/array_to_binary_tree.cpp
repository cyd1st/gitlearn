/*
	how to construct a binary tree by an array in ACM mode.
	Code from: https://programmercarl.com/%E5%89%8D%E5%BA%8F/ACM%E6%A8%A1%E5%BC%8F%E5%A6%82%E4%BD%95%E6%9E%84%E5%BB%BA%E4%BA%8C%E5%8F%89%E6%A0%91.html
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* construct_binary_tree(const vector<int>& vec) {
	vector<TreeNode*> vecTree(vec.size(), NULL);
	TreeNode* root = NULL;
	for (int i = 0; i < vec.size(); i++) {
		TreeNode *node = NULL;
		if (vec[i] != -1) node = new TreeNode(vec[i]);
		vecTree[i] = node;
		if (i == 0) root = node;
	}
	for (int i = 0; i * 2 + 1 < vec.size(); i++) {
		if (vecTree[i] != NULL) {
			vecTree[i]->left = vecTree[i*2+1];
			if (i*2+2 < vec.size()) {
				vecTree[i]->right = vecTree[i*2+2];
			}
		}
	}
	return root;
}

void print_binary_tree(TreeNode* root) {
	queue<TreeNode*> que;
	if (root != NULL) que.push(root);
	vector<vector<int>> result;
	while (!que.empty()) {
		int size = que.size();
		vector<int> vec;
		for (int i = 0; i< size; i++) {
			TreeNode* node = que.front();
			que.pop();
			if (node != NULL) {
				vec.push_back(node->val);
				que.push(node->left);
				que.push(node->right);
			} else {
				vec.push_back(-1);
			}
		}
		result.push_back(vec);
	}
	for (int i = 0; i < result.size(); i++) {
		for (int j = 0; j < result[i].size(); j++) {
			cout << result[i][j] << " ";
		}
		cout << endl;
	}
}

int main()
{
	vector<int> vec = {4,1,6,0,2,5,7,-1,-1,-1,3,-1,-1,-1,8};
	TreeNode* root = construct_binary_tree(vec);
	print_binary_tree(root);
	return 0;
}
