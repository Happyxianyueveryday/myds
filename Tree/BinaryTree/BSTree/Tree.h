#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <string>

using namespace std;
 
/**
 * ��������
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
 * Tree: ���ĳ������
 */
class Tree
{
    public:
    virtual void insert(int val) = 0;              // �����в�����
    virtual void remove(int val) = 0;              // ������ɾ�����
    virtual bool exist(int val) const = 0;         // �����в��Ҹ���ֵ�Ľ���Ƿ���� 
    virtual ~Tree() {}                             // ��������������
};

#endif
