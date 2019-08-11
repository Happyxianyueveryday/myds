#include "ArrayQueue.h"
#include <iostream>
#include <string>

using namespace std;

int main(void)
{
	ArrayQueue *quepoint=ArrayQueue::ArrayQueueFactory(3);
	ArrayQueue que=*quepoint;
	
	// 1. 测试入队功能
	if(que.push(1))
	cout<<"入队1成功"<<endl;
	else
	cout<<"入队1失败，队列已经满"<<endl;  
	
	if(que.push(2))
	cout<<"入队2成功"<<endl;
	else
	cout<<"入队2失败，队列已经满"<<endl;
	
	if(que.push(3))
	cout<<"入队3成功"<<endl;
	else
	cout<<"入队3失败，队列已经满"<<endl;
	
	if(que.push(4))
	cout<<"入队4成功"<<endl;
	else
	cout<<"入队4失败，队列已经满"<<endl;
	
	if(que.push(5))
	cout<<"入队5成功"<<endl;
	else
	cout<<"入队5失败，队列已经满"<<endl;
	
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
	
	if(que.push(1))
	cout<<"入队1成功"<<endl;
	else
	cout<<"入队1失败，队列已经满"<<endl;
	
	if(que.push(2))
	cout<<"入队2成功"<<endl;
	else
	cout<<"入队2失败，队列已经满"<<endl;
	
	if(que.push(3))
	cout<<"入队3成功"<<endl;
	else
	cout<<"入队3失败，队列已经满"<<endl;
	
	if(que.push(4))
	cout<<"入队4成功"<<endl;
	else
	cout<<"入队4失败，队列已经满"<<endl;
	
	if(que.push(5))
	cout<<"入队5成功"<<endl;
	else
	cout<<"入队5失败，队列已经满"<<endl;
	
	if(que.push(6))
	cout<<"入队6成功"<<endl;
	else
	cout<<"入队6失败，队列已经满"<<endl;
	
	while(que.length()>1)
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
	ArrayQueue que2(que);
	ArrayQueue que3=que2=que2;
	 
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
}

