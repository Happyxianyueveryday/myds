#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>

using namespace std;

struct TreeNode
{
    TreeNode(int ival=0):val(ival),left(NULL),right(NULL)
    {
    }

    int val;
    TreeNode *left;
    TreeNode *right;
};

class Tree
{
    public:
    // 1. 构造函数
    Tree();     // 默认构造函数
    Tree(vector<int> inorder, vector<int> preorder);              // 从中序遍历和前序遍历构造二叉搜索树
    Tree(vector<int> inorder, vector<int> postorder, int flag);   // 从中序遍历和后序遍历构造二叉搜索树，flag仅为区分两类的构造的哑参数

    // 2. 拷贝控制
    Tree(const Tree &other);                  // 拷贝构造函数
    Tree & operator = (const Tree &other);    // 拷贝赋值运算符

    // 3. 功能函数
    vector<int> preorder() const;             // 非递归的前序遍历
    vector<int> inorder() const;              // 非递归的中序遍历
    vector<int> postorder() const;            // 非递归的后序遍历
    vector<int> levelorder() const;           // 树的层次遍历

    void insert(int val);                     // 向树插入结点
    void remove(int val);                     // 从树删除结点
    TreeNode *search(int val);                // 在树中根据值查找结点的地址
    TreeNode *getroot() const;                // 获取二叉搜索树的根结点地址，注意声明为const成员函数

    TreeNode *lca(TreeNode *p, TreeNode *q);  // 在二叉搜索树中查找两个结点(以地址形式给出)的最近公共父节点
    TreeNode *lca(int p, int q);              // 在二叉搜索树中查找两个结点(以值形式给出)的最近公共父节点

    int depth();                              // 计算树的最大深度/高度
    int size();                               // 计算树的结点个数
    int maxpath();                            // 计算树中的最大路径和(这里将当前树视为普通二叉树)
    int maxrlpath();                          // 计算树中从根节点到叶子结点的最大路径和

    // 4. 析构函数
    ~Tree();                                  // 树的析构函数

    private:
    TreeNode *treeroot;                       // 树的根结点

    TreeNode *__buildTree1(vector<int> &inorder, vector<int> &preorder);
    TreeNode *__buildTree2(vector<int> &inorder, vector<int> &postorder);
    TreeNode *__copyTree(TreeNode *root);
    void __deleteTree(TreeNode *root);
    int __findIndex(const vector<int> &lis, int tar);
    TreeNode *__insertTree(TreeNode *root, int val);
    TreeNode *__searchTree(TreeNode *root, int val);
    TreeNode *__deleteTree(TreeNode *root, int val);
    TreeNode *__lcaTree1(TreeNode *root, TreeNode *p, TreeNode *q);
    TreeNode *__lcaTree2(TreeNode *root, int p, int q);
    int __depthTree(TreeNode *root);
    int __sizeTree(TreeNode *root);
    int __maxrlpathTree(TreeNode *root);
    int __maxpathTree(TreeNode *root);
};


/*
 * Tree: 默认构造函数
*/
Tree::Tree()
{
    treeroot=NULL;    // 默认构造函数构造一颗空的二叉搜索树
}


/*
 * Tree: 从中序遍历和前序遍历构造二叉搜索树
*/
Tree::Tree(vector<int> inorder, vector<int> preorder)
{
    treeroot=__buildTree1(inorder,preorder);
}


/*
 * Tree: 从中序遍历和后序遍历构造二叉搜索树
*/
Tree::Tree(vector<int> inorder, vector<int> postorder, int flag)
{
    treeroot=__buildTree2(inorder, postorder);
}


