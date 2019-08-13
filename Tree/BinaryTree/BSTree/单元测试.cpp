#include <iostream>
#include <vector>
#include "BSTree.h"

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
	// 1. 测试构造函数	
	BSTree tree1;      // 默认构造函数 
	cout<<"tree1 = "<<endl;
	print("tree1 层次遍历 = ", tree1.levelorder());
	
	cout<<"--------------------------------------------"<<endl;
	
	vector<int> preorder={12,5,2,9,18,15,17,16,19};
	vector<int> inorder={2,5,9,12,15,16,17,18,19};
	BSTree tree2(preorder, inorder);    // 由中序遍历和前序遍历的构造函数 
	cout<<"tree2 = "<<endl;
	print("tree2 前序遍历 = ", tree2.preorder());
	print("tree2 中序遍历 = ", tree2.inorder());  
	print("tree2 后序遍历 = ", tree2.postorder());
	print("tree2 层次遍历 = ", tree2.levelorder()); 
	
	cout<<"--------------------------------------------"<<endl;
	
	vector<int> postorder={2,9,5,16,17,15,19,18,12};
	BSTree tree3(postorder,inorder,1); // 由中序遍历和后序遍历的构造函数 
	cout<<"tree3 = "<<endl;
	print("tree3 前序遍历 = ", tree3.preorder());
	print("tree3 中序遍历 = ", tree3.inorder());  
	print("tree3 后序遍历 = ", tree3.postorder());
	print("tree3 层次遍历 = ", tree3.levelorder()); 
	
	cout<<"--------------------------------------------"<<endl;
	
	// 2. 测试拷贝构造函数和拷贝构造运算符 
	cout<<"tree4 = Tree(tree3)"<<endl;
	BSTree tree4(tree3);   // 拷贝构造函数 
	print("tree4 前序遍历 = ", tree4.preorder());
	print("tree4 中序遍历 = ", tree4.inorder());  
	print("tree4 后序遍历 = ", tree4.postorder());
	print("tree4 层次遍历 = ", tree4.levelorder()); 
	
	cout<<"--------------------------------------------"<<endl;
	
	cout<<"tree5 = tree2 = tree2"<<endl;
	vector<int> inorder2={1};
	vector<int> preorder2={1};
	BSTree tree5(preorder2, inorder2);
	tree5=tree2=tree2;
	print("tree5 前序遍历 = ", tree5.preorder());
	print("tree5 后序遍历 = ", tree5.postorder());
	print("tree5 中序遍历 = ", tree5.inorder());  
	print("tree5 层次遍历 = ", tree5.levelorder()); 
	
	cout<<"--------------------------------------------"<<endl;
	
	// 3. 测试插入结点，删除结点，查找结点的地址功能 
	tree5.insert(30);
	tree5.insert(1);
	cout<<"向tree5中插入数值30和1"<<endl;
	print("tree5 前序遍历 = ", tree5.preorder());
	print("tree5 后序遍历 = ", tree5.postorder());
	print("tree5 中序遍历 = ", tree5.inorder());  
	print("tree5 层次遍历 = ", tree5.levelorder()); 
	
	cout<<"--------------------------------------------"<<endl;
	
	cout<<"从tree5中查找结点30的地址"<<endl;
	cout<<"地址: "<<tree5.get(30)<<" 对应的值为: "<<tree5.get(30)->val<<endl;
	cout<<"从tree5中查找结点16的地址"<<endl;
	cout<<"地址: "<<tree5.get(16)<<" 对应的值为: "<<tree5.get(16)->val<<endl;
	
	cout<<"--------------------------------------------"<<endl;
	
	vector<int> test=tree2.levelorder();   
	cout<<"依次删除tree2中的所有结点，直到树tree2为空为止: "<<endl;
	print("执行删除前，tree2 中序遍历 = ", tree2.inorder());
	for(int i=0;i<test.size();i++)
	{
		tree2.remove(test[i]);
		cout<<"删除结点"<<test[i]<<"后,";
		print("tree2 中序遍历 = ", tree2.inorder());
	}
	
	cout<<"--------------------------------------------"<<endl;
	
	tree5=tree3;
	cout<<"tree5的结构为: "<<endl;  
	print("tree5 前序遍历 = ", tree5.preorder());
	print("tree5 后序遍历 = ", tree5.postorder());
	print("tree5 中序遍历 = ", tree5.inorder());  
	print("tree5 层次遍历 = ", tree5.levelorder()); 
	
	int p=16,q=19;
	cout<<"结点16和19的最近公共祖先为: "<<tree5.lca(tree5.get(p),tree5.get(q))->val<<endl;
	
	p=12,q=16;
	cout<<"结点16和12的最近公共祖先为: "<<tree5.lca(tree5.get(p),tree5.get(q))->val<<endl;
	
	cout<<"--------------------------------------------"<<endl;
	
	cout<<"tree5的深度为 depth = "<<tree5.depth()<<endl; 
	
	cout<<"--------------------------------------------"<<endl;
	
	cout<<"tree5的结点个数 size = "<<tree5.size()<<endl;
	
	cout<<"--------------------------------------------"<<endl; 
	
	cout<<"tree5的从根结点到叶子结点的最大路径和 maxrlpath = "<<tree5.maxrlpath()<<endl;
	
	cout<<"--------------------------------------------"<<endl; 
	
	cout<<"tree5的最大路径和 maxpath = "<<tree5.maxpathsum()<<endl;
} 
