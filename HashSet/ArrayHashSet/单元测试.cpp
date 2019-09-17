#include <iostream>    
#include "ArrayHashSet.h"  
#include "Hashable.h" 

using namespace std;

int main(void)
{
	int data[] = {19,14,23,1,68,20,84,27,55,11,10,79};
	int data_size=12;

	// 1. 测试线性探查法
	ArrayHashSet<Hashable> set1("linear");  
	for(int i=0;i<data_size;i++)
	{
		Hashable temp(data[i]);
 	    set1.insert(temp);
	}
	cout<<set1.toString()<<endl;
	
	// 2. 测试平方探查法 
	ArrayHashSet<Hashable> set2("square"); 
	for(int i=0;i<data_size;i++)
	{
		Hashable temp(data[i]);
 	    set2.insert(temp);
	}
	cout<<set2.toString()<<endl;
	
	// 3. 测试再哈希法 
	ArrayHashSet<Hashable> set3("rehash"); 
	for(int i=0;i<data_size;i++)
	{
		Hashable temp(data[i]);
 	    set3.insert(temp);   
	}
	cout<<set3.toString()<<endl;
	
	// 4. 测试查找方法
	for(int i=0;i<data_size;i++) 
	{
		Hashable temp(data[i]);
		cout<<set3.contain(temp)<<endl;
	}
    Hashable tempadd(999);
	cout<<set3.contain(tempadd)<<endl;
	
	// 5. 测试删除方法 
	for(int i=0;i<data_size;i++) 
	{
		Hashable temp(data[i]);
		set3.remove(temp);
	}
	cout<<set3.toString()<<endl;
	
	// 6. 测试拷贝/移动机制 
	ArrayHashSet<Hashable> set4=move(set3);    // 移动构造函数 
	cout<<set4.toString()<<endl;     
	set4=move(set2);                 // 移动赋值运算符 
	cout<<set4.toString()<<endl;
	ArrayHashSet<Hashable> set5(set4);         // 拷贝构造函数 
	cout<<set5.toString()<<endl;  
	set5=set3;                       // 拷贝赋值运算符  
	cout<<set5.toString()<<endl;    
	
	// 7. 测试计算长度方法
	ArrayHashSet<Hashable> set6=set4; 
	cout<<set6.length()<<endl;
	
	// 8. 随机测试部分 
	ArrayHashSet<Hashable> set7("linear"); 
	ArrayHashSet<Hashable> set8("rehash");
	for(int i=0;i<150;i++) 
	{
		Hashable temp(rand());
		set7.insert(temp);
		set8.insert(temp);
	}
	cout<<set7.toString()<<endl;
	cout<<set7.length()<<endl; 
	cout<<set8.toString()<<endl;
	cout<<set8.length()<<endl;  
}
