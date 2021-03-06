/* 94. Binary Tree Inorder Traversal
Medium

Given a binary tree, return the inorder traversal of its nodes' values.

Example:

Input: [1,null,2,3]
   1
    \
     2
    /
   3

Output: [1,3,2]

Follow up: Recursive solution is trivial, could you do it iteratively?
Accepted
505,525
Submissions
873,217
 */

#include <bits/stdc++.h>

using namespace std;

/* Definition for a binary tree node. */
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/* Recursive */
class Solution {
public:
    void inorderTraversalEx(TreeNode* root) {
        if (!root)
            return;
        if (root->left)
            inorderTraversalEx(root->left);
        trav.push_back(root->val);
        if (root->right)
            inorderTraversalEx(root->right);
    }
    vector<int> inorderTraversal(TreeNode* root) {
        trav.clear();
        inorderTraversalEx(root);
        //return std::move(trav); // 4ms
        return trav; // 0ms
    }
    vector<int> trav;
};

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
/* Iterative */
class Solution {
public:

    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> trav;
        deque<TreeNode *> que;
        TreeNode *node = root;
        while (node) {
            que.push_back(node);
            node = node->left;
        }
        while(!que.empty()) {
            TreeNode *node = que.back();
            que.pop_back();
            trav.push_back(node->val);
            node = node->right;
            while (node) {
                que.push_back(node);
                node = node->left;
            }
        }
        return trav; // 0ms
    }
};

