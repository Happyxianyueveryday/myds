#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

/**
 * TreeNode: ʹ�ú����ֵܱ�ʾ���Ķ�����Ľ��
 */
struct TreeNode
{
    TreeNode(int _val):val(_val),child(NULL),brother(NULL)
    {
    }

    int val;                   // ��ǰ����ֵ
    TreeNode *child;           // ��ǰ���ĺ���
    TreeNode *brother;         // ��ǰ�����ֵ�
};

struct BinaryTreeNode
{
    BinaryTreeNode(int _val):val(_val),left(NULL),right(NULL)
    {
    }

    int val;          // ��ǰ����ֵ
    BinaryTreeNode *left;   // ��ǰ����ָ����������ָ��
    BinaryTreeNode *right;  // ��ǰ����ָ����������ָ��
};

/**
 * MultiTree: ʹ�ú����ֵܷ���ʾ�Ķ����
 */
class MultiTree
{
    public:
    // 1. constructors
    MultiTree();                                               // Ĭ�Ϲ��캯��������յĶ����
    MultiTree(vector<int> preorder, vector<int> postorder);    // ���캯�������ݶ�������ȸ������ͺ������Ψһȷ������������

    // 2. copy controllers
    MultiTree(const MultiTree &other) = delete;                // ���ÿ������캯��
    MultiTree & operator = (const MultiTree &other) = delete;  // ���ÿ�����ֵ�����
    
