#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
#include "Tree.h"

using namespace std;


struct ThreadNode
{
    ThreadNode(int ival=0):val(ival),left(NULL),right(NULL),lflag(0),rflag(0)
    {
    }

    int val;
    ThreadNode *left;
    ThreadNode *right;
    int lflag;
    int rflag;
};


/*
 * ThreadPostTree: 后序遍历的二叉搜索线索树
 * note 1: 在普通二叉树中，可能存在许多的结点只有左子结点或者右子结点，或者是叶子结点，这时该结点中left和right成员就处于空置状态
 * note 2: 为了在左子结点/右子结点为空的情况下利用left和right成员，规定:当左子结点为空时，使用left字段记录当前结点在后序遍历时的前驱结点，当右子结点为空时，使用right字段记录当前结点在后序遍历时的后继结点，并额外新增lflag和rflag表明left字段和right字段指向的是前后驱结点还是左右子结点，这就构成了后序遍历二叉线索树
*/
class ThreadPostTree
{
	public:
	// 1. 构造函数
	ThreadPostTree();                                                      // 默认构造函数
	ThreadPostTree(const Tree &other);                                     // 从普通二叉搜索树生成对应的线索树

	// 2. 拷贝控制
	ThreadPostTree(const ThreadPostTree &other);                               // 拷贝构造函数
	ThreadPostTree & operator = (const ThreadPostTree &other) = delete;        // 禁止拷贝赋值运算符的使用

	// 3. 功能函数: 重点注意线索树的两种基本操作getFirstNode和getNextNode
	vector<int> reverse_postorder();                                           // 获取当前线索树倒序的后序遍历序列，该算法应用上述两个基本操作进行实现

	// 4. 析构函数
	~ThreadPostTree();

	private:
	ThreadNode *treeroot;     // 线索树的根结点

	ThreadNode *__copyTree(TreeNode *root);                              // 从二叉搜索树拷贝一个线索树的底层递归实现

	// 5. 二叉线索树的四种基本操作
	ThreadNode *getFirstNode(ThreadNode *root);               // 线索树基本操作1: 获取给定的线索树后序遍历序列中的第一个结点
	ThreadNode *getPrevNode(ThreadNode *pos);                 // 线索树基本操作2: 获取在后序遍历中当前结点的前驱结点
	ThreadNode *getLastNode (ThreadNode *root);               // 线索树基本操作3: 获取给定的线索树后序遍历序列中的最后一个结点

	// important note: 基于后序遍历的二叉线索树不能实现获取给定结点在后序遍历中的后继结点的操作，只有基于中序遍历的二叉线索树可以实现全部的四种操作
	// note: 简单解释一下为什么基于后序遍历的二叉线索树不能实现获取前驱结点的操作，因为后序遍历中，是先输出左子结点和右子结点，然后输出根结点；因此当拿到当前结点时，仅能知道在当前结点之前需要输出右子树，即后继结点是右子树的后序遍历的最后一个结点，但是不知道当前结点的后继结点（因为当前结点是最后输出的）
	// note: 而在基于中序遍历的二叉线索树中，根据中序遍历的定义，对于每个结点，在访问当前结点之前一定先访问了左子树，在访问该结点之后一定后访问了右子树，因此既可以求前驱结点也可以求后继结点，能够完全实现全部四种线索树操作
	//ThreadNode *getNextNode(ThreadNode *pos);                 // 线索树基本操作4：获取在后序遍历中当前结点的后继结点
};


/**
 * ThreadPostTree: 构造一个空的后序二叉线索树
 */
ThreadPostTree::ThreadPostTree()
{
	treeroot=NULL;
}


/**
 * ThreadPostTree: 从一个二叉树构造一个后序二叉搜索树
 */
