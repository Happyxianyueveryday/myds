#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

/**
 * TreeNode: 使用孩子兄弟表示法的多叉树的结点
 */
struct TreeNode
{
    TreeNode(int _val):val(_val),child(NULL),brother(NULL)
    {
    }

    int val;                   // 当前结点的值
    TreeNode *child;           // 当前结点的孩子
    TreeNode *brother;         // 当前结点的兄弟
};

struct BinaryTreeNode
{
    BinaryTreeNode(int _val):val(_val),left(NULL),right(NULL)
    {
    }

    int val;          // 当前结点的值
    BinaryTreeNode *left;   // 当前结点的指向左子树的指针
    BinaryTreeNode *right;  // 当前结点的指向右子树的指针
};

/**
 * MultiTree: 使用孩子兄弟法表示的多叉树
 */
class MultiTree
{
    public:
    // 1. constructors
    MultiTree();                                               // 默认构造函数，构造空的多叉树
    MultiTree(vector<int> preorder, vector<int> postorder);    // 构造函数，根据多叉树的先根遍历和后根遍历唯一确定并构造多叉树

    // 2. copy controllers
    MultiTree(const MultiTree &other) = delete;                // 禁用拷贝构造函数
    MultiTree & operator = (const MultiTree &other) = delete;  // 禁用拷贝赋值运算符
    
    // 3. methods
    vector<int> preorder();      // 多叉树的先根遍历
    vector<int> postorder();     // 多叉树的后根遍历
    vector<int> levelorder();    // 多叉树的层次遍历
    BinaryTreeNode *convertToBinaryTree();   // 将当前多叉树转换为对应的二叉树

    // 4. destructor
    ~MultiTree();

    private:
    // 5. domains
    TreeNode *treeroot;

    TreeNode *__buildTree(vector<int> preorder, vector<int> postorder);
    void __realLevelorder(vector<int> &res, TreeNode *root);
    BinaryTreeNode *__realConvertToBinaryTree(TreeNode *root);
};

/**
 * MultiTree: 多叉树的默认构造函数，构造空的多叉树
 */
MultiTree::MultiTree()
{
    treeroot=NULL;
}

/**
 * MultiTree: 多叉树的构造函数，根据多叉树的先根遍历序列和后根遍历序列
 * param preorder: 多叉树的先根遍历序列
 * param postorder: 多叉树的后根遍历序列
 * note 1: 对于多叉树而言，只需要先根遍历序列和后根遍历序列就能确定多叉树
 * note 2: 这里简单的补充说明下，因为多叉树中只存在结点之间的父子关系，而孩子结点的顺序不影响多叉树，因此只需要使用先根遍历和后根遍历即可确定。但是二叉树中不仅有父子关系，还有左右关系，只凭借前序遍历和后序遍历可以确定父子关系，但是无法确定左右关系，因此不能通过前序遍历和后序遍历位异确定二叉树
 * note 3: 具体而言，本题使用的算法可以简述为：
           (1) 当前树的先根遍历序列的第一个元素就是当前根结点的值
           (2) 在后根遍历序列中查找根结点的值的位置，从该位置开始（不包括该位置）将后根遍历序列一分为二，前半部分就是当前根结点的child树的后根遍历序列，后半部分就是当前根结点的brother树的后根遍历序列
           (3) 统计上述的child和brother的后根遍历长度，从先根遍历序列的首元素之后依次截取对应长度的序列，就分别得到child和brother的先根遍历序列
           (4) 根据当前根结点的值创建根结点
           (5) 根据之前生成的child的先根和后根遍历序列递归生成child指针所指向的多叉树，同理，根据之前生成的brother的先根和后根遍历序列递归生成brother指针所指向的多叉树
 */
MultiTree::MultiTree(vector<int> preorder, vector<int> postorder)
{
    treeroot=__buildTree(preorder, postorder);
}

TreeNode *MultiTree::__buildTree(vector<int> preorder, vector<int> postorder)
{
	if(preorder.size()==0||postorder.size()==0)
	return NULL;
	
    // 1. 从先根遍历中查找多叉树的根结点的值
    int rootval=preorder[0];

    // 2. 在后根遍历中查找当前根结点的位置
    int index=-1;
    for(int i=0;i<postorder.size();i++)
    {
        if(postorder[i]==rootval)
        {
            index=i;
            break;
        }
    }

    // 3. 创建当前根结点
    TreeNode *root=new TreeNode(rootval);
    // 4. 分别生成当前根结点的child指针和brother指针指向的树的两种遍历序列 
    // 4.1 从上述找到的后根遍历中当前根结点的位置index开始将原始后根遍历序列一分为二，前半段就是child指针所指向的树的后根遍历序列，后半段就是brother指针所指向的树的后根遍历序列 
	// 4.2 在对应的前根遍历序列中，按照后根遍历划分的结果即可划分出child指针和brother指针分别的前序遍历序列 
    vector<int> child_postorder, brother_postorder;
    vector<int> child_preorder, brother_preorder;

    for(int i=0;i<postorder.size();i++)
    {
        if(i<index)
        child_postorder.push_back(postorder[i]);
        else if(i>index)
        brother_postorder.push_back(postorder[i]);
    }

    for(int i=1;i<preorder.size();i++)
    {
        if(i>=1&&i<child_postorder.size()+1)
        child_preorder.push_back(preorder[i]);
        else
        brother_preorder.push_back(preorder[i]);
    }
	
	/*
	cout<<"当前根结点值: rootval = "<<rootval<<endl;
    for(int i=0;i<child_preorder.size();i++)
    {
        cout<<child_preorder[i]<<" ";
    }
    cout<<endl;
    for(int i=0;i<child_postorder.size();i++)
    {
        cout<<child_postorder[i]<<" ";
    }
    cout<<endl;
    for(int i=0;i<brother_preorder.size();i++)
    {
        cout<<brother_preorder[i]<<" ";
    }
    cout<<endl;
    for(int i=0;i<brother_postorder.size();i++)
    {
        cout<<brother_postorder[i]<<" ";
    }
    cout<<endl;
    cout<<"-----------------------"<<endl;
    */

    // 5. 递归地生成当前根结点的child和brother指针
    root->child=__buildTree(child_preorder, child_postorder);
    root->brother=__buildTree(brother_preorder, brother_postorder);

    return root;
}