    // 3. methods
    vector<int> preorder();      // ��������ȸ�����
    vector<int> postorder();     // ������ĺ������
    vector<int> levelorder();    // ������Ĳ�α���
    BinaryTreeNode *convertToBinaryTree();   // ����ǰ�����ת��Ϊ��Ӧ�Ķ�����

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
 * MultiTree: �������Ĭ�Ϲ��캯��������յĶ����
 */
MultiTree::MultiTree()
{
    treeroot=NULL;
}

/**
 * MultiTree: ������Ĺ��캯�������ݶ�������ȸ��������кͺ����������
 * param preorder: ��������ȸ���������
 * param postorder: ������ĺ����������
 * note 1: ���ڶ�������ԣ�ֻ��Ҫ�ȸ��������кͺ���������о���ȷ�������
 * note 2: ����򵥵Ĳ���˵���£���Ϊ�������ֻ���ڽ��֮��ĸ��ӹ�ϵ�������ӽ���˳��Ӱ�����������ֻ��Ҫʹ���ȸ������ͺ����������ȷ�������Ƕ������в����и��ӹ�ϵ���������ҹ�ϵ��ֻƾ��ǰ������ͺ����������ȷ�����ӹ�ϵ�������޷�ȷ�����ҹ�ϵ����˲���ͨ��ǰ������ͺ������λ��ȷ��������
 * note 3: ������ԣ�����ʹ�õ��㷨���Լ���Ϊ��
           (1) ��ǰ�����ȸ��������еĵ�һ��Ԫ�ؾ��ǵ�ǰ������ֵ
           (2) �ں�����������в��Ҹ�����ֵ��λ�ã��Ӹ�λ�ÿ�ʼ����������λ�ã��������������һ��Ϊ����ǰ�벿�־��ǵ�ǰ������child���ĺ���������У���벿�־��ǵ�ǰ������brother���ĺ����������
           (3) ͳ��������child��brother�ĺ���������ȣ����ȸ��������е���Ԫ��֮�����ν�ȡ��Ӧ���ȵ����У��ͷֱ�õ�child��brother���ȸ���������
           (4) ���ݵ�ǰ������ֵ���������
           (5) ����֮ǰ���ɵ�child���ȸ��ͺ���������еݹ�����childָ����ָ��Ķ������ͬ������֮ǰ���ɵ�brother���ȸ��ͺ���������еݹ�����brotherָ����ָ��Ķ����
 */
MultiTree::MultiTree(vector<int> preorder, vector<int> postorder)
{
    treeroot=__buildTree(preorder, postorder);
}

TreeNode *MultiTree::__buildTree(vector<int> preorder, vector<int> postorder)
{
	if(preorder.size()==0||postorder.size()==0)
	return NULL;
	
    // 1. ���ȸ������в��Ҷ�����ĸ�����ֵ
    int rootval=preorder[0];

    // 2. �ں�������в��ҵ�ǰ������λ��
    int index=-1;
    for(int i=0;i<postorder.size();i++)
    {
        if(postorder[i]==rootval)
        {
            index=i;
            break;
        }
    }

    // 3. ������ǰ�����
    TreeNode *root=new TreeNode(rootval);
    // 4. �ֱ����ɵ�ǰ������childָ���brotherָ��ָ����������ֱ������� 
    // 4.1 �������ҵ��ĺ�������е�ǰ������λ��index��ʼ��ԭʼ�����������һ��Ϊ����ǰ��ξ���childָ����ָ������ĺ���������У����ξ���brotherָ����ָ������ĺ���������� 
	// 4.2 �ڶ�Ӧ��ǰ�����������У����պ���������ֵĽ�����ɻ��ֳ�childָ���brotherָ��ֱ��ǰ��������� 
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
	cout<<"��ǰ�����ֵ: rootval = "<<rootval<<endl;
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

    // 5. �ݹ�����ɵ�ǰ������child��brotherָ��
    root->child=__buildTree(child_preorder, child_postorder);
    root->brother=__buildTree(brother_preorder, brother_postorder);

    return root;
}

/**
 * preorder: ���ɵ�ǰ��������ȸ���������
 * return: ��ǰ��������ȸ���������
 * note: ���ɺ����ֵܱ�ʾ���Ķ�������ȸ��������е��㷨��Ҫ����Ϊ:
        (1) ����һ����ʱջ����������ĸ������ջ
        (2) ѭ���������²���ֱ��ջΪ��Ϊֹ: ��ջ����ջ��ǰ��㣻�����ǰ��㣻���ΰ�˳�򽫵�ǰ����brother��childָ��ָ��Ľ����ջ
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
 * postorder: ���ɵ�ǰ������ĺ����������
 * return: ��ǰ������ĺ���������� 
 * note: ���ɺ����ֵܱ�ʾ���Ķ�����ĺ���������е��㷨����Ҫ������Ա���Ϊ:
        (1) ����һ����ʱջ���Ӹ���㿪ʼ����child�ķ���ֱ���ս�㣬��;���Ľ��ȫ��������ջ
        (2) ѭ���������²���ֱ��ջΪ��Ϊֹ: 
            (a) ��ջ����ջ��ǰ���now
            (b) �����ǰ���now
            (c) ��now->brother��ʼ������child�ķ���ֱ���ս�㣬��;���Ľ��ȫ��������ջ
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
 * levelorder: ���ɵ�ǰ������Ĳ�α�������
 * return: ��ǰ������Ĳ�α�������
 * note: ���ɺ����ֵܱ�ʾ���Ķ�����ĺ���������е��㷨����Ҫ������Ա���Ϊ:
        (1) �����ǰ���
		(2) �ݹ���ʵ�ǰ����brotherָ����ָ��Ľ��
		(3) �ݹ���ʵ�ǰ����childָ����ָ��Ľ�� 
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
 * convertToTree: ����ǰ�Ķ����ת��Ϊ������
 * return: �ӵ�ǰ��������ɵĶ�����
 * note: �Ӷ��������ɶ��������㷨��Ϊ�򵥣�ֱ�Ӱ��չ涨���ɣ����ĵ��㷨������Ա���Ϊ:
        (1) ���ɵ�ǰ����Ӧ��ֵ��ȵĶ��������
        (2) ����������������root->left���ǵ�ǰ����childָ��ָ�������
        (3) ����������������root->right���ǵ�ǰ����brotherָ��ָ�������
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
 * MultiTree: ���������������
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

