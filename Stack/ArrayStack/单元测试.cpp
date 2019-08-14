#include "ArrayStack.h"
#include <iostream>

using namespace std;

int main(void)
{
	ArrayStack *sta1=ArrayStack::arrayStackFactory(-1);
	cout<<sta1<<endl;
	
	ArrayStack *sta2=ArrayStack::arrayStackFactory(5);
	cout<<sta2<<endl;
	
	sta2->push(1);
	sta2->push(2);
	sta2->push(3);
	sta2->push(4);
	sta2->push(5);
	
	cout<<sta2->push(6)<<endl;
	cout<<"----------------"<<endl;
	
	int val;
	cout<<sta2->top(val)<<endl;
	cout<<val<<endl;
	cout<<sta2->length()<<endl;
	cout<<"----------------"<<endl;
	
	cout<<sta2->pop(val)<<endl;
	cout<<sta2->top(val)<<endl;
	cout<<val<<endl;
	cout<<"----------------"<<endl;
	
	ArrayStack sta3(10);
	sta3=*sta2;
	
	while(sta3.length())
	{
		sta3.pop(val);
		cout<<val<<endl;
	}
	cout<<"----------------"<<endl;
	
}
