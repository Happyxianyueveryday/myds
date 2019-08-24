#include "LinkedList.h"

using namespace std;

int main(void)
{
	LinkedList lis0;
	cout<<lis0.toString()<<endl;
	
	int data1[]={1,2,3,4,5,6,7,8,9};
	LinkedList lis1(data1, 9);
	cout<<lis1.toString()<<endl;
	cout<<lis1.length()<<endl;
	
	vector<int> data2={1,2,3,4,5,6,7,8,9};
	LinkedList lis2(data2);
	cout<<lis2.toString()<<endl;
	cout<<lis2.length()<<endl;
	
	LinkedList lis3(lis1);
	cout<<lis3.toString()<<endl;
	cout<<lis3.length()<<endl;
	
	LinkedList lis4=LinkedList()=lis2;
	cout<<lis4.toString()<<endl;
	cout<<lis4.length()<<endl;
	
	int val=0;
	if(lis2.get(5, val))
	cout<<val<<endl;
	if(lis2.get(-1, val)) 
	cout<<val<<endl;
	if(lis2.get(0, val))
	cout<<val<<endl;
	if(lis2.get(9, val))
	cout<<val<<endl;
	if(lis2.get(8, val))
	cout<<val<<endl;
	
	lis2.insert(5, -1);
	lis2.insert(10, 10);
	lis2.insert(-1, -99);
	lis2.insert(100, 100);
	lis2.insert(0,-2);
	cout<<lis2.toString()<<endl;
	
	lis2.remove(0, val);
	lis2.remove(5, val);
	lis2.remove(11, val);
	lis2.remove(99, val);
	lis2.remove(-1, val);
	cout<<lis2.toString()<<endl;
	
	lis2.reverse();
	cout<<lis2.toString()<<endl;
	
	cout<<lis2.middle()<<endl;
}
