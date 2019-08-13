#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include <iostream>
#include <vector>
#include "Tree.h"

using namespace std;

/**
 * TreeNode: 二叉树结点类
 */
struct TreeNode: public Node
{
    public:
    TreeNode(int _val=0):Node(_val),left(NULL),right(NULL)
    {
    }
    TreeNode *left;    // 左子树指针
    TreeNode *right;   // 右子树指针 
};

/** 
 * BinaryTree: 二叉树抽象基类
 */
class BinaryTree: public Tree
{
	public:
    virtual vector<int> preorder() const = 0;      // 二叉树的前序遍历
    virtual vector<int> inorder() const = 0;       // 二叉树的中序遍历
    virtual vector<int> postorder() const = 0;     // 二叉树的后序遍历
    virtual vector<int> levelorder() const = 0;    // 二叉树的层次遍历 
    virtual int size() const = 0;                  // 二叉树的结点个数
    virtual TreeNode *get(int val) const = 0;      // 查找二叉树的给定值的结点 
    virtual int maxpathsum() const = 0;            // 二叉树的最大路径和
    virtual int depth() const = 0;                 // 二叉树的深度
    virtual int maxrlpath() const = 0;             // 二叉树的从根结点到叶子结点的和的最大值
    virtual TreeNode *lca(TreeNode *p, TreeNode *q) = 0;   // 查找二叉树给定两个结点的最近公共祖先 
    virtual ~BinaryTree() {}                       // 二叉树的虚析构函数
};

#endif
