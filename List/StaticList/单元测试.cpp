#include "StaticList.h"
#include <iostream>
#include <string>      

using namespace std;
      
int main(void)
{
	StaticList<int> list1(6);
	list1.insert(0, 1); 
	list1.insert(0, 2);
	list1.insert(0, 4);
	list1.insert(0, 5);
	list1.insert(3, 3);
	list1.insert(4, 6);
	list1.insert(4, 6);
	cout<<list1.toString()<<endl; 
	cout<<list1.full()<<endl;
	int val;
	list1.remove(4, val);
	cout<<val<<endl;
	cout<<list1.toString()<<endl;
	list1.reverse();
	cout<<list1.toString()<<endl;
	list1.insert(2,12);
	cout<<list1.toString()<<endl;
	cout<<list1.middle()<<endl;
	
	StaticList<int> list2(move(list1));
	cout<<list2.toString()<<endl;
	cout<<list1.toString()<<endl;
	
	StaticList<int> list3=list1=move(list2);
	cout<<list3.toString()<<endl;
	cout<<list2.toString()<<endl;
	
}

