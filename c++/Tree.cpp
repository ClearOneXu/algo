//#include <stdlib.h>
//#include <stdio.h>
//#include <atomic>
//#include <iostream>
//#include <map>
//#include <queue>
//using namespace std;
//
////二叉树遍历框架，典型的非线性递归遍历结构：
///* 基本的二叉树节点 */
//typedef struct TreeNode {
//    int val;
//    TreeNode *left, *right;
//    TreeNode() = default;
//    TreeNode(const int & element){
//        val = element;
//        left = right = nullptr;
//    }
//} BTNode, BSTNode;
//
//
///**
// 二叉树
// */
//
////查找 find
//void traverse(BTNode *root) {
//    if (root == nullptr) return;
//    // 前序遍历
//    traverse(root->left);
//    // 中序遍历
//    traverse(root->right);
//    // 后序遍历
//}
//void level_traverse(BTNode *root, queue<int> q) {
//    if (root == nullptr){
//        q.push(-1);
//        return;
//    }
//    q.push(root->val);
//    level_traverse(root->left, q);
//    level_traverse(root->right, q);
//}
//
////Leetcode 124 Binary Tree Maximum Path Sum 最大路径和
////路径被定义为一条从树中任意节点出发，达到任意节点的序列。该路径至少包含一个节点，且不一定经过根节点。
//int maxValue = INT_MIN;
//int maxPath(TreeNode* root) {
//    if (root == nullptr) return 0;
//    int left = maxPath(root->left);
//    int right = maxPath(root->right);
//    int currentMax = max(root->val, root->val + max(left, right));
//    maxValue = max(maxValue, max(currentMax, root->val + left + right));
//    return currentMax;
//}
///**Leetode 105 Construct Binary Tree from Preorder and Inorder Traversal
//  给出 2 个数组，根据 preorder 和 inorder 数组构造一颗树。利用递归思想，从 preorder 可以得到根节点，从 inorder 中得到左子树和右子树。只剩一个节点的时候即为根节点。不断的递归直到所有的树都生成完成。
//    左中右 中左右  **/
//TreeNode *buildTree (int preorder[], int preStart, int preEnd, int inorder[], int inStart, int inEnd, map<int, int> inMap) {
//    if(preStart > preEnd || inStart > inEnd) return nullptr;
//    TreeNode *root = new TreeNode(preorder[preStart]);
//    int inRoot = inMap[root->val];
//    int numsLeft = inRoot - inStart;
//    root->left = buildTree(preorder, preStart + 1, preStart + numsLeft,
//                          inorder, inStart, inRoot - 1, inMap);
//    root->right = buildTree(preorder, preStart + numsLeft + 1, preEnd,
//                          inorder, inRoot + 1, inEnd, inMap);
//    return root;
//}
//
//
//
///**
// BST 二叉搜索树
// */
//
////是否为Valid BST
//bool isValidBST(BSTNode* root, int min, int max) {
//    if (root == nullptr) return true;
//    if (root->val <= min) return false;
//    if (root->val >= max) return false;
//    return isValidBST(root->left, min, root->val)
//        && isValidBST(root->right, root->val, max);
//}
//bool isValidBST(BSTNode* root) {
//    return isValidBST(root,INT_MIN, INT_MAX);
//}
////二叉搜索树查找
//BSTNode* BSTFind(BSTNode *root, int val) {
//    BSTNode *node = root;
//    while (node != nullptr) {
//        if (val < node->val)
//            node = node->left;
//        else if (val > node->val)
//            node = node->right;
//        else
//            return node;
//    }
//    return nullptr;
//}
////回溯
//bool isInBST(BSTNode* root, int target) {
//    if (root == nullptr) return false;
//    if (root -> val > target)
//        return isInBST(root->left, target);
//    else if (root -> val < target)
//        return isInBST(root->right, target);
//    else
//        return true;
//}
////二叉搜索树插入
//void BSTInsert(BSTNode *root, int val) {
//    if (root == nullptr) {
//        root = new BSTNode(val);
//        return;
//    }
//    BSTNode *p = root;
//    while(p != nullptr) {
//        if(p->val > val) {
//            p = p->left;
//        }
//        else if (p->val < val) {
//            p = p->right;
//        }
//        else {
//            return;
//        }
//    }
//    p = new BSTNode(val);
//    return;
//}
////回溯
//BSTNode* insertBST(BSTNode* root, int target) {
//    if (root == nullptr) return new BSTNode(target);
//    if (root -> val > target)
//        root->left = insertBST(root->left, target);
//    else if (root -> val < target)
//        root->right = insertBST(root->right, target);
//    return root;
//}
////二叉搜索树删除
////1. 只有0个/单个子树 2. 有两个子树
//void BSTDelete(BSTNode *root, int val) {
//    BSTNode* prev = nullptr;
//    BSTNode* node = root; //要删除的节点
//    while (node != nullptr && node->val != val) {
//        prev = node;
//        if (val < node->val) {
//            node = node->left;
//        }
//        else if (val > node->val) {
//            node = node->right;
//        }
//    }
//    if (node ==  nullptr) return;
//    //要删除的节点有两个⼦节点
//    if (node->left != nullptr && node->right != nullptr) { //查找最小右节点
//        BSTNode* minR = node->right;
//        BSTNode* minR_prev = node;
//        while (minR->left != nullptr) {
//            minR_prev = minR;
//            minR = minR->left;
//        }
//        node->val = minR->val;
//        node = minR; //变成删除只有一个或0个子树的操作
//        prev = minR_prev;
//    }
//    // 删除节点是叶⼦节点或者仅有⼀个⼦节点
//    BSTNode* child; // p的⼦节点
//    if (node->left != nullptr) child = node->left;
//    else if (node->right != nullptr) child = node->right;
//    else child = nullptr;
//    
//    if (prev == nullptr) root = child; // 删除的是根节点
//    else if (prev->left == node) prev->left = child;
//    else prev->right = child;
//}
////回溯
//BSTNode* deleteBST(BSTNode* root, int target) {
//    if (root == nullptr) return root;
//    if (root->val == target) {
//        //删除
//        //if (root->left == nullptr && root->right == nullptr) return nullptr;
//        if (root->left == nullptr) return root->right;
//        if (root->right == nullptr) return root->left;
//        // 找到右子树的最小节点
//        // 把 root 改成 minNode
//        // 转而去删除 minNode root.right = deleteNode(root.right, minNode.val);
//    }
//    else if (root -> val > target)
//        root->left = deleteBST(root->left, target);
//    else if (root -> val < target)
//        root -> right = deleteBST(root->right, target);
//    return root;
//}
//
///** Leetcode 99. Recover Binary Search Tree
// 在二叉搜索树中，有 2 个结点的值出错了，要求修复这两个结点。
// 本质：左中右搜索 **/
//void inOrderTraverse(BSTNode* node, BSTNode* prev, BSTNode* s, BSTNode* t) {
//    if (!node) return;
//    inOrderTraverse(node->left,prev,s,t);
//    if (prev != nullptr && (node->val < prev->val)) {
//        s = (s == nullptr) ? prev : s;
//        t = node;
//    }
//    prev = node;
//    inOrderTraverse(node->right,prev,s,t);
//}
//void recoverTree(BSTNode *root) {
//    BSTNode *prev, *target1, *target2;
//    prev = target1 = target2 = nullptr;
//    inOrderTraverse(root, prev, target1, target2);
//    if (target1 != nullptr && target2 != nullptr) {
//        auto temp = target1->val;
//        target1->val = target2->val;
//        target2->val = temp;
//    }
//}
//
///**
// LeetCode 96. Unique Binary Search Trees 动态规划
// 给定一个整数 n，求以 1 … n 为节点组成的二叉搜索树有多少种？
// */
//int numTrees(int n) {
//    int dp[n+1];
//    dp[0] = dp[1] = 1;
//    for (int i = 0; i < n; i++) {
//        for (int j = 1; j <= i; j++) {
//            dp[i] += dp[j-1] * dp[i-j];
//        }
//    }
//    return dp[n];
//}
////回溯
//int numTrees2(int i) {
//    if (i == 0 || i == 1) return 1;
//    int nums = 0;
//    for (int j = 1; j <= i; j++) {
//        nums += numTrees2(j-1)*numTrees2(i-j);
//    }
//    return nums;
//}
//
//
//
//
