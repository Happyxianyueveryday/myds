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
 * InThreadTree: ��������׽�� 
 */
class InThreadTree: public ThreadTree
{
	public: 
	InThreadTree(vector<int> &preorder, vector<int> &inorder);              // ��ǰ������������������������ 
	InThreadTree(vector<int> &postorder, vector<int> &inorder, int num);    // �Ӻ������������������������� 
	InThreadTree(const InThreadTree &other) = delete;
	InThreadTree & operator = (const InThreadTree &other) = delete;        
	ThreadNode *getFirstNode(ThreadNode *now);  // ��ȡ����������������׽�� 
	ThreadNode *getLastNode(ThreadNode *now);   // ��ȡ���������������ĩ��� 
	ThreadNode *getNextNode(ThreadNode *now);   // ��ȡ������������������������е���һ����� 
	ThreadNode *getPrevNode(ThreadNode *now);   // ��ȡ������������������������е���һ����� 
	vector<int> traversal();                    // ������������������� 
	~InThreadTree();                            // ������������������ 
	
	private:
	ThreadNode *treeroot;
};

InThreadTree::InThreadTree(vector<int> &preorder, vector<int> &inorder)
{
	// lambda func: ���ݱ������й��������� 
	function<ThreadNode*(vector<int> &, vector<int> &)> func = [&](vector<int> &preorder, vector<int> &inorder) {  
		if(!preorder.size()||!inorder.size())
		return static_cast<ThreadNode *>(NULL);
		// note: �����ԭ������������Ҫʹ���������ֽ��еݹ飬�Ͳ���ʹ��auto�ؼ��� 
		// 1. ʹ��ǰ������ĵ�һ��Ԫ�ع�������
		int rootval=preorder[0];
		ThreadNode *root=new ThreadNode(rootval);
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
	
	// lambda link: ����������������
	// ʹ��һ������������ܹ��������������� 
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
				if(sta.size())     // �״�㣬ע��ջ�п� 
				now->right=sta.top();
				else
				now->right=NULL;
			} 	
			nowprev=now;
		} 
	};
	
	treeroot=func(preorder, inorder);   // ��������� 
	link();                             // ������������ 
}

InThreadTree::InThreadTree(vector<int> &postorder, vector<int> &inorder, int num)
{
	function<ThreadNode*(vector<int> &, vector<int> &)> func = [&](vector<int> &postorder, vector<int> &inorder) {   // lambda����������ע����&����ȫ�������ı���������
		if(!postorder.size()||!inorder.size())
		return (ThreadNode*)NULL;
		// note: �����ԭ������������Ҫʹ���������ֽ��еݹ飬�Ͳ���ʹ��auto�ؼ��� 
		// 1. ʹ�ú�����������һ��Ԫ�ع�������
		int rootval=postorder[postorder.size()-1];
		ThreadNode *root=new ThreadNode(rootval);
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
	
	// lambda link: ����������������
	// ʹ��һ������������ܹ��������������� 
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
	
	treeroot=func(postorder, inorder);   // ��������� 
	link();                             // ������������ 
}

ThreadNode *InThreadTree::getFirstNode(ThreadNode *now)
{
	// �����������Ľ���������������׽��
	while(!now->lflag)
	{
		now=now->left;	
	} 
	return now;
}

ThreadNode *InThreadTree::getLastNode(ThreadNode *now)
{
	// ���������Ҳ�Ľ��������������ĩ��� 
	while(!now->rflag)
	{
		now=now->right;
	}
	return now;
}

ThreadNode *InThreadTree::getNextNode(ThreadNode *now)
{
	// 1. ��Ϊ��ǰ����Ѿ����ʣ���������������壬��˺�̽����ǵ�ǰ����������������������һ����� 
	if(!now->rflag)
	return getFirstNode(now->right);
	// 2. ����������������������������������壬now->right��ָ����������е���һ����� 
	else
	return now->right;
}

ThreadNode *InThreadTree::getPrevNode(ThreadNode *now)   
{
	// 1. ��Ϊ��ǰ����Ѿ������ʣ���������������壬���ǰ�������ǵ�ǰ������������������������һ����� 
	if(!now->lflag) 
	return getLastNode(now->left);
	// 2. ����������������������������������壬now->left��ָ����������е���һ����� 
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
