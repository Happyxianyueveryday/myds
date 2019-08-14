#define INTHREADTREE_H
#define INTHREADTREE_H
#include <iostream>
#include <string> 
#include <functional>
#include <stack>
#include <vector>
#include "ThreadTree.h"

using namespace std;

/**
 * InThreadTree: 中序遍历首结点 
 */
class InThreadTree: public ThreadTree
{
	public: 
	InThreadTree(vector<int> &preorder, vector<int> &inorder);              // 从前序遍历和中序遍历构造线索树 
	InThreadTree(vector<int> &postorder, vector<int> &inorder, int num);    // 从后序遍历和中序遍历构造线索树 
	InThreadTree(const InThreadTree &other) = delete;
	InThreadTree & operator = (const InThreadTree &other) = delete;        
	ThreadNode *getFirstNode(ThreadNode *now);  // 获取线索树的中序遍历首结点 
	ThreadNode *getLastNode(ThreadNode *now);   // 获取线索树的中序遍历末结点 
	ThreadNode *getNextNode(ThreadNode *now);   // 获取线索树中输入结点在中序遍历中的下一个结点 
	ThreadNode *getPrevNode(ThreadNode *now);   // 获取线索树中输入结点在中序遍历中的上一个结点 
	vector<int> traversal();                    // 对线索树进行中序遍历 
	~InThreadTree();                            // 中序线索树析构函数 
	
	private:
	ThreadNode *treeroot;
};

InThreadTree::InThreadTree(vector<int> &preorder, vector<int> &inorder)
{
	// lambda func: 根据遍历序列构建二叉树 
	function<ThreadNode*(vector<int> &, vector<int> &)> func = [&](vector<int> &preorder, vector<int> &inorder) {  
		if(!preorder.size()||!inorder.size())
		return static_cast<ThreadNode *>(NULL);
		// note: 如果在原匿名函数中需要使用自身名字进行递归，就不能使用auto关键字 
		// 1. 使用前序遍历的第一个元素构造根结点
		int rootval=preorder[0];
		ThreadNode *root=new ThreadNode(rootval);
		preorder.erase(preorder.begin());
		// 2. 在中序遍历序列中找到根结点的值，并从该位置开始将中序遍历序列分为左右两段
		int index=-1;
		for(int i=0;i<inorder.size();i++)
		{
			if(inorder[i]==rootval)
			{
				index=i;
				break;
			}
		}
		vector<int> left, right;
		for(int i=0;i<inorder.size();i++)
		{
			if(i<index)
			left.push_back(inorder[i]);
			else if(i>index)
			right.push_back(inorder[i]);
		}
		// 3. 使用前序遍历和左右两段中序遍历序列，递归地生成左子树和右子树 
		root->left=func(preorder, left);
		root->right=func(preorder, right);
		return root;
	};
	
	// lambda link: 中序线索化二叉树
	// 使用一次中序遍历就能够将二叉树线索化 
	function<void(void)> link = [&]()
	{
		stack<ThreadNode *> sta;
		ThreadNode *temp=treeroot;
		while(temp)
		{
			sta.push(temp);
			temp=temp->left;
		}
		
		ThreadNode *nowprev=NULL;
		while(sta.size())
		{
			ThreadNode *now=sta.top();
			sta.pop();
			temp=now->right; 
			while(temp)
			{
				sta.push(temp);
				temp=temp->left;
			} 
			
			if(!now->left)
			{
				now->lflag=true;
				now->left=nowprev;
			}
			if(!now->right)
			{
				now->rflag=true;
				if(sta.size())     // 易错点，注意栈判空 
				now->right=sta.top();
				else
				now->right=NULL;
			} 	
			nowprev=now;
		} 
	};
	
	treeroot=func(preorder, inorder);   // 构造二叉树 
	link();                             // 二叉树线索化 
}

