#ifndef BSTree_H
#define BSTree_H
#include <string>
#include <iostream>
#include <functional>
#include <stack>
#include <queue>
#include <algorithm>
#include "BinaryTree.h"

/**
 * BsTree: 二叉搜索树类 
 */
class BSTree: public BinaryTree
{
    public:
    // 1. constructors
    BSTree();                              // 默认构造函数：构造空的二叉搜索树
    BSTree(vector<int> &preorder,vector<int> &inorder);  // 从前序遍历和中序遍历构造二叉搜索树
	BSTree(vector<int> &postorder, vector<int> &inorder, int val);// 从后序遍历和中序遍历构造二叉搜索树，最后一个参数为用于重载的哑元，没有实际意义 
	
	// 2. copy controllers
	BSTree(const BSTree &other);           // 拷贝构造函数
	BSTree & operator = (const BSTree &other);   // 拷贝构造运算符 
    
    // 3. methods 
	void insert(int val) override;              // 向树中插入结点
    void remove(int val) override;              // 从树中删除结点
    bool exist(int val) const override;         // 在树中查找给定值的结点是否存在  
    vector<int> preorder() const override;      // 二叉树的前序遍历
    vector<int> inorder() const override;       // 二叉树的中序遍历
    vector<int> postorder() const override;     // 二叉树的后序遍历
    vector<int> levelorder() const override;    // 二叉树的层次遍历 
    int size() const override;                  // 二叉树的结点个数
    TreeNode *get(int val) const override;      // 查找二叉树的给定值的结点 
    int maxpathsum() const override;            // 二叉树的最大路径和
    int depth() const override;                 // 二叉树的深度
    int maxrlpath() const override;             // 二叉树的从根结点到叶子结点的和的最大值
    
    // 4. destructor
    ~BSTree();                         // 二叉树析构函数 
    
    // 5. domains
    private:
    TreeNode *treeroot;                // 二叉树根结点 
    TreeNode *__copy__(TreeNode *root);  
    void __delete__(TreeNode *root); 
}; 

BSTree::BSTree()
{
	treeroot=NULL;
}

