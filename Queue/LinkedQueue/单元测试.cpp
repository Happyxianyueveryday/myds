#include "LinkedQueue.h"
#include <iostream>
#include <string> 

using namespace std; 

int main(void)
{
	LinkedQueue<int> que;   
	
	// 1. ������ӹ���
	que.push(1);
	que.push(2);
	que.push(3);
	
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
	 
	que.push(1);
	que.push(2);
	que.push(3);
	que.push(4);
	que.push(5);
	que.push(6);
	
	while(que.length()>3)
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
	LinkedQueue<int> que2(que);
	LinkedQueue<int> que3=que2=que2;
	 
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
	
	cout<<"--------------------------------------------"<<endl;
	
	LinkedQueue<int> que4(move(que));
	cout<<que4.length()<<endl;
	cout<<que.length()<<endl;
	LinkedQueue<int> que5(move(que));
	que5=move(que4);
	cout<<que5.length()<<endl;
	cout<<que4.length()<<endl; 
}
