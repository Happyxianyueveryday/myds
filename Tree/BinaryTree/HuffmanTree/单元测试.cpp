#include <iostream>
#include "HuffmanTree.h"

using namespace std;

int main(void)
{
	int data[]={9,16,5,12,13,45};

	HuffmanTree huffman(data, 6);

	cout<<"所创建的哈夫曼树的层次遍历序列为: "<<huffman.toString()<<endl;

	HuffmanTree huffman2(huffman);
	HuffmanTree huffman3=huffman2;
	cout<<"所拷贝的哈夫曼树的层次遍历序列为: "<<huffman2.toString()<<endl;
	cout<<"所拷贝的哈夫曼树的层次遍历序列为: "<<huffman3.toString()<<endl;


	map<int, string> dic=huffman.getHuffmanCode();

	for(int i=0;i<6;i++)
	{
		cout<<"叶子结点"<<data[i]<<"对应的哈夫曼编码为: "<<dic[data[i]]<<endl;
	}
}
