#include "Sort.h"
#include <iostream>
#include <string>

using namespace std;

int main(void)
{
	int data[]={9,6,3,2,8,5,7,4,1}; 
	Sort::bubble_sort(data, 9);
	
	for(int i=0;i<9;i++)
	{
		cout<<data[i]<<" ";
	}
	cout<<endl;
}
