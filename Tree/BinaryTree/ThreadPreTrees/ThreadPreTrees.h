#include <iostream>
#include <string>
#include <stack>
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
 * ThreadPreTree: 前序遍历的二叉搜索线索树
 * note 1: 在普通二叉树中，可能存在许多的结点只有左子结点或者右子结点，或者是叶子结点，这时该结点中left和right成员就处于空置状态
 * note 2: 为了在左子结点/右子结点为空的情况下利用left和right成员，规定:当左子结点为空时，使用left字段记录当前结点在前序遍历时的前驱结点，当右子结点为空时，使用right字段记录当前结点在前序遍历时的后继结点，并额外新增lflag和rflag表明left字段和right字段指向的是前后驱结点还是左右子结点，这就构成了前序遍历二叉线索树
*/
class ThreadPreTree
{
	public:
	// 1. 构造函数
	ThreadPreTree();                                                      // 默认构造函数
	ThreadPreTree(const Tree &other);                                     // 从普通二叉搜索树生成对应的线索树

	// 2. 拷贝控制
	ThreadPreTree(const ThreadPreTree &other);                               // 拷贝构造函数
	ThreadPreTree & operator = (const ThreadPreTree &other) = delete;        // 禁止拷贝赋值运算符的使用

	// 3. 功能函数: 重点注意线索树的两种基本操作getFirstNode和getNextNode
	vector<int> preorder();                                              // 获取当前线索树的前序遍历序列，该算法应用上述两个基本操作进行实现

	// 4. 析构函数
	~ThreadPreTree();

	private:
	ThreadNode *treeroot;     // 线索树的根结点

	ThreadNode *__copyTree(TreeNode *root);                              // 从二叉搜索树拷贝一个线索树的底层递归实现

	// 5. 二叉线索树的四种基本操作
	ThreadNode *getFirstNode(ThreadNode *root);               // 线索树基本操作1: 获取给定的线索树前序遍历序列中的第一个结点
	ThreadNode *getNextNode(ThreadNode *pos);                 // 线索树基本操作2: 获取在前序遍历中当前结点的下一个结点
	ThreadNode *getLastNode (ThreadNode *root);               // 线索树基本操作3: 获取给定的线索树前序遍历序列中的最后一个结点

	// important note: 基于前序遍历的二叉线索树不能实现获取给定结点在前序遍历中的前驱结点的操作，只有基于中序遍历的二叉线索树可以实现全部的四种操作
	// note: 简单解释一下为什么基于前序遍历的二叉线索树不能实现获取前驱结点的操作，因为前序遍历中，是先输出当前结点，然后输出左子树，最后输出右子树；因此当拿到当前结点时，仅能知道接下来要输出左子树，即后继结点是左子树的前序遍历的首结点，但是不知道当前结点的前驱结点（因为当前结点是最先输出的）
	// note: 而在基于中序遍历的二叉线索树中，根据中序遍历的定义，对于每个结点，在访问当前结点之前一定先访问了左子树，在访问该结点之后一定后访问了右子树，因此既可以求前驱结点也可以求后继结点，能够完全实现全部四种线索树操作
	//ThreadNode *getPrevNode(ThreadNode *pos);                 // 线索树基本操作4：获取在前序遍历中当前结点的上一个结点
};


/**
 * ThreadPreTree: 构造一个空的前序二叉线索树
 */
ThreadPreTree::ThreadPreTree()
{
	treeroot=NULL;
}


/**
 * ThreadPreTree: 从一个二叉树构造一个前序二叉搜索树
 */
