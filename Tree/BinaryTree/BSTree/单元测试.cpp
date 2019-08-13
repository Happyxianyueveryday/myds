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
	// 1. ���Թ��캯��	
	BSTree tree1;      // Ĭ�Ϲ��캯�� 
	cout<<"tree1 = "<<endl;
	print("tree1 ��α��� = ", tree1.levelorder());
	
	cout<<"--------------------------------------------"<<endl;
	
	vector<int> preorder={12,5,2,9,18,15,17,16,19};
	vector<int> inorder={2,5,9,12,15,16,17,18,19};
	BSTree tree2(preorder, inorder);    // �����������ǰ������Ĺ��캯�� 
	cout<<"tree2 = "<<endl;
	print("tree2 ǰ����� = ", tree2.preorder());
	print("tree2 ������� = ", tree2.inorder());  
	print("tree2 ������� = ", tree2.postorder());
	print("tree2 ��α��� = ", tree2.levelorder()); 
	
	cout<<"--------------------------------------------"<<endl;
	
	vector<int> postorder={2,9,5,16,17,15,19,18,12};
	BSTree tree3(postorder,inorder,1); // ����������ͺ�������Ĺ��캯�� 
	cout<<"tree3 = "<<endl;
	print("tree3 ǰ����� = ", tree3.preorder());
	print("tree3 ������� = ", tree3.inorder());  
	print("tree3 ������� = ", tree3.postorder());
	print("tree3 ��α��� = ", tree3.levelorder()); 
	
	cout<<"--------------------------------------------"<<endl;
	
	// 2. ���Կ������캯���Ϳ������������ 
	cout<<"tree4 = Tree(tree3)"<<endl;
	BSTree tree4(tree3);   // �������캯�� 
	print("tree4 ǰ����� = ", tree4.preorder());
	print("tree4 ������� = ", tree4.inorder());  
	print("tree4 ������� = ", tree4.postorder());
	print("tree4 ��α��� = ", tree4.levelorder()); 
	
	cout<<"--------------------------------------------"<<endl;
	
	cout<<"tree5 = tree2 = tree2"<<endl;
	vector<int> inorder2={1};
	vector<int> preorder2={1};
	BSTree tree5(preorder2, inorder2);
	tree5=tree2=tree2;
	print("tree5 ǰ����� = ", tree5.preorder());
	print("tree5 ������� = ", tree5.postorder());
	print("tree5 ������� = ", tree5.inorder());  
	print("tree5 ��α��� = ", tree5.levelorder()); 
	
	cout<<"--------------------------------------------"<<endl;
	
	// 3. ���Բ����㣬ɾ����㣬���ҽ��ĵ�ַ���� 
	tree5.insert(30);
	tree5.insert(1);
	cout<<"��tree5�в�����ֵ30��1"<<endl;
	print("tree5 ǰ����� = ", tree5.preorder());
	print("tree5 ������� = ", tree5.postorder());
	print("tree5 ������� = ", tree5.inorder());  
	print("tree5 ��α��� = ", tree5.levelorder()); 
	
	cout<<"--------------------------------------------"<<endl;
	
	cout<<"��tree5�в��ҽ��30�ĵ�ַ"<<endl;
	cout<<"��ַ: "<<tree5.get(30)<<" ��Ӧ��ֵΪ: "<<tree5.get(30)->val<<endl;
	cout<<"��tree5�в��ҽ��16�ĵ�ַ"<<endl;
	cout<<"��ַ: "<<tree5.get(16)<<" ��Ӧ��ֵΪ: "<<tree5.get(16)->val<<endl;
	
	cout<<"--------------------------------------------"<<endl;
	
	vector<int> test=tree2.levelorder();   
	cout<<"����ɾ��tree2�е����н�㣬ֱ����tree2Ϊ��Ϊֹ: "<<endl;
	print("ִ��ɾ��ǰ��tree2 ������� = ", tree2.inorder());
	for(int i=0;i<test.size();i++)
	{
		tree2.remove(test[i]);
		cout<<"ɾ�����"<<test[i]<<"��,";
		print("tree2 ������� = ", tree2.inorder());
	}
	
	cout<<"--------------------------------------------"<<endl;
	
	tree5=tree3;
	cout<<"tree5�ĽṹΪ: "<<endl;  
	print("tree5 ǰ����� = ", tree5.preorder());
	print("tree5 ������� = ", tree5.postorder());
	print("tree5 ������� = ", tree5.inorder());  
	print("tree5 ��α��� = ", tree5.levelorder()); 
	
	int p=16,q=19;
	cout<<"���16��19�������������Ϊ: "<<tree5.lca(tree5.get(p),tree5.get(q))->val<<endl;
	
	p=12,q=16;
	cout<<"���16��12�������������Ϊ: "<<tree5.lca(tree5.get(p),tree5.get(q))->val<<endl;
	
	cout<<"--------------------------------------------"<<endl;
	
	cout<<"tree5�����Ϊ depth = "<<tree5.depth()<<endl; 
	
	cout<<"--------------------------------------------"<<endl;
	
	cout<<"tree5�Ľ����� size = "<<tree5.size()<<endl;
	
	cout<<"--------------------------------------------"<<endl; 
	
	cout<<"tree5�ĴӸ���㵽Ҷ�ӽ������·���� maxrlpath = "<<tree5.maxrlpath()<<endl;
	
	cout<<"--------------------------------------------"<<endl; 
	
	cout<<"tree5�����·���� maxpath = "<<tree5.maxpathsum()<<endl;
} 
