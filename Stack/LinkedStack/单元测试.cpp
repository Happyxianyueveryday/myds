#include "LinkedStack.h"
#include <iostream>

using namespace std; 

int main(void)        
{
	LinkedStack<int> sta1_item=LinkedStack<int>();
	LinkedStack<int> sta2_item=LinkedStack<int>();
	
	LinkedStack<int> &sta1=sta1_item;
	LinkedStack<int> &sta2=sta2_item;
	
	sta2.push(1);
	sta2.push(2);
	sta2.push(3);
	sta2.push(4);
	sta2.push(5);
	sta2.push(6);
	
	int val;
	cout<<sta2.top(val)<<endl;
	cout<<val<<endl;
	cout<<sta2.length()<<endl;
	cout<<"----------------"<<endl;
	
	cout<<sta2.top(val)<<endl;
	cout<<val<<endl;
	cout<<"----------------"<<endl; 
	
	LinkedStack<int> sta3(sta1);
	sta3=sta2;
	
	while(sta3.length())
	{
		sta3.pop(val);
		cout<<val<<endl;
	}
	cout<<"----------------"<<endl;
	
	LinkedStack<int> sta4(move(sta2));
	cout<<sta4.length()<<endl;
	cout<<sta2.length()<<endl;
	
	LinkedStack<int> sta5;
	sta5=move(sta4);
	cout<<sta5.length()<<endl;
	cout<<sta4.length()<<endl; 
}