ThreadPreTree::ThreadPreTree(const Tree &other)
{
	// 1. 首先从输入的源二叉搜索树进行深拷贝，得到一个二叉搜索树
	treeroot=__copyTree(other.getroot());

	// 2. 然后进行该二叉搜索树的线索化，通过一次前序遍历进行实现，这里使用非递归方法进行实现（关于普通二叉树的中序遍历请参见二叉搜索树的部分，本处不再重复介绍）
	// note: 使用一个指针nowprev记录当前正在访问的结点在前序遍历中的前驱结点，若当前结点不存在左子结点，则令now->lflag=1，并令now->left=nowprev；若当前结点不存在右子结点，则令now->rflag=1，并令now->right指向当前的栈顶结点

	if(!treeroot)   // 注意处理特殊情况
		return;

	stack<ThreadNode *> sta;
	ThreadNode *nowprev=NULL;

	sta.push(treeroot);

	while(sta.size())
	{
		ThreadNode *now=sta.top();

		sta.pop();     // 个人习惯经常忘记将当前结点出栈，需要特别提醒和引起注意

		if(now->right)
			sta.push(now->right);
		if(now->left)
			sta.push(now->left);

		if(!now->left)
		{
			now->lflag=1;
			now->left=nowprev;
		}
		if(!now->right)
		{
			now->rflag=1;
			if(sta.size())
				now->right=sta.top();
			else
				now->right=NULL;
		}

		nowprev=now;
	}

	return;
}

ThreadNode *ThreadPreTree::__copyTree(TreeNode *root)
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
 * getFirstNode: 获取线索树的前序遍历中的第一个结点
 * param root: 输入的线索树的根结点
 * return: 输入线索树的前序遍历的首结点
 * note: 一个二叉线索树的前序遍历的首结点一定就是该二叉线索树的根结点，因此直接返回根结点即可
 */
ThreadNode *ThreadPreTree::getFirstNode(ThreadNode *root)
{
	return root;
}


/**
 * getNextNode: 获取线索树的前序遍历中给定结点的下一个结点
 * param pos: 给定的输入结点
 * return: 输入结点在前序遍历中的下一个结点
 * note: 这里的处理方法和中序遍历时不同，需要仔细从前序遍历的定义来思考：对输入的结点pos，根据前序遍历，访问完当前结点后，应当首先访问左子树，然后访问右子树：
 *       (1)若pos->lflag==1，则左子树不存在，这时跳过左子树，直接开始访问右子树：
 *       	 (a)若pos->rflag==0，即右子树存在，这时下一个结点就是右子树的前序遍历序列的第一个结点，因此返回getFirstNode(root->right)
 *       	 (b)若pos->rflag==1，即右子树不存在，这时root->right就指向后继节点，因此直接返回root->right
 *       (2)若pos->lflag==0，则左子树存在，这时下一个结点就是左子树的前序遍历序列的第一个结点，因此返回getFirstNode(root->left)
 */
ThreadNode *ThreadPreTree::getNextNode(ThreadNode *pos)
{
	if(pos->lflag==1)   // 1. 左子树不存在
	{
		if(pos->rflag==1)
			return pos->right;
		else
			return getFirstNode(pos->right);
	}
	else
		return getFirstNode(pos->left);
}


/**
 * getLastNode: 获取线索树的前序遍历中的最后一个结点
 * param root: 输入的二叉线索树
 * return: 输入的二叉线索树的前序遍历中的最后一个结点
 * note: 给定一个二叉线索树root，根据前序遍历的定义，前序遍历中的最后一个结点必定是该二叉线索树的最右侧的结点，故直接从根节点沿着右子结点前进，返回前进路径上的最后一个结点即可
 */
ThreadNode *ThreadPreTree::getLastNode(ThreadNode *root)
{
	ThreadNode *now=root;

	while(now->rflag==0&&now->right)
	{
		now=now->right;
	}

	return now;
}


/**
 * preorder: 获取当前二叉线索树的前序遍历序列
 * return: 当前二叉县所属的前序遍历序列
 */
vector<int> ThreadPreTree::preorder()
{
	vector<int> res;

	ThreadNode *now=getFirstNode(treeroot);

	while(now)
	{
		res.push_back(now->val);
		now=getNextNode(now);
	}

	return res;
}


/**
 * ~ThreadPreTree: 析构函数
 */
ThreadPreTree::~ThreadPreTree()
{
	ThreadNode *now=getFirstNode(treeroot);

	while(now)
	{
		ThreadNode *temp=now;
		now=getNextNode(now);
		delete temp;
	}
}