/**
 * preorder: 生成当前多叉树的先根遍历序列
 * return: 当前多叉树的先根遍历序列
 * note: 生成孩子兄弟表示法的多叉树的先根遍历序列的算法主要步骤为:
        (1) 创建一个临时栈，将多叉树的根结点入栈
        (2) 循环进行以下步骤直到栈为空为止: 从栈顶出栈当前结点；输出当前结点；依次按顺序将当前结点的brother和child指针指向的结点入栈
 */
vector<int> MultiTree::preorder()
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

        if(now->brother)
        sta.push(now->brother);
        if(now->child)
        sta.push(now->child);
    }
    
    return res;
}

/**
 * postorder: 生成当前多叉树的后根遍历序列
 * return: 当前多叉树的后根遍历序列 
 * note: 生成孩子兄弟表示法的多叉树的后根遍历序列的算法，主要步骤可以表述为:
        (1) 创建一个临时栈，从根结点开始沿着child的方向直到空结点，将途径的结点全部依次入栈
        (2) 循环进行以下步骤直到栈为空为止: 
            (a) 从栈顶出栈当前结点now
            (b) 输出当前结点now
            (c) 从now->brother开始，沿着child的方向直到空结点，将途径的结点全部依次入栈
 */
vector<int> MultiTree::postorder()
{
    vector<int> res;
    if(!treeroot)
    return res;

    stack<TreeNode *> sta;

    TreeNode *temp=treeroot;
    while(temp)
    {
        sta.push(temp);
        temp=temp->child;
    }

    while(sta.size())
    {
        TreeNode *now=sta.top();
        sta.pop();

        res.push_back(now->val);

        TreeNode *temp=now->brother;

        while(temp)
        {
            sta.push(temp);
            temp=temp->child;
        }
    }

    return res;
}

/**
 * levelorder: 生成当前多叉树的层次遍历序列
 * return: 当前多叉树的层次遍历序列
 * note: 生成孩子兄弟表示法的多叉树的后根遍历序列的算法，主要步骤可以表述为:
        (1) 输出当前结点
		(2) 递归访问当前结点的brother指针所指向的结点
		(3) 递归访问当前结点的child指针所指向的结点 
 */
vector<int> MultiTree::levelorder()
{
	vector<int> res;
	__realLevelorder(res, treeroot);
	
	return res;
}

void MultiTree::__realLevelorder(vector<int> &res, TreeNode *root)
{
	if(!root)
	return;
	
	res.push_back(root->val);
	__realLevelorder(res, root->brother);
	__realLevelorder(res, root->child);
	
	return;
}

/**
 * convertToTree: 将当前的多叉树转换为二叉树
 * return: 从当前多叉树生成的二叉树
 * note: 从二叉树生成二叉树的算法较为简单，直接按照规定即可，核心的算法步骤可以表述为:
        (1) 生成当前结点对应的值相等的二叉树结点
        (2) 二叉树结点的左子树root->left就是当前结点的child指针指向的子树
        (3) 二叉树结点的右子树root->right就是当前结点的brother指针指向的子树
 */
BinaryTreeNode *MultiTree::convertToBinaryTree()
{
    return __realConvertToBinaryTree(treeroot);
}

BinaryTreeNode *MultiTree::__realConvertToBinaryTree(TreeNode *root)
{
    if(!root)
    return NULL;
    
    BinaryTreeNode *res=new BinaryTreeNode(root->val);
    res->left=__realConvertToBinaryTree(root->child);
    res->right=__realConvertToBinaryTree(root->brother);

    return res;
}

/**
 * MultiTree: 多叉树的析构函数
 */
MultiTree::~MultiTree()
{
    if(!treeroot)
    return;

    stack<TreeNode *> sta;
    sta.push(treeroot);

    while(sta.size())
    {
        TreeNode *now=sta.top();
        sta.pop();

        if(now->brother)
        sta.push(now->brother);
        if(now->child)
        sta.push(now->child);
        
        delete now;
    }
}

