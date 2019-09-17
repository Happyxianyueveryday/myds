#include <iostream>    
#include "ArrayHashSet.h"  
#include "Hashable.h" 

using namespace std;

int main(void)
{
	int data[] = {19,14,23,1,68,20,84,27,55,11,10,79};
	int data_size=12;

	// 1. ��������̽�鷨
	ArrayHashSet<Hashable> set1("linear");  
	for(int i=0;i<data_size;i++)
	{
		Hashable temp(data[i]);
 	    set1.insert(temp);
	}
	cout<<set1.toString()<<endl;
	
	// 2. ����ƽ��̽�鷨 
	ArrayHashSet<Hashable> set2("square"); 
	for(int i=0;i<data_size;i++)
	{
		Hashable temp(data[i]);
 	    set2.insert(temp);
	}
	cout<<set2.toString()<<endl;
	
	// 3. �����ٹ�ϣ�� 
	ArrayHashSet<Hashable> set3("rehash"); 
	for(int i=0;i<data_size;i++)
	{
		Hashable temp(data[i]);
 	    set3.insert(temp);   
	}
	cout<<set3.toString()<<endl;
	
	// 4. ���Բ��ҷ���
	for(int i=0;i<data_size;i++) 
	{
		Hashable temp(data[i]);
		cout<<set3.contain(temp)<<endl;
	}
    Hashable tempadd(999);
	cout<<set3.contain(tempadd)<<endl;
	
	// 5. ����ɾ������ 
	for(int i=0;i<data_size;i++) 
	{
		Hashable temp(data[i]);
		set3.remove(temp);
	}
	cout<<set3.toString()<<endl;
	
	// 6. ���Կ���/�ƶ����� 
	ArrayHashSet<Hashable> set4=move(set3);    // �ƶ����캯�� 
	cout<<set4.toString()<<endl;     
	set4=move(set2);                 // �ƶ���ֵ����� 
	cout<<set4.toString()<<endl;
	ArrayHashSet<Hashable> set5(set4);         // �������캯�� 
	cout<<set5.toString()<<endl;  
	set5=set3;                       // ������ֵ�����  
	cout<<set5.toString()<<endl;    
	
	// 7. ���Լ��㳤�ȷ���
	ArrayHashSet<Hashable> set6=set4; 
	cout<<set6.length()<<endl;
	
	// 8. ������Բ��� 
	ArrayHashSet<Hashable> set7("linear"); 
	ArrayHashSet<Hashable> set8("rehash");
	for(int i=0;i<150;i++) 
	{
		Hashable temp(rand());
		set7.insert(temp);
		set8.insert(temp);
	}
	cout<<set7.toString()<<endl;
	cout<<set7.length()<<endl; 
	cout<<set8.toString()<<endl;
	cout<<set8.length()<<endl;  
}
