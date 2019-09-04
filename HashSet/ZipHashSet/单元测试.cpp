#include "ZipHashSet.h"
#include "TestElement.h"
#include <iostream>
#include <cstdlib>
using namespace std;
 
int main(void)
{
	ZipHashSet hashset;
	vector<HashElement *> dev;
	for(int i=0;i<5;i++)
	{
		HashElement *temp=new TestElement(rand());
		hashset.insert(temp);   // һ������������ϣ����ö�����ͷ����ɹ�ϣ����� 
		dev.push_back(temp);
	} 
	cout<<hashset.length()<<endl;
	cout<<"hashset = "<<endl;
	cout<<hashset.toString()<<endl;
	
	cout<<"--------------------------------------------"<<endl;
	
	for(int i=0;i<5;i++)
	{
		cout<<hashset.contain(dev[i])<<endl;
	}
	cout<<hashset.contain(new TestElement(2));
	
	cout<<"--------------------------------------------"<<endl;
	
	vector<const HashElement *> res=hashset.values();
	for(int i=0;i<res.size();i++)
	{
		cout<<res[i]->toString()<<" ";
	}
	cout<<endl;
	
	cout<<"--------------------------------------------"<<endl;
	
	HashSet *hashset2=new ZipHashSet(dev);
	cout<<"hashset2 = "<<endl;
	cout<<hashset2->toString()<<endl;
	
	cout<<"--------------------------------------------"<<endl;
	
	ZipHashSet hashset3;
	hashset3=hashset;
	cout<<"hashset3 = "<<endl;
	cout<<hashset3.toString()<<endl;
	
	cout<<"--------------------------------------------"<<endl;
	
	cout<<(hashset==hashset3)<<endl;
	ZipHashSet hashset4=hashset3;
	hashset4.remove(dev[0]);
	cout<<(hashset4==hashset3)<<endl;
	
	cout<<"--------------------------------------------"<<endl;
	
	for(int i=0;i<5;i++)
	{
		hashset.remove(dev[i]);
	}
	hashset.remove(new TestElement(2));
	cout<<hashset.length()<<endl;
	cout<<"hashset = "<<endl;
	cout<<hashset.toString()<<endl;
	
	cout<<"--------------------------------------------"<<endl;
	cout<<"���������ݲ���"<<endl;
	
	vector<HashElement *> data; 
	for(int i=0;i<10;i++)    // 11��Ԫ�أ�δ������ϣ���ݲ��� 
	{
		data.push_back(new TestElement(rand())); 
	}
	
	ZipHashSet hashset5(data);
	
	cout<<hashset5.length()<<endl;
	cout<<"hashset5 = "<<endl;
	cout<<hashset5.toString()<<endl;
	
	for(int i=0;i<5;i++)    // ���������5��������������ϣ���ݲ��� 
	{
		hashset5.insert(new TestElement(rand()));
	}
	
	cout<<hashset5.length()<<endl;
	cout<<"hashset5 = "<<endl; 
	cout<<hashset5.toString()<<endl;
	
	for(int i=0;i<100;i++)   // ��Χ������� 
	{
		hashset5.insert(new TestElement(rand()));
	}
	cout<<hashset5.length()<<endl;
	cout<<"hashset5 = "<<endl; 
	cout<<hashset5.toString()<<endl; 
	
	cout<<"--------------------------------------------"<<endl;
	ZipHashSet hashset6(move(hashset5));
	cout<<hashset6.length()<<endl;
	ZipHashSet hashset7=ZipHashSet()=move(hashset6);
	cout<<hashset7.length()<<endl;
	cout<<hashset6.length()<<endl;
	
	for(int i=0;i<dev.size();i++)
	{
		delete dev[i];
		dev[i]=nullptr;
	}
	
	for(int i=0;i<data.size();i++)
	{
		delete data[i];
		data[i]=nullptr;
	}
}
