#include "ArrayQueue.h"
#include <iostream>
#include <string>

using namespace std;

int main(void)
{
	ArrayQueue *quepoint=ArrayQueue::ArrayQueueFactory(3);
	ArrayQueue que=*quepoint;
	
	// 1. ������ӹ���
	if(que.push(1))
	cout<<"���1�ɹ�"<<endl;
	else
	cout<<"���1ʧ�ܣ������Ѿ���"<<endl;  
	
	if(que.push(2))
	cout<<"���2�ɹ�"<<endl;
	else
	cout<<"���2ʧ�ܣ������Ѿ���"<<endl;
	
	if(que.push(3))
	cout<<"���3�ɹ�"<<endl;
	else
	cout<<"���3ʧ�ܣ������Ѿ���"<<endl;
	
	if(que.push(4))
	cout<<"���4�ɹ�"<<endl;
	else
	cout<<"���4ʧ�ܣ������Ѿ���"<<endl;
	
	if(que.push(5))
	cout<<"���5�ɹ�"<<endl;
	else
	cout<<"���5ʧ�ܣ������Ѿ���"<<endl;
	
	cout<<"--------------------------------------------"<<endl;
	
	// 2. ���Ի�ȡ����Ԫ�ع���
	int val; 
	if(que.frontval(val))
	{
		cout<<"����Ԫ��Ϊ: val = "<<val<<endl;
	}
	else
	{
		cout<<"����Ϊ�գ��޷���ȡ����Ԫ��"<<endl;
	}
	
	while(que.length())
	{
		que.pop(val);
		cout<<"���Ӷ���Ԫ�� val = "<<val<<endl;
	}
	
	if(que.frontval(val))
	{
		cout<<"����Ԫ��Ϊ: val = "<<val<<endl;
	}
	
	else
	{
		cout<<"����Ϊ�գ��޷���ȡ����Ԫ��"<<endl;
	}
	
	cout<<"--------------------------------------------"<<endl;	
	
	
	// 3. ���Գ��ӹ���
	que.push(1);
	if(que.pop(val))
	cout<<"���Ӷ���Ԫ�� val = "<<val<<endl;
	else
	cout<<"����Ϊ�գ�����ʧ��"<<endl;
	
	if(que.push(1))
	cout<<"���1�ɹ�"<<endl;
	else
	cout<<"���1ʧ�ܣ������Ѿ���"<<endl;
	
	if(que.push(2))
	cout<<"���2�ɹ�"<<endl;
	else
	cout<<"���2ʧ�ܣ������Ѿ���"<<endl;
	
	if(que.push(3))
	cout<<"���3�ɹ�"<<endl;
	else
	cout<<"���3ʧ�ܣ������Ѿ���"<<endl;
	
	if(que.push(4))
	cout<<"���4�ɹ�"<<endl;
	else
	cout<<"���4ʧ�ܣ������Ѿ���"<<endl;
	
	if(que.push(5))
	cout<<"���5�ɹ�"<<endl;
	else
	cout<<"���5ʧ�ܣ������Ѿ���"<<endl;
	
	if(que.push(6))
	cout<<"���6�ɹ�"<<endl;
	else
	cout<<"���6ʧ�ܣ������Ѿ���"<<endl;
	
	while(que.length()>1)
	{
		if(que.pop(val))
		cout<<"���Ӷ���Ԫ�� val = "<<val<<endl;
		else
		cout<<"����Ϊ�գ�����ʧ��"<<endl;
	}
	
	if(que.frontval(val))
	{
		cout<<"���ڶ���Ԫ��Ϊ: val = "<<val<<endl;
	}
	else
	{
		cout<<"����Ϊ�գ��޷���ȡ����Ԫ��"<<endl;
	}
	
	cout<<"--------------------------------------------"<<endl;
	
	// 3. ���Կ������캯���������������������������
	ArrayQueue que2(que);
	ArrayQueue que3=que2=que2;
	 
	while(que2.length()) 
	{
		if(que2.pop(val))
		cout<<"���Ӷ���Ԫ�� val = "<<val<<endl;
		else
		cout<<"����Ϊ�գ�����ʧ��"<<endl;
	}
	
	while(que3.length())
	{
		if(que3.pop(val))
		cout<<"���Ӷ���Ԫ�� val = "<<val<<endl;
		else
		cout<<"����Ϊ�գ�����ʧ��"<<endl;
	}
}