/*
 * __buildTree1: 从中序遍历和前序遍历构造二叉搜索树的底层递归实现
 * param inorder: 中序遍历序列
 * param preorder: 前序遍历序列
*/
TreeNode *Tree::__buildTree1(vector<int> &inorder, vector<int> &preorder)
{
    // 0. 处理特殊情况
    if(!preorder.size()||!inorder.size())
    return NULL;

    // 1. 从前序遍历的首元素取得根节点
    int rootval=preorder[0];
    TreeNode *root=new TreeNode(rootval);

    // 2. 在中序遍历序列中查找根结点的值，将中序遍历序列分为左右两个部分
    vector<int> left, right;
    int index=__findIndex(inorder, rootval);

    for(int i=0;i<inorder.size();i++)
    {
    	if(i<index)
    	left.push_back(inorder[i]);
    	if(i>index)
    	right.push_back(inorder[i]);
	}

    // 3. 在前序遍历序列中弹出根结点，由前序遍历序列的前半部分和中序遍历序列构造根节点的左子树，同理可以使用前序遍历序列的后半部分和中序遍历序列构造根节点的右子树
    preorder.erase(preorder.begin());
    root->left=__buildTree1(left, preorder);
    root->right=__buildTree1(right, preorder);

    return root;
}


/*
 * __buildTree2: 从中序遍历和后序遍历构造二叉搜索树的底层递归实现
 * param inorder: 中序遍历序列
 * param postorder: 后序遍历序列
*/
TreeNode *Tree::__buildTree2(vector<int> &inorder, vector<int> &postorder)
{
    // 0. 处理特殊情况
    if(!inorder.size()||!postorder.size())
    return NULL;

    // 1. 由后序遍历的最后一个元素构造树的根节点
    int rootval=postorder[postorder.size()-1];
    TreeNode *root=new TreeNode(rootval);

    // 2. 在中序遍历序列中查找根节点的值，将中序遍历序列分为左右两个部分
    vector<int> left, right;
    int index=__findIndex(inorder, rootval);

    for(int i=0;i<inorder.size();i++)
    {
    	if(i<index)
    	left.push_back(inorder[i]);
    	if(i>index)
    	right.push_back(inorder[i]);
	}

    // 3. 在后序遍历序列中弹出根结点，由后序遍历序列的前半部分和中序遍历序列构造根节点的左子树，同理可以使用后序遍历序列的后半部分和中序遍历序列构造根节点的右子树
    postorder.pop_back();

    root->right=__buildTree2(right, postorder);   // 易错点：后序遍历中构造顺序必须相反，即先构造右子树再构造左子树，只要简单思考一下后序遍历的定义即可理解
    root->left=__buildTree2(left, postorder);

    return root;
}


/*
 * Tree: 拷贝构造函数
*/
Tree::Tree(const Tree &other)
{
    treeroot=__copyTree(other.treeroot);
}


/*
 * __copyTree: 树的拷贝的底层递归实现
*/
TreeNode *Tree::__copyTree(TreeNode *other)
{
    // 0. 处理特殊情况
    if(!other)
    return NULL;

    // 1. 拷贝根结点
    TreeNode *root=new TreeNode(other->val);

    // 2. 递归地拷贝左子树和右子树
    root->left=__copyTree(other->left);
    root->right=__copyTree(other->right);

    return root;
}


/*
 * operator =: 拷贝赋值运算符
*/
Tree & Tree::operator = (const Tree &other)
{
    // 0. 处理自我赋值问题
    if(this==&other)
    return (*this);

    // 1. 递归释放当前对象的树
    __deleteTree(treeroot);

    // 2. 拷贝源对象的树到当前对象中
    treeroot=__copyTree(other.treeroot);

    return (*this);
}


/*
 * __deleteTree: 删除树指针并释放内存
*/
void Tree::__deleteTree(TreeNode *root)
{
	if(!root)
	return;

	else
	{
		// 1. 首先释放根结点的左子树和右子树
		__deleteTree(root->left);
		__deleteTree(root->right);

		// 2. 最后释放根结点
		delete root;
	}
}


/*
 * preorder: 二叉树的非递归前序遍历
*/
vector<int> Tree::preorder() const
{
	vector<int> res;

	// 0. 处理特殊情况
	if(!treeroot)
	return res;

    // 1. 创建一个遍历使用的栈，并将根结点入栈
    stack<TreeNode *> sta;
    sta.push(treeroot);

    // 2. 循环进行以下步骤直到栈为空为止：首先从栈顶取一个结点，输出该结点，然后分别依次将该结点的非空右子结点和左子结点入栈
    while(sta.size())
    {
        TreeNode *temp=sta.top();
        sta.pop();

        res.push_back(temp->val);

        if(temp->right)
        sta.push(temp->right);
        if(temp->left)
        sta.push(temp->left);
    }

    return res;
}


