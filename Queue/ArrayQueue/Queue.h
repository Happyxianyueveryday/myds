#include <iostream>
#include <string>

using namespace std;

/**
 * Queue: ���еĳ������
 * note 1: ע�⣬virtual����ָ���麯����cpp�Ĵ��麯��ʹ��=0�ļǺ������������麯�����麯���ĸ���Ҫ������� 
 * note 2: ֻҪ����һ�����麯�����������ǳ�����࣬����������ͨ����һ�£����������������������Ϊ�˶�̬�󶨵���Ҫ 
 */
class Queue
{
	public:
    virtual bool push(int val) = 0;            // ������Ӳ���
    virtual bool pop(int &val) = 0;            // ���г��Ӳ���
    virtual bool frontval(int &val) const = 0; // ��ȡ����Ԫ��
    virtual int length() const = 0;            // ������г��ȣ��������е�Ԫ�ظ���
    virtual ~Queue() {};                      // ��������������ע���κεĻ��඼��������������������������ͬ�� 
};
