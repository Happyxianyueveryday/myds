#include "InThreadTree.h"
#include <iostream>
#include <string>
       
using namespace std;

int main(void)
{
	vector<int> preorder={12,5,2,9,18,15,17,16,19};
	vector<int> inorder={2,5,9,12,15,16,17,18,19};
	InThreadTree tree1(preorder,inorder);    // 由中序遍历和前序遍历的构造函数 
	cout<<"tree1 = "<<endl;
	vector<int> res1=tree1.traversal();
	for(int i=0;i<res1.size();i++)
	{
	    cout<<res1[i]<<" ";	
	} 
	cout<<endl;
}
