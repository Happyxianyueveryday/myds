#include "ZipHashMap.h"         
#include "Hashable.h"     
#include <iostream>
#include <cstdlib>
using namespace std;
 
int main(void)
{
	ZipHashMap<Hashable, Hashable> hashset;
	vector<Hashable> dev;
	
	for(int i=0;i<5;i++)
	{
		Hashable temp(rand());
		hashset.insert(temp, temp);
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
	cout<<hashset.contain(Hashable(2))<<endl;
	
	cout<<"--------------------------------------------"<<endl;
	
	vector<Hashable> res=hashset.keys();
	for(int i=0;i<res.size();i++)
	{
		cout<<res[i].toString()<<" ";
	}
	cout<<endl;
	
	cout<<"--------------------------------------------"<<endl;
	
	HashMap<Hashable, Hashable> *hashset2=new ZipHashMap<Hashable, Hashable>(dev, dev);
	cout<<"hashset2 = "<<endl;
	cout<<hashset2->toString()<<endl;
	
	cout<<"--------------------------------------------"<<endl;
	
	ZipHashMap<Hashable, Hashable> hashset3;
	hashset3=hashset;
	cout<<"hashset3 = "<<endl;
	cout<<hashset3.toString()<<endl;
	
	cout<<"--------------------------------------------"<<endl;
	
	cout<<(hashset==hashset3)<<endl;
	hashset3.insert(Hashable(1), Hashable(1)); 
	cout<<(hashset==hashset3)<<endl;
	ZipHashMap<Hashable, Hashable> hashset4=hashset3;
	hashset4.remove(dev[0]);
	cout<<(hashset4==hashset3)<<endl;
	
	cout<<"--------------------------------------------"<<endl;
	
	for(int i=0;i<5;i++)
	{
		hashset.remove(dev[i]);
	}
	hashset.remove(Hashable(2));
	cout<<hashset.length()<<endl;
	cout<<"hashset = "<<endl;
	cout<<hashset.toString()<<endl;
	
	cout<<"--------------------------------------------"<<endl;
	cout<<"下面是扩容测试"<<endl;
	
	vector<Hashable> data; 
	for(int i=0;i<10;i++)    // 11个元素，未发生哈希扩容操作 
	{
		data.push_back(Hashable(rand())); 
	}
	
	ZipHashMap<Hashable, Hashable> hashset5(data, data);
	
	cout<<hashset5.length()<<endl;
	cout<<"hashset5 = "<<endl;
	cout<<hashset5.toString()<<endl;
	
	for(int i=0;i<5;i++)    // 再随机插入5个整数，发生哈希扩容操作 
	{
		Hashable temp=Hashable(rand());
		hashset5.insert(temp, temp);
	} 
	
	cout<<hashset5.length()<<endl;
	cout<<"hashset5 = "<<endl; 
	cout<<hashset5.toString()<<endl;
	
	for(int i=0;i<100;i++)   // 大范围随机测试 
	{
		Hashable temp=Hashable(rand());
		hashset5.insert(temp, temp);
	}
	cout<<hashset5.length()<<endl;
	cout<<"hashset5 = "<<endl; 
	cout<<hashset5.toString()<<endl; 
	
	cout<<"--------------------------------------------"<<endl;
	ZipHashMap<Hashable, Hashable> hashset6(move(hashset5));
	cout<<hashset6.length()<<endl;
	ZipHashMap<Hashable, Hashable> hashset7=ZipHashMap<Hashable, Hashable>()=move(hashset6);
	cout<<hashset7.length()<<endl;
	cout<<hashset6.length()<<endl;
}
