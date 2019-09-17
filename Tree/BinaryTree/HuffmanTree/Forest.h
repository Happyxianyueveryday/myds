#include <iostream>
#include <string>
#include "TreeNode.h"

using namespace std;

struct ListNode
{
	ListNode(TreeNode *_val=NULL):node(_val), next(NULL)
	{
	}

    TreeNode *node;
	ListNode *next;
};

/**
 * Forest: 有序森林
 */
class Forest
{
	public:
	// 1. constructor
	Forest();

	// 2. copy controller
	Forest(const Forest &other);                  // 拷贝构造函数
	Forest & operator = (const Forest &other);    // 拷贝赋值运算符

	// 3. methods
	void insert(TreeNode *root);           // 向森林中插入一个树，并保证森林有序，时间复杂度O(n)
	TreeNode *pop();                             // 从森林中取出根结点最小的树，并保证森林有序，时间复杂度O(1)
	int length();                                // 计算并返回森林中树的个数，时间复杂度O(1)

	// 4. destructor
	~Forest();

	// 5. domains
	private:
	ListNode *head;
	int size;
};

/**
 * Forest: 构造一个空的森林，森林中的树以根结点的值从小到大排序
 */
Forest::Forest()
{
	head=new ListNode(NULL);
	size=0;
}

/**
 * Forest: 拷贝构造函数
 */
Forest::Forest(const Forest &other)
{
	head=new ListNode(NULL);
	size=0;

	ListNode *othernow=other.head->next;
	ListNode *now=head->next;

	while(othernow)
	{
		now->next=new ListNode(othernow->node);

		now=now->next;
		othernow=othernow->next;
	}
}

/**
 * operator =: 拷贝赋值运算符
 */
Forest & Forest::operator = (const Forest &other)
{
	if(&other==this)
		return (*this);

	ListNode *temp=head;
	while(temp)
	{
		ListNode *del=temp;
		temp=temp->next;
		delete del;
	}

	head=new ListNode(NULL);
	size=0;

	ListNode *othernow=other.head->next;
	ListNode *now=head->next;

	while(othernow)
	{
		now->next=new ListNode(othernow->node);

		now=now->next;
		othernow=othernow->next;
	}

	return (*this);
}

/**
 * insert: 向森林中增加一个树，并保证森林中树的有序性
 */
void Forest::insert(TreeNode *root)
{
	size+=1;

	// 1. 若要插入的树为空树，则将空树插入到最前，认为空树的值小于任何一个森林中的树
	if(root==NULL)
	{
		ListNode *newnode=new ListNode(root);
		newnode->next=head->next;
		head->next=newnode;
		return;
	}

	ListNode *now=head->next;
	ListNode *nowprev=head;

	while(now)
	{
		if(now->node!=NULL&&now->node->val>=root->val)    // 将新插入的树插入到链表的合适位置，则结点now和nowprev之间
			break;
		else
		{
			nowprev=now;
			now=now->next;
		}
	}

	ListNode *newnode=new ListNode(root);
	newnode->next=now;
	nowprev->next=newnode;

	return;
}

/**
 * pop: 从森林中取出根结点最小的树，并保证森林有序，时间复杂度O(1)
 * return: 森林中当前根结点的值最小的树
 * warning: 本处实现的接口和stl风格相同，必须在森林中存在树的情况下调用该方法，否则恒定返回NULL
 */
TreeNode *Forest::pop()
{
	if(!head->next)
		return NULL;
	else
	{
		ListNode *temp=head->next;
		TreeNode *res=head->next->node;
		head->next=head->next->next;

		delete temp;
		size-=1;

		return res;
	}
}

/**
 * length: 计算并返回森林中树的个数，时间复杂度O(1)
 * return: 森林中树的个数
 */
int Forest::length()
{
	return size;
}

/**
 * ~Forest: 本类的析构函数
 */
Forest::~Forest()
{
	ListNode *now=head;

	while(now)
	{
		ListNode *temp=now;
		now=now->next;
		delete temp;
	}
}

/*
// main：单元测试
int main(void)
{
	Forest forest;

	TreeNode *root1=new TreeNode(1);
	TreeNode *root2=new TreeNode(2);
	TreeNode *root3=new TreeNode(5);
	TreeNode *root4=new TreeNode(6);
	TreeNode *root5=new TreeNode(3);
	TreeNode *root6=new TreeNode(4);
	TreeNode *root7=new TreeNode(3);

	forest.insert(root1);
	forest.insert(root2);
	forest.insert(root3);
	forest.insert(root4);
	forest.insert(root5);
	forest.insert(root6);
	forest.insert(root7);

	while(forest.length())
	{
		cout<<forest.pop()->val<<endl;
	}
}
*/
