#include "LinkedQueue.h"
#include <iostream>
#include <string> 

using namespace std; 

int main(void)
{
	LinkedQueue<int> que;   
	
	// 1. 测试入队功能
	que.push(1);
	que.push(2);
	que.push(3);
	
	cout<<"--------------------------------------------"<<endl;
	
	
	// 2. 测试获取队首元素功能
	int val; 
	if(que.frontval(val))
	{
		cout<<"队首元素为: val = "<<val<<endl;
	}
	else
	{
		cout<<"队列为空，无法获取队首元素"<<endl;
	}
	
	while(que.length())
	{
		que.pop(val);
		cout<<"出队队首元素 val = "<<val<<endl;
	}
	
	if(que.frontval(val))
	{
		cout<<"队首元素为: val = "<<val<<endl;
	}
	else
	{
		cout<<"队列为空，无法获取队首元素"<<endl;
	}
	
	cout<<"--------------------------------------------"<<endl;	
	
	
	// 3. 测试出队功能
	que.push(1);
	if(que.pop(val))
	cout<<"出队队首元素 val = "<<val<<endl;
	else
	cout<<"队列为空，出队失败"<<endl;
	 
	que.push(1);
	que.push(2);
	que.push(3);
	que.push(4);
	que.push(5);
	que.push(6);
	
	while(que.length()>3)
	{
		if(que.pop(val))
		cout<<"出队队首元素 val = "<<val<<endl;
		else
		cout<<"队列为空，出队失败"<<endl;
	}
	
	if(que.frontval(val))
	{
		cout<<"现在队首元素为: val = "<<val<<endl;
	}
	else
	{
		cout<<"队列为空，无法获取队首元素"<<endl;
	}
	
	cout<<"--------------------------------------------"<<endl;
	
	// 3. 测试拷贝构造函数，拷贝构造运算符和析构函数
	LinkedQueue<int> que2(que);
	LinkedQueue<int> que3=que2=que2;
	 
	while(que2.length())
	{
		if(que2.pop(val))
		cout<<"出队队首元素 val = "<<val<<endl;
		else
		cout<<"队列为空，出队失败"<<endl;
	}  
	
	while(que3.length())
	{
		if(que3.pop(val))
		cout<<"出队队首元素 val = "<<val<<endl;
		else
		cout<<"队列为空，出队失败"<<endl;
	}
	
	cout<<"--------------------------------------------"<<endl;
	
	LinkedQueue<int> que4(move(que));
	cout<<que4.length()<<endl;
	cout<<que.length()<<endl;
	LinkedQueue<int> que5(move(que));
	que5=move(que4);
	cout<<que5.length()<<endl;
	cout<<que4.length()<<endl; 
}