/*
 *  inorder: 二叉树的非递归中序遍历
*/
vector<int> Tree::inorder() const
{
    vector<int> res;

    // 0. 处理特殊情况
	if(!treeroot)
	return res;

    // 1. 创建一个遍历使用的栈，并从根结点沿着左子结点的路径上的所有结点全部依次入栈
    stack<TreeNode *> sta;
    TreeNode *now=treeroot;

    while(now)
    {
        sta.push(now);
        now=now->left;
    }

    // 2. 循环进行以下步骤直到栈为空为止：从栈中出栈栈顶结点，输出栈顶结点，然后从该结点的右子结点开始沿着左子节点路径上的所有结点依次入栈
    while(sta.size())
    {
        TreeNode *temp=sta.top();
        sta.pop();

        res.push_back(temp->val);

        temp=temp->right;
        while(temp)
        {
            sta.push(temp);
            temp=temp->left;
        }
    }

    return res;
}


/*
 *  postorder: 二叉树的非递归后序遍历
*/
vector<int> Tree::postorder() const
{
    // 0. 处理特殊情况
    vector<int> res;
    if(!treeroot)
    return res;

    // 1. 创建一个遍历使用的栈，从根结点开始沿着左子结点的方向访问，将途经的结点(包括空结点)加入栈中
    stack<TreeNode *> sta;
    TreeNode *now=treeroot;

    while(now)
    {
        sta.push(now);
        now=now->left;
    }
    sta.push(now);

    // 2. 循环进行以下步骤直到栈为空为止：首先从栈顶出栈一个元素并输出(如果出栈的结点非空)，然后从当前栈顶结点的右子树开始，沿着左子节点路径上的结点依次入栈
    while(sta.size())
    {
        TreeNode *temp=sta.top();
        sta.pop();

        if(temp)
        res.push_back(temp->val);

		// 需要特别注意非递归后序遍历实现的两个特别判断条件，就在于此：
		// 1. 若刚刚出栈的结点就是出栈后栈顶结点的右子结点，则说明栈顶结点的右子结点已经输出过，故这时无需继续将其重复入栈
		// 2. 若出栈一个元素后栈为空，则直接返回到循环条件处进行
        if(!sta.size()||temp==sta.top()->right)
        continue;

        TreeNode *now=sta.top()->right;

        while(now)
        {
            sta.push(now);
            now=now->left;
        }
        sta.push(now);
    }

    return res;
}


/*
 *  levelorder: 二叉树的非递归后序遍历
*/
vector<int> Tree::levelorder() const
{
    // 0. 处理特殊情况
    vector<int> res;
    if(!treeroot)
    return res;

    // 1. 创建一个用于遍历的队列，将根结点入队
    queue<TreeNode *> que;
    que.push(treeroot);

    // 2. 重复进行以下步骤直到队列为空：从数列中出队队首结点，然后依次将出队结点非空的左子结点和右子结点加入队列
    while(que.size())
    {
        TreeNode *temp=que.front();
        que.pop();

        res.push_back(temp->val);

        if(temp->left)
        que.push(temp->left);
        if(temp->right)
        que.push(temp->right);
    }

    return res;
}


/*
 * __findIndex: 根据值查找在数组中的下标
*/
int Tree::__findIndex(const vector<int> &lis, int tar)
{
	for(int i=0;i<lis.size();i++)
	{
		if(lis[i]==tar)
		return i;
	}

	return -1;
}


/*
 * insert: 向树中插入结点
*/
void Tree::insert(int val)
{
	__insertTree(treeroot,val);
}

/*
 * __insertTree: 树中插入结点的底层递归实现
*/
TreeNode *Tree::__insertTree(TreeNode *root, int val)
{
	if(!root)
	{
		TreeNode *newnode=new TreeNode(val);
		return newnode;
	}
	else if(val>root->val)
	root->right=__insertTree(root->right,val);
	else if(val<=root->val)
	root->left=__insertTree(root->left,val);

	return root;
}


/*
 * remove: 从树中移除等于给定值的结点
*/
void Tree::remove(int val)
{
	treeroot=__deleteTree(treeroot,val);
}