ThreadPostTree::ThreadPostTree(const Tree &other)
{
	// 1. 首先从输入的源二叉搜索树进行深拷贝，得到一个二叉搜索树
	treeroot=__copyTree(other.getroot());

	// 2. 然后进行二叉树的后序线索化
	vector<ThreadNode *> res;
	stack<ThreadNode *> sta;

	if(!treeroot)
		return;

	sta.push(treeroot);

	while(sta.size())
	{
		ThreadNode *now=sta.top();
		res.push_back(now);

		sta.pop();

		if(now->left)
			sta.push(now->left);
		if(now->right)
			sta.push(now->right);
	}

	reverse(res.begin(), res.end());

	for(int i=0;i<res.size();i++)
	{
		if(!res[i]->left)
		{
			res[i]->lflag=1;

			if(i!=0)
				res[i]->left=res[i-1];
			else
				res[i]->left=NULL;
		}
		if(!res[i]->right)
		{
			res[i]->rflag=1;

			if(i!=res.size()-1)
				res[i]->right=res[i+1];
			else
				res[i]->right=NULL;
		}
	}

	return;
}

ThreadNode *ThreadPostTree::__copyTree(TreeNode *root)
{
	if(!root)
	return NULL;
	else
	{
		ThreadNode *now=new ThreadNode(root->val);
		now->left=__copyTree(root->left);
		now->right=__copyTree(root->right);

		return now;
	}
}


/**
 * getFirstNode: 获取线索树的后序遍历中的第一个结点
 * param root: 输入的线索树的根结点
 * return: 输入线索树的后序遍历的首结点
 * note: 一个线索二叉树的后序遍历中，第一个结点一定是整个树的最左侧的结点，因此一直沿着左子结点的方向进行访问，路径上的最后一个结点就是后序遍历中的第一个结点
 */
ThreadNode *ThreadPostTree::getFirstNode(ThreadNode *root)
{
	ThreadNode *now=root;

	while(now->lflag==0)
	{
		now=now->left;
	}

	return now;
}


/**
 * getNextNode: 获取线索树的后序遍历中给定结点的前驱结点
 * param pos: 给定的输入结点
 * return: 输入结点在后序遍历中的前一个结点，即前驱结点
 * note: 从后序遍历的定义可知，后序遍历访问当前结点之前，首先需要访问左子树，然后访问右子树，最后访问当前结点，因此:
 * 		 (1) 若当前结点存在右子树，即root->rflag==0，则当前结点在后序遍历中的前驱结点就是右子树的后序遍历的最后一个结点，故返回getLastNode(root->right)
 * 		 (2) 若当前结点不存在右子树,即root->rflag==1:
 * 		     (a) 在情况(2)下，若当前结点不存在左子树，即root->lflag==1，则这时根据线索树的定义，root->left指向当前结点在后序遍历中的前驱结点，故返回root->left
 * 		     (b) 在情况(2)下，若当前结点存在左子树，即root->lflag==0，则这时当前结点在后序遍历中的前驱结点就是左子树的后序遍历的最后一个结点，故返回getLastNode(root->left)
 */
ThreadNode *ThreadPostTree::getPrevNode(ThreadNode *pos)
{
	if(pos->rflag==0)
		return getLastNode(pos->right);
	else
	{
		if(pos->lflag==0)
			return getLastNode(pos->left);
		else
			return pos->left;
	}
}


/**
 * getLastNode: 获取线索树的后序遍历中的最后一个结点
 * param root: 输入的二叉线索树
 * return: 输入的二叉线索树的后序遍历中的最后一个结点
 * note: 给定一个二叉线索树root，根据后序遍历的定义，后序遍历中的最后一个结点必定是该二叉线索树的根结点，故直接返回根结点即可
 */
ThreadNode *ThreadPostTree::getLastNode(ThreadNode *root)
{
	return root;
}


/**
 * reverse_postorder: 获取当前二叉线索树的倒序的后序遍历序列
 * return: 当前二叉线索树的倒序后序遍历序列
 */
vector<int> ThreadPostTree::reverse_postorder()
{
	vector<int> res;

	ThreadNode *now=getLastNode(treeroot);

	while(now)
	{
		res.push_back(now->val);
		now=getPrevNode(now);
	}

	return res;
}


/**
 * ~ThreadPostTree: 析构函数
 */
ThreadPostTree::~ThreadPostTree()
{
	ThreadNode *now=getLastNode(treeroot);

	while(now)
	{
		ThreadNode *temp=now;
		now=getPrevNode(now);
		delete temp;
	}
}
