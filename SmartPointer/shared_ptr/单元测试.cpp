#include "shared_ptr.h"
#include "TestElement.h"

using namespace std;
 
int main(void)
{
	shared_ptr<TestElement> pos1, pos2, pos3;
	pos1->print();
	(*pos1).print();
	for(int i=0;i<5;i++)
	{
		shared_ptr<TestElement> *temp=new shared_ptr<TestElement>();
		delete temp;
	}
	
	pos3=pos2;
	pos2=pos1;
	{
		shared_ptr<TestElement> pos9, pos10(pos9);
		pos2=pos9;
		pos10=pos1;
	}
}
