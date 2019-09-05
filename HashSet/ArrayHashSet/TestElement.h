#ifndef TESTELEMENT_H
#define TESTELEMENT_H
#include "HashElement.h" 
#include <string>  
#include <iostream>

using namespace std;  

/**
 * TestElement: �̳�HashElement�������࣬������ʹ�õĹ�ϣ��Ԫ������  
 * note: ���������ṩ��һ��Ӧ����μ̳�HashElement����д���еķ�������֧��ʹ��HashSet��ZipHashSet�� 
 */
class TestElement: public HashElement
{
	public:
	TestElement(int _val);                              		 // Ĭ�Ϲ��캯�� 
	int hashCode() const override;                               // ���㵱ǰԪ�صĹ�ϣֵ 
    bool equals (const HashElement *other) const override;       // �������������������б���Ҫʹ��dynamic_cast 
    HashElement *clone() const override; 					     // �鿽������
    string toString() const override;                            // �ַ��������ǰԪ�� 
    ~TestElement() override;                                     // ����������
    
    private: 
    int val;    // ʵ�ʴ洢��ֵ������Ԫ������ʵ���Ͼ��Ǽ򵥷�װ��һ��intֵ 
};

TestElement::TestElement(int _val)
{
	val=_val;
}

int TestElement::hashCode() const
{
	return val;
}

bool TestElement::equals(const HashElement *other) const
{
	const TestElement *other_cast=dynamic_cast<const TestElement *>(other);   // dynamic_cast�����������ת�ͺ�����ת�ͣ��������ת�ͺ�����ת��ʹ�� 
	if(!other_cast)                    // ���dynamic_castʧ�ܣ���ʱ�����ָ�벻��TestElement�������˷���false 
	return false;
	else if(this->val==other_cast->val)// ���dynamic_cast�ɹ��������ߵ�ֵ��ȣ�������������ȣ�����true 
	return true;
	else                               // ���������������������� 
	return false;
}

HashElement *TestElement::clone() const
{
	return new TestElement(val);
}

string TestElement::toString() const
{
	return to_string(val);
}

TestElement::~TestElement() 
{
	//cout<<"TestElement����������������"<<endl; 
}                                 

#endif
