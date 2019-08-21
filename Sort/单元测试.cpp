#include "Sort.h"
#include <iostream>
#include <string>

using namespace std;

int main(void)
{
	// 1. √∞≈›≈≈–Ú 
	int data1[]={9,6,3,2,8,5,7,4,1}; 
	Sort::bubble_sort(data1, 9);
	
	for(int i=0;i<9;i++)
	{
		cout<<data1[i]<<" ";
	}
	cout<<endl;
	
	// 2. ≤Â»Î≈≈–Ú 
	int data2[]={9,6,7,2,8,5,3,4,1}; 
	Sort::insert_sort(data2, 9);
	
	for(int i=0;i<9;i++)
	{
		cout<<data2[i]<<" ";
	}
	cout<<endl;
	
	// 3. Ωªªª≈≈–Ú 
	int data3[]={9,6,3,2,8,4,7,5,1}; 
	Sort::swap_sort(data3, 9);
	
	for(int i=0;i<9;i++)  
	{
		cout<<data3[i]<<" ";
	}
	cout<<endl;
	
	// 4. πÈ≤¢≈≈–Ú 
	int data4[]={9,6,3,2,8,4,7,5,1}; 
	Sort::merge_sort(data4, 9);
	
	for(int i=0;i<9;i++)
	{
		cout<<data4[i]<<" ";
	}
	cout<<endl;
}