BSTree::BSTree(vector<int> &preorder,vector<int> &inorder)
{
	function<TreeNode*(vector<int> &, vector<int> &)> func = [&](vector<int> &preorder, vector<int> &inorder) {   // lambda匿名函数，注意用&捕获全部上下文变量的引用
		if(!preorder.size()||!inorder.size())
		return (TreeNode*)NULL;
		// note: 如果在原匿名函数中需要使用自身名字进行递归，就不能使用auto关键字 
		// 1. 使用前序遍历的第一个元素构造根结点
		int rootval=preorder[0];
		TreeNode *root=new TreeNode(rootval);
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
	
	treeroot=func(preorder, inorder);
}

BSTree::BSTree(vector<int> &postorder, vector<int> &inorder, int val)
{
	function<TreeNode*(vector<int> &, vector<int> &)> func = [&](vector<int> &postorder, vector<int> &inorder) {   // lambda匿名函数，注意用&捕获全部上下文变量的引用
		if(!postorder.size()||!inorder.size())
		return (TreeNode*)NULL;
		// note: 如果在原匿名函数中需要使用自身名字进行递归，就不能使用auto关键字 
		// 1. 使用后序遍历的最后一个元素构造根结点
		int rootval=postorder[postorder.size()-1];
		TreeNode *root=new TreeNode(rootval);
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
	
	treeroot=func(postorder, inorder);
}
	
BSTree::BSTree(const BSTree &other)
{
	treeroot=__copy__(other.treeroot);
}

BSTree & BSTree::operator = (const BSTree &other)
{
	if(this==&other)
	return (*this);
	
	__delete__(treeroot);
	treeroot=__copy__(other.treeroot);
	return (*this);
}

TreeNode *BSTree::__copy__(TreeNode *root)
{
	if(!root)
	return NULL;
	else
	{
		TreeNode *newroot=new TreeNode(root->val);
		newroot->left=__copy__(root->left);
		newroot->right=__copy__(root->right);
		return newroot;
	}
}

void BSTree::__delete__(TreeNode *root)
{
	if(!root)
	return;
	else
	{
		__delete__(root->left);
		__delete__(root->right);
		delete root; 
	}
}
    
void BSTree::insert(int val)
{
	function<TreeNode *(TreeNode *, int)> func=[&](TreeNode *root, int val) {
		if(!root)
		return new TreeNode(val);
		else if(val<root->val)
		root->left=func(root->left, val);
		else if(val>root->val)
		root->right=func(root->right, val);
		else 
		return root;
	};
	
	treeroot=func(treeroot, val);
}

void BSTree::remove(int val)
{
	function<TreeNode *(TreeNode *, int)> func=[&](TreeNode *root, int val) {
		if(!root)              // 查找到空结点，则不存在要删除的结点，终止递归 
		return root;
		else if(val<root->val) // 若目标值小于当前结点的值，则向左查找待删除结点 
		root->left=func(root->left, val);
		else if(val>root->val) // 若目标值大于当前结点的值，则向右查找待删除结点 
		root->right=func(root->right, val);
		else                   // 找到了目标结点，开始进行结点删除算法 
		{
			if(!root->left&&!root->right)    // 若待删除结点为叶子结点，则直接进行删除 
			{
				delete root;
				return (TreeNode *)NULL;
			}
			else if(root->left&&!root->right) // 左右子树中只存在一个，则删除结点后返回其中那个非空的子树 
			{
				TreeNode *temp=root->left;
				delete root;
				return temp;
			}
			else if(!root->left&&root->right)
			{
				TreeNode *temp=root->right;
				delete root;
				return temp;
			}
			else   // 若待删除结点既有左子树又有右子树，这时删除过程最为复杂，详细请参加下面的代码 
			{
				// 首先，查找具有左子树中的最大值（或者右子树中的最小值）的目标结点，并保留该值所在结点的父结点 
				TreeNode *now=root->left;
				TreeNode *nowprev=root;
				while(now->right)
				{
					nowprev=now;
					now=now->right;
				}
				// 然后，将该值和待删除的结点的值互换（使用左子树中最大值或者右子树中最小值的目的都是保证在交换后仍然能够维持二叉搜索树的性质） 
				int temp=root->val;
				root->val=now->val;
				now->val=temp;
				// 最后，删除目标结点（按照前两种规则），因为目标结点最多只有一个子树
				if(now->left)
				nowprev->right=now->left;
				else if(now->right)
				nowprev->right=now->right;
				else
				nowprev->right=NULL;
				
				delete now;
				return root;
			}
		}
	};
	
	treeroot=func(treeroot, val);
}

bool BSTree::exist(int val) const
{
	function<bool(TreeNode *)> func = [&](TreeNode *root) {
		if(!root)
		return false;
		else if(root->val==val)
		return true;
		else if(val<root->val)
		return func(root->left);
		else
		return func(root->right);
	};
	
	return func(treeroot);
}

vector<int> BSTree::preorder() const
{
	vector<int> res;
	if(!treeroot)
	return res;
	
	stack<TreeNode *> sta;
	sta.push(treeroot);
	while(sta.size())
	{
		TreeNode *now=sta.top();
		sta.pop();
		res.push_back(now->val);
		
		if(now->right)
		sta.push(now->right);
		if(now->left)
		sta.push(now->left);
	}
	return res;
}

vector<int> BSTree::inorder() const 
{
	vector<int> res;
	if(!treeroot)
	return res;
	
	stack<TreeNode *> sta;
	TreeNode *temp=treeroot;
	while(temp)
	{
		sta.push(temp);
		temp=temp->left;
	}
	
	while(sta.size())
	{
		TreeNode *now=sta.top();
		sta.pop();
		res.push_back(now->val);
		
		temp=now->right;
		while(temp)
		{
			sta.push(temp);
			temp=temp->left;
		}
	}
	return res;
}

vector<int> BSTree::postorder() const
{
	vector<int> res;
	if(!treeroot)
	return res;
	
	stack<TreeNode *> sta;
	sta.push(treeroot);
	while(sta.size())
	{
		TreeNode *now=sta.top();
		sta.pop();
		res.push_back(now->val);
		
		if(now->left)
		sta.push(now->left);
		if(now->right)
		sta.push(now->right);
	}
	reverse(res.begin(), res.end()); 
	return res;
}

vector<int> BSTree::levelorder() const
{
	vector<int> res;
	if(!treeroot)
	return res;
	
	queue<TreeNode *> que;
	que.push(treeroot);
	while(que.size())
	{
		TreeNode *now=que.front();
		que.pop();
		res.push_back(now->val);
		
		if(now->left)
		que.push(now->left);
		if(now->right)
		que.push(now->right);
	}
	return res;
}

int BSTree::size() const 
{
	function<int(TreeNode *)> func = [&](TreeNode *root) {
		if(!root)
		return 0;
		else if(!root->left&&!root->right)
		return 1;
		else
		return 1+func(root->left)+func(root->right); 
	};
	
	return func(treeroot);
}

TreeNode *BSTree::get(int val) const
{
	function<TreeNode*(TreeNode *)> func = [&](TreeNode *root) {
		if(!root)
		return (TreeNode*)NULL;
		else if(root->val==val)
		return root;
		else if(val<root->val)
		return func(root->left);
		else
		return func(root->right);
	};
	
	return func(treeroot);
}

int BSTree::maxpathsum() const
{
	
}

int BSTree::depth() const
{
	
} 

int BSTree::maxrlpath() const
{
	
}
    
BSTree::~BSTree()
{
	__delete__(treeroot);
}

#endif
