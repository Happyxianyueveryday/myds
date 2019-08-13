#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include <iostream>
#include <vector>
#include "Tree.h"

using namespace std;

/**
 * TreeNode: �����������
 */
struct TreeNode: public Node
{
    public:
    TreeNode(int _val=0):Node(_val),left(NULL),right(NULL)
    {
    }
    TreeNode *left;    // ������ָ��
    TreeNode *right;   // ������ָ�� 
};

/** 
 * BinaryTree: �������������
 */
class BinaryTree: public Tree
{
	public:
    virtual vector<int> preorder() const = 0;      // ��������ǰ�����
    virtual vector<int> inorder() const = 0;       // ���������������
    virtual vector<int> postorder() const = 0;     // �������ĺ������
    virtual vector<int> levelorder() const = 0;    // �������Ĳ�α��� 
    virtual int size() const = 0;                  // �������Ľ�����
    virtual TreeNode *get(int val) const = 0;      // ���Ҷ������ĸ���ֵ�Ľ�� 
    virtual int maxpathsum() const = 0;            // �����������·����
    virtual int depth() const = 0;                 // �����������
    virtual int maxrlpath() const = 0;             // �������ĴӸ���㵽Ҷ�ӽ��ĺ͵����ֵ
    virtual TreeNode *lca(TreeNode *p, TreeNode *q) = 0;   // ���Ҷ���������������������������� 
    virtual ~BinaryTree() {}                       // ������������������
};

#endif
