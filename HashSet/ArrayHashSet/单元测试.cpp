#include <iostream>
#include "ArrayHashSet.h" 
#include "TestElement.h"

using namespace std;

int main(void)
{
	int data[] = {19,14,23,1,68,20,84,27,55,11,10,79};
	int data_size=12;

	// 1. 测试线性探查法
	ArrayHashSet set1("linear");
	for(int i=0;i<data_size;i++)
	{
		const HashElement *temp=new TestElement(data[i]);
 	    set1.insert(temp);
 	    delete temp;
	}
	cout<<set1.toString()<<endl;
	
	// 2. 测试平方探查法 
	ArrayHashSet set2("square"); 
	for(int i=0;i<data_size;i++)
	{
		const HashElement *temp=new TestElement(data[i]);
 	    set2.insert(temp);
 	    delete temp;
	}
	cout<<set2.toString()<<endl;
	
	// 3. 测试再哈希法 
	ArrayHashSet set3("rehash"); 
	for(int i=0;i<data_size;i++)
	{
		const HashElement *temp=new TestElement(data[i]);
 	    set3.insert(temp);   
 	    delete temp;
	}
	cout<<set3.toString()<<endl;
	
	// 4. 测试查找方法
	for(int i=0;i<data_size;i++) 
	{
		const HashElement *temp=new TestElement(data[i]);
		cout<<set3.contain(temp)<<endl;
		delete temp;
	}
	const HashElement *tempadd=new TestElement(999);
	cout<<set3.contain(tempadd)<<endl;
	
	// 5. 测试删除方法 
	for(int i=0;i<data_size;i++) 
	{
		const HashElement *temp=new TestElement(data[i]);
		set3.remove(temp);
		delete temp;
	}
	cout<<set3.toString()<<endl;
	
	// 6. 测试拷贝/移动机制 
	ArrayHashSet set4=move(set3);    // 移动构造函数 
	cout<<set4.toString()<<endl;     
	set4=move(set2);                 // 移动赋值运算符 
	cout<<set4.toString()<<endl;
	ArrayHashSet set5(set4);         // 拷贝构造函数 
	cout<<set5.toString()<<endl;  
	set5=set3;                       // 拷贝赋值运算符  
	cout<<set5.toString()<<endl;    
	
	// 7. 测试计算长度方法
	ArrayHashSet set6=set4; 
	cout<<set6.length()<<endl;
	
	// 8. 随机测试部分 
	ArrayHashSet set7("linear"); 
	ArrayHashSet set8("rehash");
	for(int i=0;i<150;i++) 
	{
		const HashElement *temp=new TestElement(rand());
		set7.insert(temp);
		set8.insert(temp);
		delete temp;
	}
	cout<<set7.toString()<<endl;
	cout<<set7.length()<<endl; 
	cout<<set8.toString()<<endl;
	cout<<set8.length()<<endl;  
}
