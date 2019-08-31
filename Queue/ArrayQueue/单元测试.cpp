#include "ArrayQueue.h"
#include <iostream> 
#include <string>

using namespace std; 

int main(void)
{
	Queue *que=ArrayQueue::ArrayQueueFactory(3);
	
	// 1. ������ӹ���
	if(que->push(1))
	cout<<"���1�ɹ�"<<endl;
	else
	cout<<"���1ʧ�ܣ������Ѿ���"<<endl;  
	
	if(que->push(2))
	cout<<"���2�ɹ�"<<endl;
	else
	cout<<"���2ʧ�ܣ������Ѿ���"<<endl;
	
	if(que->push(3))
	cout<<"���3�ɹ�"<<endl;
	else
	cout<<"���3ʧ�ܣ������Ѿ���"<<endl;
	
	if(que->push(4))
	cout<<"���4�ɹ�"<<endl;
	else
	cout<<"���4ʧ�ܣ������Ѿ���"<<endl;
	
	if(que->push(5))
	cout<<"���5�ɹ�"<<endl;
	else
	cout<<"���5ʧ�ܣ������Ѿ���"<<endl;
	
	cout<<"--------------------------------------------"<<endl;
	
	// 2. ���Ի�ȡ����Ԫ�ع���
	int val; 
	if(que->frontval(val))
	{
		cout<<"����Ԫ��Ϊ: val = "<<val<<endl;
	}
	else
	{
		cout<<"����Ϊ�գ��޷���ȡ����Ԫ��"<<endl;
	}
	
	while(que->length())
	{
		que->pop(val);
		cout<<"���Ӷ���Ԫ�� val = "<<val<<endl;
	}
	
	if(que->frontval(val))
	{
		cout<<"����Ԫ��Ϊ: val = "<<val<<endl;
	}
	
	else
	{
		cout<<"����Ϊ�գ��޷���ȡ����Ԫ��"<<endl;
	}
	
	cout<<"--------------------------------------------"<<endl;	
	
	
	// 3. ���Գ��ӹ���
	que->push(1);
	if(que->pop(val))
	cout<<"���Ӷ���Ԫ�� val = "<<val<<endl;
	else
	cout<<"����Ϊ�գ�����ʧ��"<<endl;
	
	if(que->push(1))
	cout<<"���1�ɹ�"<<endl;
	else
	cout<<"���1ʧ�ܣ������Ѿ���"<<endl;
	
	if(que->push(2))
	cout<<"���2�ɹ�"<<endl;
	else
	cout<<"���2ʧ�ܣ������Ѿ���"<<endl;
	
	if(que->push(3))
	cout<<"���3�ɹ�"<<endl;
	else
	cout<<"���3ʧ�ܣ������Ѿ���"<<endl;
	
	if(que->push(4))
	cout<<"���4�ɹ�"<<endl;
	else
	cout<<"���4ʧ�ܣ������Ѿ���"<<endl;
	
	if(que->push(5))
	cout<<"���5�ɹ�"<<endl;
	else
	cout<<"���5ʧ�ܣ������Ѿ���"<<endl;
	
	if(que->push(6))
	cout<<"���6�ɹ�"<<endl;
	else
	cout<<"���6ʧ�ܣ������Ѿ���"<<endl;
	
	while(que->length()>1)
	{
		if(que->pop(val))
		cout<<"���Ӷ���Ԫ�� val = "<<val<<endl;
		else
		cout<<"����Ϊ�գ�����ʧ��"<<endl;
	} 
	
	if(que->frontval(val))
	{
		cout<<"���ڶ���Ԫ��Ϊ: val = "<<val<<endl;
	}
	else
	{
		cout<<"����Ϊ�գ��޷���ȡ����Ԫ��"<<endl;
	}
	
	cout<<"--------------------------------------------"<<endl;
	
	ArrayQueue que2(move(*dynamic_cast<ArrayQueue *> (que)));
	cout<<que2.length()<<endl;
	cout<<que->length()<<endl;
	ArrayQueue que3(move(*dynamic_cast<ArrayQueue *> (que)));
	que3=move(que2);
	cout<<que3.length()<<endl;
	cout<<que2.length()<<endl;
}

