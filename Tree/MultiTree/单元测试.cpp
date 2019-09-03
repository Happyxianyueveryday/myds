#include "MultiTree.h" 
#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

vector<int> levelorder(BinaryTreeNode *root)
{
	vector<int> res;
	
	if(!root)	
	return res;
	
	queue<BinaryTreeNode *> que;
	que.push(root);
	
	while(que.size())
	{
		BinaryTreeNode *now=que.front();
		que.pop();
		
		res.push_back(now->val);
		
		if(now->left)
		que.push(now->left);
		if(now->right)
		que.push(now->right);
	}
	
	return res;
}

int main(void)
{
	vector<int> preorder={1,2,5,6,3,4,7};
	vector<int> postorder={5,6,2,3,7,4,1};
	
	MultiTree tree(preorder, postorder);
	
	// 1. ���Զ������ǰ���������� 
	vector<int> pre=tree.preorder();
	for(int i=0;i<pre.size();i++)
	{
		cout<<pre[i]<<" ";
	}
	cout<<endl;
	
	// 2. ���Զ�����ĺ����������
	vector<int> post=tree.postorder();
	for(int i=0;i<post.size();i++)
	{
		cout<<post[i]<<" ";
	}
	cout<<endl;
	
	// 3. ���Զ�����Ĳ�α�������
	vector<int> level=tree.levelorder();
	for(int i=0;i<level.size();i++)
	{
		cout<<level[i]<<" ";
	}
	cout<<endl;
	
	// 4. ���Զ����ת������
	BinaryTreeNode *root=tree.convertToBinaryTree(); 
	vector<int> binary_level=levelorder(root);
	for(int i=0;i<binary_level.size();i++)
	{
		cout<<binary_level[i]<<" ";
	}
	cout<<endl;
	
	// 5. ������������ 
	
}
