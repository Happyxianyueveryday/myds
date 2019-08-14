#ifndef THREADTREE_H
#define THREADTREE_H
#include <iostream>
#include <string>
#include <vector> 

using namespace std;

struct ThreadNode 
{
	public:   // ��ȻstructĬ�Ͽɼ��Ծ���public���������Ƽ�д��� 
	ThreadNode(int _val): val(_val), lflag(false), rflag(false), left(NULL), right(NULL)
	{
	}
	int val;
	ThreadNode *left;
	ThreadNode *right;
	bool lflag;     // true��ʾleftָ��ָ������е���һ����㣬false��ʾleftָ��ָ�������� 
	bool rflag;
};

class ThreadTree
{
	public:
	virtual ThreadNode *getFirstNode(ThreadNode *now);
	virtual ThreadNode *getLastNode(ThreadNode *now);
	virtual ThreadNode *getNextNode(ThreadNode *now);
	virtual ThreadNode *getPrevNode(ThreadNode *now);
	virtual vector<int> traversal();
	virtual ~ThreadTree() { } 
};

ThreadNode *ThreadTree::getFirstNode(ThreadNode *now)
{
	return NULL;
}

ThreadNode *ThreadTree::getLastNode(ThreadNode *now)
{
	return NULL;
}

ThreadNode *ThreadTree::getNextNode(ThreadNode *now)
{
	return NULL;
}

ThreadNode *ThreadTree::getPrevNode(ThreadNode *now)
{
	return NULL;
}

vector<int> ThreadTree::traversal()
{
	vector<int> res;
	return res;
}

#endif