InThreadTree::InThreadTree(vector<int> &postorder, vector<int> &inorder, int num)
{
	function<ThreadNode*(vector<int> &, vector<int> &)> func = [&](vector<int> &postorder, vector<int> &inorder) {   // lambda匿名函数，注意用&捕获全部上下文变量的引用
		if(!postorder.size()||!inorder.size())
		return (ThreadNode*)NULL;
		// note: 如果在原匿名函数中需要使用自身名字进行递归，就不能使用auto关键字 
		// 1. 使用后序遍历的最后一个元素构造根结点
		int rootval=postorder[postorder.size()-1];
		ThreadNode *root=new ThreadNode(rootval);
		postorder.pop_back();
		// 2. 在中序遍历序列中找到根结点的值，并从该位置开始将中序遍历序列分为左右两段
		int index=-1;
		for(int i=0;i<inorder.size();i++)
		{
			if(inorder[i]==rootval)
			{
				index=i;
				break;
			}
		}
		vector<int> left, right;
		for(int i=0;i<inorder.size();i++)
		{
			if(i<index)
			left.push_back(inorder[i]);
			else if(i>index)
			right.push_back(inorder[i]);
		}
		// 3. 使用前序遍历和左右两段中序遍历序列，递归地生成左子树和右子树，注意后序遍历逆向序列的顺序，必须先构造右子树 
		root->right=func(postorder, right);
		root->left=func(postorder, left);
		return root;
	};
	
	// lambda link: 中序线索化二叉树
	// 使用一次中序遍历就能够将二叉树线索化 
	function<void(void)> link = [&]()
	{
		stack<ThreadNode *> sta;
		ThreadNode *temp=treeroot;
		while(temp)
		{
			sta.push(temp);
			temp=temp->left;
		}
		
		ThreadNode *nowprev=NULL;
		while(sta.size())
		{
			ThreadNode *now=sta.top();
			sta.pop();
			temp=now->right; 
			while(temp)
			{
				sta.push(temp);
				temp=temp->left;
			}
			
			if(!now->left)
			{
				now->lflag=true;
				now->left=nowprev;
			}
			if(!now->right)
			{
				now->rflag=true;
				now->right=sta.top();
			} 	
			nowprev=now;
		} 
	};
	
	treeroot=func(postorder, inorder);   // 构造二叉树 
	link();                             // 二叉树线索化 
}

ThreadNode *InThreadTree::getFirstNode(ThreadNode *now)
{
	// 二叉树最左侧的结点就是中序遍历的首结点
	while(!now->lflag)
	{
		now=now->left;	
	} 
	return now;
}

ThreadNode *InThreadTree::getLastNode(ThreadNode *now)
{
	// 二叉树最右侧的结点就是中序遍历的末结点 
	while(!now->rflag)
	{
		now=now->right;
	}
	return now;
}

ThreadNode *InThreadTree::getNextNode(ThreadNode *now)
{
	// 1. 因为当前结点已经访问，根据中序遍历定义，因此后继结点就是当前结点的左子树中序遍历的最后一个结点 
	if(!now->rflag)
	return getFirstNode(now->right);
	// 2. 若不存在右子树，则根据中序线索树定义，now->right就指向中序遍历中的下一个结点 
	else
	return now->right;
}

ThreadNode *InThreadTree::getPrevNode(ThreadNode *now)   
{
	// 1. 因为当前结点已经被访问，根据中序遍历定义，因此前驱结点就是当前结点的左子树的中序遍历的最后一个结点 
	if(!now->lflag) 
	return getLastNode(now->left);
	// 2. 若不存在左子树，则根据中序线索树定义，now->left就指向中序遍历中的上一个结点 
	else
	return now->left;
}

vector<int> InThreadTree::traversal()  
{
	ThreadNode *now=getFirstNode(treeroot);
	vector<int> res;
	while(now)
	{
		res.push_back(now->val);
		now=getNextNode(now);
	}
	return res;
}

InThreadTree::~InThreadTree()
{
	ThreadNode *now=getLastNode(treeroot);
	while(now)
	{
		ThreadNode *temp=now;
		now=getPrevNode(now);
		delete temp;
	}
}
