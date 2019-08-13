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
 * BsTree: ������������ 
 */
class BSTree: public BinaryTree
{
    public:
    // 1. constructors
    BSTree();                              // Ĭ�Ϲ��캯��������յĶ���������
    BSTree(vector<int> &preorder,vector<int> &inorder);  // ��ǰ���������������������������
	BSTree(vector<int> &postorder, vector<int> &inorder, int val);// �Ӻ���������������������������������һ������Ϊ�������ص���Ԫ��û��ʵ������ 
	
	// 2. copy controllers
	BSTree(const BSTree &other);           		 // �������캯��
	BSTree & operator = (const BSTree &other);   // ������������� 
    
    // 3. methods 
	void insert(int val) override;              // �����в�����
    void remove(int val) override;              // ������ɾ�����
    bool exist(int val) const override;         // �����в��Ҹ���ֵ�Ľ���Ƿ����  
    vector<int> preorder() const override;      // ��������ǰ�����
    vector<int> inorder() const override;       // ���������������
    vector<int> postorder() const override;     // �������ĺ������
    vector<int> levelorder() const override;    // �������Ĳ�α��� 
    int size() const override;                  // �������Ľ�����
    TreeNode *get(int val) const override;      // ���Ҷ������ĸ���ֵ�Ľ�� 
    int maxpathsum() const override;            // �����������·����
    int depth() const override;                 // �����������
    int maxrlpath() const override;             // �������ĴӸ���㵽Ҷ�ӽ��ĺ͵����ֵ
    TreeNode *lca(TreeNode *p, TreeNode *q); 	// ���Ҷ���������������������������� 
    
    // 4. destructor
    virtual ~BSTree();                          // �������������������� 
    
    // 5. domains
    private:
    TreeNode *treeroot;                // ����������� 
    TreeNode *__copy__(TreeNode *root);  
    void __delete__(TreeNode *root); 
    int maxrlpath(TreeNode *root) const;
}; 

BSTree::BSTree()
{
	treeroot=NULL;
}

BSTree::BSTree(vector<int> &preorder,vector<int> &inorder)
{
	function<TreeNode*(vector<int> &, vector<int> &)> func = [&](vector<int> &preorder, vector<int> &inorder) {   // lambda�����������vector<int> &preorder, vector<int> &inorder�����&����ȫ�������ı���������
		if(!preorder.size()||!inorder.size())
		return static_cast<TreeNode *>(NULL);
		// note: �����ԭ������������Ҫʹ���������ֽ��еݹ飬�Ͳ���ʹ��auto�ؼ��� 
		// 1. ʹ��ǰ������ĵ�һ��Ԫ�ع�������
		int rootval=preorder[0];
		TreeNode *root=new TreeNode(rootval);
		preorder.erase(preorder.begin());
		// 2. ����������������ҵ�������ֵ�����Ӹ�λ�ÿ�ʼ������������з�Ϊ��������
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
		// 3. ʹ��ǰ�������������������������У��ݹ�������������������� 
		root->left=func(preorder, left);
		root->right=func(preorder, right);
		return root;
	};
	
	treeroot=func(preorder, inorder);
}

