#ifndef LIST_H
#define LIST_H
#include <string>

using namespace std; 

class List  
{
	public:
	virtual bool get(int index, int &val) const = 0;    // ����ָ��λ�û�ȡԪ�� 
    virtual bool insert(int index, int val) = 0;        // ����ָ��λ�ò���Ԫ��
    virtual bool remove(int index, int &val) = 0;       // ����ָ��λ��ɾ��Ԫ��
    virtual int length() const = 0;                     // ��ȡ����ĳ���
    virtual void reverse() = 0;                         // ԭ�ط�ת��������
    virtual int middle() const = 0;                     // ���������м����ֵ
    virtual string toString() const = 0;                // �����ǰ���� 
	virtual ~List() {};                                 // ���������� 
};

#endif 
