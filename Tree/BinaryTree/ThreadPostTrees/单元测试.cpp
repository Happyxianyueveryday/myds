#include <iostream>
#include <vector>

#include "ThreadPostTrees.h"

using namespace std;

void print(string info, const vector<int> &lis)
{
	cout<<info;
	for(int i=0;i<lis.size();i++)
	{
		cout<<lis[i]<<" ";
	}
	cout<<endl;
}

int main(void)
{
	// 0. 初始化测试所用的树
	Tree tree1;      // 默认构造函数
	cout<<"tree1 = "<<endl;
	print("tree1 层次遍历 = ", tree1.levelorder());

	cout<<"--------------------------------------------"<<endl;

	int pre[]={12,5,2,9,18,15,17,16,19};
	int in[]={2,5,9,12,15,16,17,18,19};

	vector<int> preorder(pre, pre+9);
	vector<int> inorder(in, in+9);
	Tree tree2(inorder,preorder);    // 由中序遍历和前序遍历的构造函数
	cout<<"tree2 = "<<endl;
	print("tree2 前序遍历 = ", tree2.preorder());
	print("tree2 中序遍历 = ", tree2.inorder());
	print("tree2 后序遍历 = ", tree2.postorder());
	print("tree2 层次遍历 = ", tree2.levelorder());

	cout<<"--------------------------------------------"<<endl;
	ThreadPostTree threadtree1(tree1);
	ThreadPostTree threadtree2(tree2);

	print("线索树tree1 反向后序遍历 = ", threadtree1.reverse_postorder());
	print("线索树tree2 反向后序遍历 = ", threadtree2.reverse_postorder());
}