BSTree::BSTree(vector<int> &postorder, vector<int> &inorder, int val)
{
	function<TreeNode*(vector<int> &, vector<int> &)> func = [&](vector<int> &postorder, vector<int> &inorder) {   // lambda����������ע����&����ȫ�������ı���������
		if(!postorder.size()||!inorder.size())
		return static_cast<TreeNode *>(NULL);
		// note: �����ԭ������������Ҫʹ���������ֽ��еݹ飬�Ͳ���ʹ��auto�ؼ��� 
		// 1. ʹ�ú�����������һ��Ԫ�ع�������
		int rootval=postorder[postorder.size()-1];
		TreeNode *root=new TreeNode(rootval);
		postorder.pop_back();
		// 2. ����������������ҵ�������ֵ�����Ӹ�λ�ÿ�ʼ������������з�Ϊ��������
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
		// 3. ʹ��ǰ�������������������������У��ݹ����������������������ע���������������е�˳�򣬱����ȹ��������� 
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
		if(!root)              // ���ҵ��ս�㣬�򲻴���Ҫɾ���Ľ�㣬��ֹ�ݹ� 
		return root;
		else if(val<root->val) // ��Ŀ��ֵС�ڵ�ǰ����ֵ����������Ҵ�ɾ����� 
		root->left=func(root->left, val);
		else if(val>root->val) // ��Ŀ��ֵ���ڵ�ǰ����ֵ�������Ҳ��Ҵ�ɾ����� 
		root->right=func(root->right, val);
		else                   // �ҵ���Ŀ���㣬��ʼ���н��ɾ���㷨 
		{
			if(!root->left&&!root->right)    // ����ɾ�����ΪҶ�ӽ�㣬��ֱ�ӽ���ɾ�� 
			{
				delete root;
				return static_cast<TreeNode *>(NULL);
			}
			else if(root->left&&!root->right) // ����������ֻ����һ������ɾ�����󷵻������Ǹ��ǿյ����� 
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
			else   // ����ɾ����������������������������ʱɾ��������Ϊ���ӣ���ϸ��μ�����Ĵ��� 
			{
				// ���ȣ����Ҿ����������е����ֵ�������������е���Сֵ����Ŀ���㣬��������ֵ���ڽ��ĸ���� 
				TreeNode *now=root->left;
				TreeNode *nowprev=root;
				while(now->right)
				{
					nowprev=now;
					now=now->right;
				}
				// Ȼ�󣬽���ֵ�ʹ�ɾ���Ľ���ֵ������ʹ�������������ֵ��������������Сֵ��Ŀ�Ķ��Ǳ�֤�ڽ�������Ȼ�ܹ�ά�ֶ��������������ʣ� 
				int temp=root->val;
				root->val=now->val;
				now->val=temp;
				// ���ɾ��Ŀ���㣨����ǰ���ֹ��򣩣���ΪĿ�������ֻ��һ������
				if(now->left)
				nowprev->right=now->left;
				else if(now->right)
				nowprev->right=now->right;
				else
				nowprev->right=static_cast<TreeNode *>(NULL);
				
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
		return static_cast<TreeNode *>(NULL);
		else if(root->val==val)
		return root;
		else if(val<root->val)
		return func(root->left);
		else
		return func(root->right);
	};
	
	return func(treeroot);
}

TreeNode *BSTree::lca(TreeNode *p, TreeNode *q)
{
	if(p->val>q->val)   // ȷ��p����ֵ��С��q����ֵ�ϴ� 
	{
		TreeNode *temp=p;
		p=q;
		q=p;
	}
	
	function<TreeNode*(TreeNode *, TreeNode *, TreeNode *)> func = [&](TreeNode *root, TreeNode *p, TreeNode *q) {
		if(!root)                   // ��ǰ��Ϊ�գ�������lca 
		return static_cast<TreeNode *>(NULL);
		else if(root->val<p->val)   // ��ǰ����ֵС��������еĽ�Сֵ����lca�ض��ڵ�ǰ������������
		return func(root->right, p, q);
		else if(root->val>q->val)   // ��ǰ����ֵ����������еĽϴ�ֵ����lca�ض��ڵ�ǰ������������
		return func(root->left, p, q);
		else                        // ��ǰ����ֵ�ڽ��p�ͽ��q֮�䣬��lca���ǵ�ǰ��� 
		return root; 
	};
	
	return func(treeroot, p, q);
} 

int BSTree::maxpathsum() const
{
	function<int(TreeNode *)> func = [&](TreeNode *root) {
		if(!root)
		return 0;
		else if(!root->left&&!root->right)
		return root->val;
		else 
		{
			// ������Ϊ�գ������·���Ĵ��ڿ��ܴ��������������
			int first=maxrlpath(root->left)+maxrlpath(root->right)+root->val;   // ��һ��������·����Խ�������������� 
			int second=func(root->left);    // �ڶ������: �·�������������� 
			int third=func(root->right);    // ���������: �·��������������
			
			int max=((first>second)?((first>third)?first:third):((second>third)?second:third));
		}
	};
	
	return func(treeroot);
}

int BSTree::depth() const
{
	function<int(TreeNode *)> func = [&](TreeNode *root) {
		if(!root)
		return 0;
		else
		{
			int leftdepth=func(root->left);
			int rightdepth=func(root->right);
			int max=(leftdepth>rightdepth)?leftdepth:rightdepth;
			return 1+max;
		}
	};
	
	return func(treeroot);
} 

int BSTree::maxrlpath() const
{
	vector<int> res;
	function<void(TreeNode *, int)> func = [&](TreeNode *root, int sum) {
		if(!root)
		res.push_back(sum);
		else
		{
			func(root->left, sum+root->val);
			func(root->right, sum+root->val);
		}
	};
	
	func(treeroot, 0);
	int max=INT_MIN;
	for(auto a:res)
	{
		if(a>max)
		max=a;
	}
	return max;
}

int BSTree::maxrlpath(TreeNode *root) const
{
	vector<int> res;
	function<void(TreeNode *, int)> func = [&](TreeNode *root, int sum) {
		if(!root)
		res.push_back(sum);
		else
		{
			func(root->left, sum+root->val);
			func(root->right, sum+root->val);
		}
	};
	
	func(root, 0);
	int max=INT_MIN;
	for(auto a:res)
	{
		if(a>max)
		max=a;
	}
	return max;
}
    
BSTree::~BSTree() 
{
	__delete__(treeroot);
}

#endif
