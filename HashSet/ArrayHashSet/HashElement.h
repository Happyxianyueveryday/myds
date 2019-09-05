#ifndef HASHELEMENT_H
#define HASHELEMENT_H 
#include <iostream> 
#include <string>    
 
using namespace std;   

/**
 * HashElement: ��ϣԪ�ؽӿڳ������
 * note 1: ����ʹ�ù�ϣ���ϻ��߹�ϣӳ���洢��Ԫ�ض�����̳иýӿڵĳ�����࣬��ʵ�����е�hashCode�������=�����ұ�����д������������ʵ��clone���� 
 */ 
class HashElement
{
    public:
    virtual int hashCode() const = 0;                               // ���㵱ǰԪ�صĹ�ϣֵ 
    virtual bool equals(const HashElement *other) const = 0;   	    // ��������
    virtual HashElement *clone() const = 0;                         // �鿽���������鿽����������������� 
    virtual string toString() const = 0;                            // �ַ��������ǰԪ�� 
    virtual ~HashElement() {};                                      // ����������
};

#endif
