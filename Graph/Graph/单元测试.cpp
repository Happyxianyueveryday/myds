#include <iostream>
#include "Graph.h"

using namespace std;

int main(void)
{
	// 1. 测试构造函数
	Graph graph1;   // 默认构造函数
	graph1.print();

	int lis[]={0,2,4,1,-1,-1,-1,2,0,-1,3,10,-1,-1,4,-1,0,2,-1,5,-1,1,3,2,0,7,8,4,-1,10,-1,7,0,-1,6,-1,-1,5,8,-1,0,1,-1,-1,-1,4,6,1,0};
	Graph graph2(lis, 7);  // 由数组构造的构造函数
	graph2.print();

	int array[6][6]={ {0,6,1,5,-1,-1},
					  {6,0,5,-1,3,-1},
					  {1,5,0,5,6,4},
					  {5,-1,5,0,-1,2},
					  {-1,3,6,-1,0,6},
					  {-1,-1,4,2,6,0},
					};   // 距离为-1表示两结点之间距离为无穷大
	Graph special((const int *)array, 6);

	// 2. 测试拷贝控制函数
	Graph graph3(special);    // 拷贝构造函数
	graph3.print();

	vector<int> res;

	// 3. 测试广度优先遍历和深度优先遍历
	cout<<"graph2的深度优先搜索 dfs = "<<endl;
	res=graph2.dfs(1);
	for(int i=0;i<res.size();i++)
	{
		cout<<res[i]<<" ";
	}
	cout<<endl;

	cout<<"graph3的深度优先搜索 dfs = "<<endl;
	res=graph3.dfs(1);
	for(int i=0;i<res.size();i++)
	{
		cout<<res[i]<<" ";
	}
	cout<<endl;

	cout<<"graph2的广度优先搜索 bfs = "<<endl;
	res=graph2.bfs(1);
	for(int i=0;i<res.size();i++)
	{
		cout<<res[i]<<" ";
	}
	cout<<endl;

	cout<<"graph3的广度优先搜索 bfs = "<<endl;
	res=graph3.bfs(1);
	for(int i=0;i<res.size();i++)
	{
		cout<<res[i]<<" ";
	}
	cout<<endl;

	// 4. 测试最短距离路径的dijkstra算法和floyd算法
	cout<<"使用dijkstra算法求解graph2中结点0到其他结点的最短距离 dijkstra = "<<endl;
	res=graph2.dijkstra(0);
	for(int i=0;i<res.size();i++)
	{
		cout<<res[i]<<" ";
	}
	cout<<endl;

	cout<<"使用dijkstra算法求解graph3中结点0到其他结点的最短距离 dijkstra = "<<endl;
	res=graph3.dijkstra(0);
	for(int i=0;i<res.size();i++)
	{
		cout<<res[i]<<" ";
	}
	cout<<endl;

	cout<<"使用floyd算法求解graph2中结点0到其他结点的最短距离 floyd = "<<endl;
	res=graph2.floyd(0);
	for(int i=0;i<res.size();i++)
	{
		cout<<res[i]<<" ";
	}
	cout<<endl;

	cout<<"使用floyd算法求解graph3中结点0到其他结点的最短距离 floyd = "<<endl;
	res=graph3.floyd(0);
	for(int i=0;i<res.size();i++)
	{
		cout<<res[i]<<" ";
	}
	cout<<endl;

	// 5. 测试最小生成树的prim算法和kruskkal算法
	cout<<"使用prim算法求解graph2的最小生成树 prim = "<<endl;
	Graph res2;
	res2=graph2.prim();
	res2.print();

	cout<<"使用kruskkal算法求解graph2的最小生成树 kruskkal = "<<endl;
	Graph res3;
	res3 = graph2.kruskkal();
	res3.print();

	cout<<"使用prim算法求解graph3的最小生成树 prim = "<<endl;
	Graph res4;
	res4=graph3.prim();
	res4.print();

	cout<<"使用kruskkal算法求解graph3的最小生成树 kruskkal = "<<endl;
	Graph res5;
	res5 = graph3.kruskkal();
	res5.print();
}
