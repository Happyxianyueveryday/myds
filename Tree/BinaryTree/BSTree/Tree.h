#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <string>

using namespace std;

/**
 * 树结点基类
 */
struct Node
{
    public:
    Node(int _val=0):val(_val)
    {
    }
    int val;
};

/**
 * Tree: 树的抽象基类
 */
class Tree
{
    public:
    virtual void insert(int val) = 0;              // 向树中插入结点
    virtual void remove(int val) = 0;              // 从树中删除结点
    virtual bool exist(int val) const = 0;         // 在树中查找给定值的结点是否存在 
    virtual ~Tree() {}                             // 树的虚析构函数
};

#endif
