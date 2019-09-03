#include <iostream>
#include <string>
#include "DiGraph.h"

using namespace std;

int main(void)
{
	double data[]={-1,1,-1,1,-1,-1,-1,1,1,-1,-1,-1,-1,-1,1,-1,-1,1,-1,1,-1,-1,-1,-1,-1};

	DiGraph gra(data, 5);

	vector<int> res;
	if(gra.topoSort1(res))
	{
		cout<<"拓扑排序成功，有向图gra1的拓扑排序 = ";
		for(int i=0;i<res.size();i++)
		{
			cout<<res[i]<<" ";
		}
		cout<<endl;
	}
	else
		cout<<"原有向图中存在环，拓扑排序失败"<<endl;

	vector<int> res2;
	if(gra.topoSort2(res2))
	{
		cout<<"拓扑排序成功，有向图gra1的拓扑排序 = ";
		for(int i=0;i<res2.size();i++)
		{
			cout<<res2[i]<<" ";
		}
		cout<<endl;
	}
	else
		cout<<"原有向图中存在环，拓扑排序失败"<<endl;


	double data2[]={-1,3,2,-1,-1,-1,-1,-1,-1,2,3,-1,-1,-1,-1,4,-1,3,-1,-1,-1,-1,-1,2,-1,-1,-1,-1,-1,1,-1,-1,-1,-1,-1,-1};

	DiGraph gra2(data2, 6);

	vector<int> res3;
	if(gra2.topoSort1(res3))
	{
		cout<<"拓扑排序成功，有向图gra2的拓扑排序 = ";
		for(int i=0;i<res3.size();i++)
		{
			cout<<res3[i]<<" ";
		}
		cout<<endl;
	}
	else
		cout<<"原有向图中存在环，拓扑排序失败"<<endl;

	vector<int> res4;
	if(gra2.topoSort2(res4))
	{
		cout<<"拓扑排序成功，有向图gra2的拓扑排序 = ";
		for(int i=0;i<res4.size();i++)
		{
			cout<<res4[i]<<" ";
		}
		cout<<endl;
	}
	else
		cout<<"原有向图中存在环，拓扑排序失败"<<endl;
}