TreeNode *Tree::__deleteTree(TreeNode *root, int val)
{
	if(!root)
	return NULL;
	else if(val>root->val)
	root->right=__deleteTree(root->right,val);
	else if(val<root->val)
	root->left=__deleteTree(root->left,val);
	else
	{
		// 已经查找到了目标结点，下面进行删除操作
		// 1. 若待删除的结点既没有左子结点也没有右子结点，则直接删除该结点，返回NULL
		if(!root->left&&!root->right)
		{
			delete root;
			return NULL;
		}
		// 2. 若待删除的结点既有左子结点也有右子结点，则首先查找左子树中的最大值或者右子树中的最小值结点tar，然后将结点tar的值和待删除结点的值交换，最后删除结点tar
		// 附注: 关于为什么选择左子树中的最大值或者右子树中的最小值来取代待删除结点的值，原因是为了保持取代原值后，保持二叉搜索树的基本性质——左子树的值均小于根结点，右子树的值均大于根结点
		else if(root->left&&root->right)
		{
			// 2.1 首先先查找到左子树中的最大值
			TreeNode *tar=root->left;  // 左子树中的最大值结点tar
			TreeNode *parent=root;     // 记录结点tar的父结点
			while(tar->right)
			{
				parent=tar;
				tar=tar->right;
			}

			// 2.2 交换结点tar和当前结点root的值
			int temp=tar->val;
			tar->val=root->val;
			root->val=temp;

			// 2.3 删除结点tar，因为结点tar是原先左子树中的最大值，即左子树中最右侧的结点，因此其最多只有左子结点，从而将问题递归地转化为待删除结点只有一个子结点地情况
			// 附注: 这一步容易出现错误，即直接将parent->right=NULL; 需要特别注意，找到的这个左子树中的最大值结点同样可能有最多一个子结点
			parent->right=tar->left;
			delete tar;

			// 2.4 直接返回当前结点，因为当前结点的存储未被真正删除
			return root;
		}
		// 3. 若待删除的结点具有左子结点和右子结点之中的一个，则删除目标结点，删除后，由其左子树或右子树占据原先删掉的结点的位置，即返回左子字节或者右子结点
		else
		{
			TreeNode *temp=(root->left)?root->left:root->right;
			delete root;
			return temp;
		}
	}

	return root;
}


/*
 * search: 在树中查找对应值的结点地址
*/
TreeNode *Tree::search(int val)
{
	return __searchTree(treeroot,val);
}

/*
 * __searchTree: 查找树结点的底层递归实现
*/
TreeNode *Tree::__searchTree(TreeNode *root, int val)
{
	if(!root)
	return NULL;
	else if(val>root->val)
	return __searchTree(root->right, val);
	else if(val<root->val)
	return __searchTree(root->left, val);
	else
	return root;
}


/*
* lca: 查找树中两个结点地址的最近公共祖先/最近公共父结点(lca)
*/
TreeNode *Tree::lca(TreeNode *p, TreeNode *q)
{
	return __lcaTree1(treeroot, p, q);
}

TreeNode *Tree::__lcaTree1(TreeNode *root, TreeNode *p, TreeNode *q)
{
	// 这里换用在普通二叉树(不一定是完全二叉树)中查找最近公共祖先的算法

	// 0. 若根结点为空，则直接返回NULL，表明查找失败
	if(!root)
	return NULL;
	else if(root==p||root==q)  // 标记*
	return root;
	else
	{
		// 1. 首先在当前结点的左右子树中分别查找p和q的最近公共祖先，注意结点p或者q自身也是自身的最近公共祖先
		TreeNode *left=__lcaTree1(root->left, p, q);     // 在左子树中查找p和q的最近公共祖先
		TreeNode *right=__lcaTree1(root->right, p, q);   // 在左子树中查找p和q的最近公共祖先

		// 2. 若在左子树中查找到了p和q的最近公共祖先，则结点p和结点q都在当前结点root的左子树中，直接返回left即可
		if(left&&!right)
		return left;

		// 3. 若在右子树中查找到了p和q的最近公共祖先，则结点p和q都在当前结点root的右子树中，直接返回right即可
		else if(!left&&right)
		return right;

		// 4. 若在左子树和右子树中都查找到了p和q的最近公共祖先，这时说明结点p和结点q分别在两个子树中，见上面*标记的代码段，因此返回当前结点root作为最近公共祖先
		else if(left&&right)
		return root;

		// 5. 左右子树中查找的结果都是NULL，则结果不存在，因此直接返回NULL
		else
		return NULL;
	}
}


