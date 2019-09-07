#include "Sort.h"      
#include <iostream>
#include <string>

using namespace std;

int main(void)
{
	// 1. √∞≈›≈≈–Ú 
	int data1[]={9,6,3,2,8,5,7,4,1}; 
	Sort<int>::bubble_sort(data1, 9);
	
	for(int i=0;i<9;i++)
	{
		cout<<data1[i]<<" ";
	}
	cout<<endl;
	
	// 2. ≤Â»Î≈≈–Ú 
	int data2[]={9,6,7,2,8,5,3,4,1}; 
	Sort<int>::insert_sort(data2, 9);
	
	for(int i=0;i<9;i++)
	{
		cout<<data2[i]<<" ";
	}
	cout<<endl;
	
	// 3. Ωªªª≈≈–Ú 
	int data3[]={9,6,3,2,8,4,7,5,1}; 
	Sort<int>::select_sort(data3, 9);
	
	for(int i=0;i<9;i++)  
	{
		cout<<data3[i]<<" ";
	}
	cout<<endl;
	
	// 4. πÈ≤¢≈≈–Ú 
	int data4[]={9,6,3,2,8,4,7,5,1}; 
	Sort<int>::merge_sort(data4, 9);
	
	for(int i=0;i<9;i++) 
	{
		cout<<data4[i]<<" ";
	}
	cout<<endl;
	
	// 5. øÏÀŸ≈≈–Ú 
	int data5[]={9,6,3,2,1,4,7,5,8};  
	Sort<int>::quick_sort(data5, 9);
	
	for(int i=0;i<9;i++)
	{
		cout<<data5[i]<<" ";
	}
	cout<<endl;
	
	// 6. ∂—≈≈–Ú
	int data6[]={9,6,3,2,1,4,7,5,8};  
	Sort<int>::heap_sort(data6, 9);
	
	for(int i=0;i<9;i++)
	{
		cout<<data6[i]<<" ";
	}
	cout<<endl;
	
	// 7. œ£∂˚≈≈–Ú
	int data7[]={9,6,3,2,1,4,5,7,8};   
	Sort<int>::shell_sort(data7, 9); 
	
	for(int i=0;i<9;i++)
	{
		cout<<data7[i]<<" ";
	}
	cout<<endl;
}
