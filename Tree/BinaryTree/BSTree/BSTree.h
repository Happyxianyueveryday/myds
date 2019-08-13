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
 * BsTree: ¶ş²æËÑË÷Ê÷Àà 
 */
class BSTree: public BinaryTree
{
    public:
    // 1. constructors
    BSTree();                              // Ä¬ÈÏ¹¹Ôìº¯Êı£º¹¹Ôì¿ÕµÄ¶ş²æËÑË÷Ê÷
    BSTree(vector<int> &preorder,vector<int> &inorder);  // ´ÓÇ°Ğò±éÀúºÍÖĞĞò±éÀú¹¹Ôì¶ş²æËÑË÷Ê÷
	BSTree(vector<int> &postorder, vector<int> &inorder, int val);// ´ÓºóĞò±éÀúºÍÖĞĞò±éÀú¹¹Ôì¶ş²æËÑË÷Ê÷£¬×îºóÒ»¸ö²ÎÊıÎªÓÃÓÚÖØÔØµÄÑÆÔª£¬Ã»ÓĞÊµ¼ÊÒâÒå 
	
	// 2. copy controllers
	BSTree(const BSTree &other);           		 // ¿½±´¹¹Ôìº¯Êı
	BSTree & operator = (const BSTree &other);   // ¿½±´¹¹ÔìÔËËã·û 
    
    // 3. methods 
	void insert(int val) override;              // ÏòÊ÷ÖĞ²åÈë½áµã
    void remove(int val) override;              // ´ÓÊ÷ÖĞÉ¾³ı½áµã
    bool exist(int val) const override;         // ÔÚÊ÷ÖĞ²éÕÒ¸ø¶¨ÖµµÄ½áµãÊÇ·ñ´æÔÚ  
    vector<int> preorder() const override;      // ¶ş²æÊ÷µÄÇ°Ğò±éÀú
    vector<int> inorder() const override;       // ¶ş²æÊ÷µÄÖĞĞò±éÀú
    vector<int> postorder() const override;     // ¶ş²æÊ÷µÄºóĞò±éÀú
    vector<int> levelorder() const override;    // ¶ş²æÊ÷µÄ²ã´Î±éÀú 
    int size() const override;                  // ¶ş²æÊ÷µÄ½áµã¸öÊı
    TreeNode *get(int val) const override;      // ²éÕÒ¶ş²æÊ÷µÄ¸ø¶¨ÖµµÄ½áµã 
    int maxpathsum() const override;            // ¶ş²æÊ÷µÄ×î´óÂ·¾¶ºÍ
    int depth() const override;                 // ¶ş²æÊ÷µÄÉî¶È
    int maxrlpath() const override;             // ¶ş²æÊ÷µÄ´Ó¸ù½áµãµ½Ò¶×Ó½áµãµÄºÍµÄ×î´óÖµ
    TreeNode *lca(TreeNode *p, TreeNode *q); 	// ²éÕÒ¶ş²æÊ÷¸ø¶¨Á½¸ö½áµãµÄ×î½ü¹«¹²×æÏÈ 
    
    // 4. destructor
    virtual ~BSTree();                          // ¶ş²æËÑË÷Ê÷ĞéÎö¹¹º¯Êı 
    
    // 5. domains
    private:
    TreeNode *treeroot;                // ¶ş²æÊ÷¸ù½áµã 
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
	function<TreeNode*(vector<int> &, vector<int> &)> func = [&](vector<int> &preorder, vector<int> &inorder) {   // lambdaÄäÃûº¯Êı£¬×vector<int> &preorder, vector<int> &inorder¢ÒâÓÃ&²¶»ñÈ«²¿ÉÏÏÂÎÄ±äÁ¿µÄÒıÓÃ
		if(!preorder.size()||!inorder.size())
		return static_cast<TreeNode *>(NULL);
		// note: Èç¹ûÔÚÔ­ÄäÃûº¯ÊıÖĞĞèÒªÊ¹ÓÃ×ÔÉíÃû×Ö½øĞĞµİ¹é£¬¾Í²»ÄÜÊ¹ÓÃauto¹Ø¼ü×Ö 
		// 1. Ê¹ÓÃÇ°Ğò±éÀúµÄµÚÒ»¸öÔªËØ¹¹Ôì¸ù½áµã
		int rootval=preorder[0];
		TreeNode *root=new TreeNode(rootval);
		preorder.erase(preorder.begin());
		// 2. ÔÚÖĞĞò±éÀúĞòÁĞÖĞÕÒµ½¸ù½áµãµÄÖµ£¬²¢´Ó¸ÃÎ»ÖÃ¿ªÊ¼½«ÖĞĞò±éÀúĞòÁĞ·ÖÎª×óÓÒÁ½¶Î
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
		// 3. Ê¹ÓÃÇ°Ğò±éÀúºÍ×óÓÒÁ½¶ÎÖĞĞò±éÀúĞòÁĞ£¬µİ¹éµØÉú³É×ó×ÓÊ÷ºÍÓÒ×ÓÊ÷ 
		root->left=func(preorder, left);
		root->right=func(preorder, right);
		return root;
	};
	
