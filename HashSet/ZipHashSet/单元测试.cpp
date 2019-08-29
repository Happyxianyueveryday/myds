#include "ZipHashSet.h"
#include "TestElement.h"
using namespace std;
 
int main(void)
{
	ZipHashSet hashset;
	HashElement *val1=new TestElement(1), *val2=new TestElement(2), *val3=new TestElement(16), *val4=new TestElement(37), *val5=new TestElement(64), *val6=new TestElement(37);
	hashset.insert(val1);
	hashset.insert(val2);
	hashset.insert(val3);
	hashset.insert(val4);
	hashset.insert(val5);
	hashset.insert(val6);
	cout<<hashset.toString()<<endl;
	
	HashElement *dev1=new TestElement(1), *dev2=new TestElement(2), *dev3=new TestElement(16), *dev4=new TestElement(37), *dev5=new TestElement(64), *dev6=new TestElement(37);
	HashElement *dev7=new TestElement(55), *dev8=new TestElement(102);
	cout<<hashset.contain(dev1)<<endl;
	cout<<hashset.contain(dev2)<<endl;
	cout<<hashset.contain(dev3)<<endl;
	cout<<hashset.contain(dev4)<<endl;
	cout<<hashset.contain(dev5)<<endl;
	cout<<hashset.contain(dev6)<<endl;
	cout<<hashset.contain(dev7)<<endl;
}