/*
* lca: 查找树中两个值的最近公共祖先/最近公共父结点(lca)
*/
TreeNode *Tree::lca(int p, int q)
{
	return __lcaTree2(treeroot, p, q);
}

TreeNode *Tree::__lcaTree2(TreeNode *root, int p, int q)
{
	// 在二叉搜索树中查找最近公共祖先的算法

	// 0. 统一设置p为两个数中的较小值，q为两个数中的较大值
	if(p>q)
	{
		int temp=p;
		p=q;
		q=temp;
	}

	// 1. 若当前结点root为空，则查找失败，直接返回NULL
	if(!root)
	return NULL;

	// 2. 若当前结点root的值大于较大值q，则结点p和q的最近公共祖先在当前结点的左子树root->left中
	else if(root->val>q)
	return __lcaTree2(root->left, p, q);

	// 3. 若当前结点root的值小于较小值p，则结点p和q的最近公共祖先在当前结点的右子树root->right中
	else if(root->val<p)
	return __lcaTree2(root->right, p, q);

	// 4. 若当前结点root的值介于q和p之间，则当前结点root就是最终所求的p和q的最近公共祖先
	else
	return root;
}


/*
 * depth: 计算树的深度
*/
int Tree::depth()
{
	return __depthTree(treeroot);
}

int Tree::__depthTree(TreeNode *root)
{
	if(!root)
	return 0;
	else if(!root->left&&!root->right)
	return 1;
	else
	{
		int left=__depthTree(root->left);
		int right=__depthTree(root->right);

		return ((left>right)?left:right)+1;
	}
}


/*
* size: 计算二叉树的结点个数
*/
int Tree::size()
{
	return __sizeTree(treeroot);
}

int Tree::__sizeTree(TreeNode *root)
{
	if(!root)
	return 0;
	else if(!root->left&&!root->right)
	return 1;
	else
	return 1+__sizeTree(root->left)+__sizeTree(root->right);
}


/*
* maxrlpath: 计算二叉树从根结点到叶子结点的结点值之和最大的路径
*/
int Tree::maxrlpath()
{
	return __maxrlpathTree(treeroot);
}

int Tree::__maxrlpathTree(TreeNode *root)
{
	if(!root)
	return 0;
	else if(!root->left&&!root->right)
	return root->val;
	else
	{
		int left=__maxrlpathTree(root->left);
		int right=__maxrlpathTree(root->right);

		return ((left>right)?left:right) + root->val;   // 注意三元运算符必须使用括号括起来，否则相当于: (left>right)?left:(right+root->val)，会出现逻辑错误
	}
}


/*
* maxpath: 计算树中的最长路径和
*/
int Tree::maxpath()
{
	return __maxpathTree(treeroot);
}

int Tree::__maxpathTree(TreeNode *root)
{
	// 计算二叉树中结点值之和最大的路径的算法较为简单：最大路径要么只在根结点的左子树中，要么只在根结点的右子树中，要么通过根结点，横跨左右两个子树
	if(!root)
	return 0;
	else if(!root->left&&!root->right)
	return root->val;
	else
	{
		int left=__maxpathTree(root->left);         // 第一种情况: 最大路径只存在于根结点的左子树中
		int right=__maxpathTree(root->right);       // 第二种情况: 最大路径只存在于根结点的右子树中
		// 第三种情况: 最大路径横跨左子树，根结点和右子树，这时相当于左子树中从根节点到叶子结点的最大路径值加上根节点的值加上右子树中从根节点到叶子结点的最大路径值
		int lr=__maxrlpathTree(root->left) + root->val + __maxrlpathTree(root->right);

		return ((left>right)?((left>lr)?left:lr):((right>lr)?right:lr));   // 三种情况中的最大值就是所求的最大路径
	}
}

TreeNode *Tree::getroot() const
{
	return treeroot;
}

/*
 * ~Tree: 析构函数
*/
Tree::~Tree()
{
	__deleteTree(treeroot);
}