	treeroot=func(preorder, inorder);
}

BSTree::BSTree(vector<int> &postorder, vector<int> &inorder, int val)
{
	function<TreeNode*(vector<int> &, vector<int> &)> func = [&](vector<int> &postorder, vector<int> &inorder) {   // lambdaÄäÃûº¯Êı£¬×¢ÒâÓÃ&²¶»ñÈ«²¿ÉÏÏÂÎÄ±äÁ¿µÄÒıÓÃ
		if(!postorder.size()||!inorder.size())
		return static_cast<TreeNode *>(NULL);
		// note: Èç¹ûÔÚÔ­ÄäÃûº¯ÊıÖĞĞèÒªÊ¹ÓÃ×ÔÉíÃû×Ö½øĞĞµİ¹é£¬¾Í²»ÄÜÊ¹ÓÃauto¹Ø¼ü×Ö 
		// 1. Ê¹ÓÃºóĞò±éÀúµÄ×îºóÒ»¸öÔªËØ¹¹Ôì¸ù½áµã
		int rootval=postorder[postorder.size()-1];
		TreeNode *root=new TreeNode(rootval);
		postorder.pop_back();
		// 2. ÔÚÖĞĞò±éÀúĞòÁĞÖĞÕÒµ½¸ù½áµãµÄÖµ£¬²¢´Ó¸ÃÎ»ÖÃ¿ªÊ¼½«ÖĞĞò±éÀúĞòÁĞ·ÖÎª×óÓÒÁ½¶Î
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
		// 3. Ê¹ÓÃÇ°Ğò±éÀúºÍ×óÓÒÁ½¶ÎÖĞĞò±éÀúĞòÁĞ£¬µİ¹éµØÉú³É×ó×ÓÊ÷ºÍÓÒ×ÓÊ÷£¬×¢ÒâºóĞò±éÀúÄæÏòĞòÁĞµÄË³Ğò£¬±ØĞëÏÈ¹¹ÔìÓÒ×ÓÊ÷ 
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
		if(!root)              // ²éÕÒµ½¿Õ½áµã£¬Ôò²»´æÔÚÒªÉ¾³ıµÄ½áµã£¬ÖÕÖ¹µİ¹é 
		return root;
		else if(val<root->val) // ÈôÄ¿±êÖµĞ¡ÓÚµ±Ç°½áµãµÄÖµ£¬ÔòÏò×ó²éÕÒ´ıÉ¾³ı½áµã 
		root->left=func(root->left, val);
		else if(val>root->val) // ÈôÄ¿±êÖµ´óÓÚµ±Ç°½áµãµÄÖµ£¬ÔòÏòÓÒ²éÕÒ´ıÉ¾³ı½áµã 
		root->right=func(root->right, val);
		else                   // ÕÒµ½ÁËÄ¿±ê½áµã£¬¿ªÊ¼½øĞĞ½áµãÉ¾³ıËã·¨ 
		{
			if(!root->left&&!root->right)    // Èô´ıÉ¾³ı½áµãÎªÒ¶×Ó½áµã£¬ÔòÖ±½Ó½øĞĞÉ¾³ı 
			{
				delete root;
				return static_cast<TreeNode *>(NULL);
			}
			else if(root->left&&!root->right) // ×óÓÒ×ÓÊ÷ÖĞÖ»´æÔÚÒ»¸ö£¬ÔòÉ¾³ı½áµãºó·µ»ØÆäÖĞÄÇ¸ö·Ç¿ÕµÄ×ÓÊ÷ 
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
			else   // Èô´ıÉ¾³ı½áµã¼ÈÓĞ×ó×ÓÊ÷ÓÖÓĞÓÒ×ÓÊ÷£¬ÕâÊ±É¾³ı¹ı³Ì×îÎª¸´ÔÓ£¬ÏêÏ¸Çë²Î¼ÓÏÂÃæµÄ´úÂë 
			{
				// Ê×ÏÈ£¬²éÕÒ¾ßÓĞ×ó×ÓÊ÷ÖĞµÄ×î´óÖµ£¨»òÕßÓÒ×ÓÊ÷ÖĞµÄ×îĞ¡Öµ£©µÄÄ¿±ê½áµã£¬²¢±£Áô¸ÃÖµËùÔÚ½áµãµÄ¸¸½áµã 
				TreeNode *now=root->left;
				TreeNode *nowprev=root;
				while(now->right)
				{
					nowprev=now;
					now=now->right;
				}
				// È»ºó£¬½«¸ÃÖµºÍ´ıÉ¾³ıµÄ½áµãµÄÖµ»¥»»£¨Ê¹ÓÃ×ó×ÓÊ÷ÖĞ×î´óÖµ»òÕßÓÒ×ÓÊ÷ÖĞ×îĞ¡ÖµµÄÄ¿µÄ¶¼ÊÇ±£Ö¤ÔÚ½»»»ºóÈÔÈ»ÄÜ¹»Î¬³Ö¶ş²æËÑË÷Ê÷µÄĞÔÖÊ£© 
				int temp=root->val;
				root->val=now->val;
				now->val=temp;
				// ×îºó£¬É¾³ıÄ¿±ê½áµã£¨°´ÕÕÇ°Á½ÖÖ¹æÔò£©£¬ÒòÎªÄ¿±ê½áµã×î¶àÖ»ÓĞÒ»¸ö×ÓÊ÷
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
	if(p->val>q->val)   // È·±£p½áµãµÄÖµ½ÏĞ¡£¬q½áµãµÄÖµ½Ï´ó 
	{
		TreeNode *temp=p;
		p=q;
		q=p;
	}
	
	function<TreeNode*(TreeNode *, TreeNode *, TreeNode *)> func = [&](TreeNode *root, TreeNode *p, TreeNode *q) {
		if(!root)                   // µ±Ç°Ê÷Îª¿Õ£¬²»´æÔÚlca 
		return static_cast<TreeNode *>(NULL);
		else if(root->val<p->val)   // µ±Ç°½áµãµÄÖµĞ¡ÓÚÁ½½áµãÖĞµÄ½ÏĞ¡Öµ£¬Ôòlca±Ø¶¨ÔÚµ±Ç°½áµãµÄÓÒ×ÓÊ÷ÖĞ
		return func(root->right, p, q);
		else if(root->val>q->val)   // µ±Ç°½áµãµÄÖµ´óÓÚÁ½½áµãÖĞµÄ½Ï´óÖµ£¬Ôòlca±Ø¶¨ÔÚµ±Ç°½áµãµÄ×ó×ÓÊ÷ÖĞ
		return func(root->left, p, q);
		else                        // µ±Ç°½áµãµÄÖµÔÚ½áµãpºÍ½áµãqÖ®¼ä£¬Ôòlca¾ÍÊÇµ±Ç°½áµã 
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
			// ÈôÊ÷²»Îª¿Õ£¬Ôò×î´óÂ·¾¶µÄ´æÔÚ¿ÉÄÜ´æÔÚÈçÏÂÈıÖÖÇé¿ö
			int first=maxrlpath(root->left)+maxrlpath(root->right)+root->val;   // µÚÒ»ÖÖÇé¿ö£º×î³¤Â·¾¶¿çÔ½×ó×ÓÊ÷ºÍÓÒ×ÓÊ÷ 
			int second=func(root->left);    // µÚ¶şÖÖÇé¿ö: ×î³¤Â·¾¶½öÔÚ×ó×ÓÊ÷ÖĞ 
			int third=func(root->right);    // µÚÈıÖÖÇé¿ö: ×î³¤Â·¾¶½öÔÚÓÒ×ÓÊ÷ÖĞ
			
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
