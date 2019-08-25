#include "Search.h"
#include <iostream>
#include <string>

using namespace std;

int main(void)
{
	int data[]={1,3,5,7,9,11,13,15,17,19};
	for(int i=0;i<10;i++)
	{
		cout<<Search::binary_search(data, 10, data[i])<<" ";	
	}
	cout<<endl;
	for(int i=0;i<10;i++) 
	{
		cout<<Search::linear_search(data, 10, data[i])<<" ";	 
	}
	cout<<endl;
	
	int data1[]={2,4,6,8,10,12,14};
	for(int i=0;i<7;i++)
	{
		cout<<Search::binary_search(data1, 7, data1[i])<<" "; 	
	}
	cout<<endl;
	for(int i=0;i<7;i++)
	{
		cout<<Search::linear_search(data1, 7, data1[i])<<" ";	
	}
	cout<<endl;
}
