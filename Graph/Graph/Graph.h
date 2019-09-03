#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <cstring>
#include <algorithm>
#include <limits>
#include <cfloat>

using namespace std;

// 0. 定义表示图的边的自定义数据结构
struct Edge
{
	Edge(int ix, int iy, double ilen):x(ix), y(iy), len(ilen)
	{
	}

	int x;     // 端点1
	int y;	   // 端点2
	double len;   // 边长
};

bool compare(const Edge &a, const Edge &b)
{
	return a.len<b.len;
}

/*
* Graph: 无向图类
*/
class Graph
{
    public:

    // 1. 构造函数
    Graph();                                      // 默认构造函数
    Graph(int isize);                              // 初始化一个含有size个结点的图，图中默认没有任何的边
    Graph(const vector<vector<int> > &lis);       // 从邻接矩阵数组(vector)构造图，图中的结点依次被命名为0,1,...,size-1
    Graph(const int *lis, int isize);             // 从邻接矩阵数组构造图

    // 2. 拷贝控制
    Graph(const Graph &gra);                      // 拷贝构造函数
    Graph & operator = (const Graph &other);      // 拷贝赋值运算符

    // 3. 基本操作与功能
    vector<int> bfs(int start);                   // 图的广度优先搜索
    vector<int> dfs(int start);                   // 图的深度优先搜索

    vector<int> dijkstra(int start);              // 计算某个结点到所有其他各个结点的最短路径长度: dijkstra算法
    vector<int> floyd(int start);                 // 计算某个结点到所有其他各个结点的最短路径长度: floyd算法

    Graph prim();                                 // 产生最小生成树: prim算法
    Graph kruskkal();                             // 产生最小生成树: krustkal算法

    void print();                                 // 输出图的邻接表

    // 4. 析构函数
    ~Graph();                                     // 析构函数

    private:
    double **data;                                   // 图的邻接矩阵: 矩阵元素值为-1表示两个结点之间不相邻，之间的距离为无穷大
    int size;                                     // 图的大小

    bool hasloop(Graph gra, int u, int v, int len);  // 判断给定的图增加一条边u,v后是否有环
};

/*
 * Graph: 默认构造函数
*/
Graph::Graph()
{
    data=NULL;
    size=0;
}

/*
 * Graph: 构造固定大小的无边图
*/
Graph::Graph(int isize)
{
	// 0. 计算邻接表大小
    size=isize;

    // 1. 申请邻接表空间
    data=new double *[size];

    for(int i=0;i<size;i++)
    {
        data[i]=new double[size];
    }

    // 2. 初始化邻接表为仅含结点而没有边的图
	for(int i=0;i<size;i++)
	{
		for(int k=0;k<size;k++)
		{
			if(i==k)
			data[i][k]=0;
			else
			data[i][k]=DBL_MAX;
		}
	}
}

/*
 * Graph: 从邻接矩阵数组(vector)构造图
*/
Graph::Graph(const vector<vector<int> > &lis)
{
    // 0. 计算邻接表大小
    size=lis.size();

    // 1. 申请邻接表空间
    data=new double *[size];

    for(int i=0;i<size;i++)
    {
        data[i]=new double[size];
    }

    // 2. 拷贝邻接表内容
    for(int i=0;i<size;i++)
    {
        for(int k=0;k<size;k++)
        {
        	if(lis[i][k]!=-1)
        		data[i][k]=lis[i][k];
        	else
        		data[i][k]=DBL_MAX;
        }
    }
}

/*
 * Graph: 从邻接矩阵数组构造图
*/
Graph::Graph(const int *lis, int isize)
{
	size=isize;

	// 1. 申请邻接表空间
    data=new double *[size];

    for(int i=0;i<size;i++)
    {
        data[i]=new double[size];
    }

    // 2. 拷贝邻接表内容
    for(int i=0;i<size;i++)
    {
        for(int k=0;k<size;k++)
        {
            // 这里仅使用一维数组指针lis来进行二维数组的传参，实际上lis指针指向二维数组的首元素，因为使用的是一维指针，因此必须使用lis[i*size+k]来代替lis[i][k]
        	if(lis[i*size+k]!=-1)
        		data[i][k]=lis[i*size+k];
        	else
        		data[i][k]=DBL_MAX;
        }
    }
}

/*
 * Graph: 拷贝构造函数
*/
Graph::Graph(const Graph &other)
{
    // 1. 重新申请和拷贝源相同大小的邻接表内存
    size=other.size;
    data=new double*[size];

    for(int i=0;i<size;i++)
    {
        data[i]=new double[size];
    }

    // 2. 拷贝邻接表内容
    for(int i=0;i<size;i++)
    {
        for(int k=0;k<size;k++)
        {
            data[i][k]=other.data[i][k];
        }
    }
}

/*
 * operator = : 拷贝赋值运算符
*/
Graph & Graph::operator = (const Graph &other)
{
    // 0. 处理自我赋值的情况
    if(&other==this)
    return (*this);

    // 1. 释放当前邻接表内存
    for(int i=0;i<size;i++)
    {
        delete [] data[i];
    }
    delete [] data;

    // 2. 重新申请和拷贝源相同大小的邻接表内存
    size=other.size;
    data=new double*[size];

    for(int i=0;i<size;i++)
    {
        data[i]=new double[size];
    }

    // 3. 拷贝邻接表内容
    for(int i=0;i<size;i++)
    {
        for(int k=0;k<size;k++)
        {
            data[i][k]=other.data[i][k];
        }
    }

    return (*this);
}

/*
 * print: 输出邻接表
*/
void Graph::print()
{
	for(int i=0;i<size;i++)
	{
		for(int k=0;k<size;k++)
		{
			if(data[i][k]!=DBL_MAX)
				cout<<data[i][k]<<" ";
			else
				cout<<-1<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

/**
 * bfs: 对原图进行广度优先搜索
 * param start: 广度优先搜索的起始结点
 * return: 当前图的广度优先搜索序列，若输入的起始结点下标不合法，则返回空的遍历序列
 * note: 图的广度优先搜索的基本步骤为：（1） 将起始结点入队；（2）循环进行以下步骤直到队列为空为止：从队首出队一个结点，若该结点未访问，则依次进行以下步骤：（a）输出该结点，（b）将该结点标记为已访问，（c）将该结点的所有相邻的未访问的结点依次入队
 */
vector<int> Graph::bfs(int start)
{
	vector<int> res;
	if(start<0||start>=size)
		return res;

	queue<int> que;
	que.push(start);

	bool visit[size];
	memset(visit, 0, size*sizeof(bool));

	while(que.size())
	{
		int now=que.front();

		que.pop();

		if(visit[now])
			continue;

		res.push_back(now);
		visit[now]=true;

		for(int i=0;i<size;i++)
		{
			if(!visit[i]&&data[now][i]!=DBL_MAX)
				que.push(i);
		}
	}

	return res;
}

/**
 * dfs: 对原图进行深度优先搜索
 * param start: 深度优先搜索的起始结点
 * return: 当前图的深度优先搜索序列，若输入的起始结点下标不合法，则返回空的遍历序列
 * note: 图的广度优先搜索的基本步骤为：（1）将起始结点入栈；（2）循环进行以下步骤直到栈为空为止：从栈中出栈一个结点，若该结点未访问，则依次执行下列步骤：（a）输出该结点，（b）将该结点标记为已访问，（c）将该节点所有的未访问的邻居结点入栈
 */
vector<int> Graph::dfs(int start)
{
	vector<int> res;
	if(start<0||start>=size)
		return res;

	stack<int> que;
	que.push(start);

	bool visit[size];
	memset(visit, 0, size*sizeof(bool));

	while(que.size())
	{
		int now=que.top();

		que.pop();

		if(visit[now])
			continue;

		res.push_back(now);
		visit[now]=true;

		for(int i=0;i<size;i++)
		{
			if(!visit[i]&&data[now][i]!=DBL_MAX)
				que.push(i);
		}
	}

	return res;
}


/**
 * dijkstra: 计算单源最短路径的dijkstra算法
 * param start: 单源最短路径的起始结点
 * return: 指定的起始结点到所有其他结点的最短路径
 * note: dijkstra算法的基本步骤为：（1）将图中的所有结点划分为集合S和集合N，集合S中包含起始结点，集合N中包含图中的其他结点
 * 			                                               （2）初始化集合N中的各个结点i到集合S中的起始结点start的距离dist[i]，初始化公式为：dist[i]=data[i][start]
 * 			                                               （3）循环进行以下步骤直到集合S中包含所有结点为止：（a）从集合N中找到一个到start的当前距离dist[i]最短的结点k，（b）将结点k从集合N中删除并加入集合S中，（b）更新集合N中剩下的结点i通过集合S中的点到达起始点start的最短路径dist[i]，更新公式为：dist[i]=min(dist[i], data[i][k]+dist[k])
 */
vector<int> Graph::dijkstra(int start)
{
	vector<int> res;

	if(start<0||start>=size)
		return res;

	double dist[size];
	bool visit[size];

	for(int i=0;i<size;i++)
	{
		dist[i]=data[i][start];
		visit[i]=false;
	}

	visit[start]=true;
	int count=1;

	while(count<size)
	{
		int minpos=-1;
		double minvalue=DBL_MAX;
		for(int i=0;i<size;i++)
		{
			if(!visit[i]&&dist[i]<minvalue)
			{
				minvalue=dist[i];
				minpos=i;
			}
		}

		visit[minpos]=true;
		count+=1;

		for(int i=0;i<size;i++)
		{
			if(!visit[i]&&data[i][minpos]+dist[minpos]<dist[i])
				dist[i]=data[i][minpos]+dist[minpos];
		}
	}

	for(int i=0;i<size;i++)
	{
		if(dist[i]!=DBL_MAX)
			res.push_back(dist[i]);
		else
			res.push_back(-1);
	}

	return res;
}

/**
 * floyd: 计算多源最短路径的floyd算法
 * param start: 指定的起始结点
 * return: 指定结点到其他结点的最短路径
 * note: floyd算法的核心公式表述是：data[i][j]=min(data[i][m]+data[m][j], data[i][j])，只需首先依次选择每个中间结点m，然后对每对起点终点应用该公式即可
 */
vector<int> Graph::floyd(int start)
{
	vector<int> res;

	if(start<0||start>=size)
		return res;

	double dist[size][size];

	for(int i=0;i<size;i++)
	{
		for(int k=0;k<size;k++)
		{
			dist[i][k]=data[i][k];
		}
	}

	for(int k=0;k<size;k++)  // 选择从起点到终点之间的中间结点
	{
		for(int i=0;i<size;i++)  // 选择起点结点
		{
			for(int j=0;j<size;j++)  // 选择终点结点
			{
				if(dist[i][k]+dist[k][j]<dist[i][j])
					dist[i][j]=dist[i][k]+dist[k][j];
			}
		}
	}

	for(int i=0;i<size;i++)
	{
		if(dist[start][i]!=DBL_MAX)
			res.push_back(dist[start][i]);
		else
			res.push_back(-1);
	}

	return res;
}

/**
 * prim: 生成最小生成树的prim算法
 * return: 当前图的最小生成树
 * note: prim算法的基本步骤为：（1）初始化集合S中包含图中任意一个结点start，集合N中包含图中的其他结点
 * 						  （2）初始化集合N中的结点i到集合S的距离dist[i]，到集合S的距离定义为到集合S中的点的距离中的最小值，初始化公式为：dist[i]=data[i][start]
 * 						  （3）循环进行以下步骤直到集合S中包含图中所有的结点为止：（a）选择集合N中到集合S的距离dist[i]最短的结点k，（b）将结点k从集合N中删除，并加入集合S，将对应的边加入结果中，（c）更新集合N中的各个结点到集合S的距离，更新公式为：dist[i]=min(dist[i], data[i][k])
 */
Graph Graph::prim()
{
	int res[size][size];
	double dist[size];
	int distnode[size];
	bool visit[size];

	int start=0;

	for(int i=0;i<size;i++)
	{
		for(int k=0;k<size;k++)
		{
			if(i!=k)
				res[i][k]=-1;
			else
				res[i][k]=0;
		}
	}

	for(int i=0;i<size;i++)
	{
		dist[i]=data[i][start];
		distnode[i]=start;
		visit[i]=false;
	}

	visit[start]=true;
	int count=1;

	while(count<size)
	{
		int minpos=-1;
		double minvalue=DBL_MAX;

		for(int i=0;i<size;i++)
		{
			if(!visit[i]&&dist[i]<minvalue)
			{
				minvalue=dist[i];
				minpos=i;
			}
		}

		visit[minpos]=true;
		res[minpos][distnode[minpos]]=data[minpos][distnode[minpos]];
		res[distnode[minpos]][minpos]=data[distnode[minpos]][minpos];
		count+=1;

		for(int i=0;i<size;i++)
		{
			if(!visit[i])
			{
				if(data[i][minpos]<dist[i])
				{
					dist[i]=data[i][minpos];
					distnode[i]=minpos;
				}
			}
		}
	}

	Graph tar=Graph((const int *)res, size);

	return tar;
}

/**
 * kruskkal: 生成最小生成树的kruskkal算法
 * return: 原图的最小生成树
 */
Graph Graph::kruskkal()
{
	Graph res(size);   // 创建一个和当前图大小相同的图，该图即为最终的最小生成树

	// 1. 初始化所有边的列表
	vector<Edge> edge;
	for(int i=0;i<size;i++)
	{
		for(int k=0;k<i+1;k++)    // 注意: k<i+1的目的是保证排除重复边，例如u-v和v-u是同一条边，只需要记录其中一个即可
		{
			if(data[i][k]!=0)     // 排除结点自身的边长
			edge.push_back(Edge(i,k,data[i][k]));
		}
	}

	// 2. 按照边长从小到大对列表进行排序
	sort(edge.begin(),edge.end(),compare);

	// 3. 初始化集合S和集合N，集合S初始情况下仅包含最短的边，集合N包含其他边
	bool visit[edge.size()];
	memset(visit, 0, edge.size()*sizeof(bool));

	visit[0]=true;     // 将最短的边加入集合S，其他的边加入集合N, visit[i]=true表明边edge[i]在集合S中，否则在集合N中
	res.data[edge[0].x][edge[0].y]=edge[0].len;       // 将集合S中的边写入结果图中
	res.data[edge[0].y][edge[0].x]=edge[0].len;

	// 4. 循环进行以下步骤直到集合S加入了(n-1)条边时停止：从集合N中选出最短的且能保证加入集合S后不会产生环的边，将该边从集合N中删除并加入集合S
	int count=1;      // 集合S所包含的边数

	for(int i=1;i<edge.size();i++)
	{
		if(count==size-1)
		break;

		if(!hasloop(res, edge[i].x, edge[i].y, edge[i].len))   // 若将边edge[i]加入集合S中不会导致出现环，则将该边加入集合S
		{
			count+=1;
			visit[i]=true;   // 将符合不出现环的边从集合N中删除，并加入集合S

			res.data[edge[i].x][edge[i].y]=edge[i].len;       // 将新加入集合S的边写入结果图中
			res.data[edge[i].y][edge[i].x]=edge[i].len;
		}
	}

	return res;
}

/**
 * hasloop: 判断将边加入图中后是否存在环
 */
bool Graph::hasloop(Graph gra, int u, int v, int len)
{
	gra.data[u][v]=len;   // 将边加入给定的图中
	gra.data[v][u]=len;

	stack<int> sta;
	bool visit[gra.size];    // 用于记录对应结点是否已经被访问过的数组
	memset(visit, 0, (gra.size)*sizeof(bool));
	sta.push(v);

	while(sta.size())
	{
	    int temp=sta.top();
	    sta.pop();

	    // 若栈中弹出的结点已经访问过，则说明图中存在环
	    if(visit[temp])
	    {
	    	return true;
	    }
	    else
	    {
	    	visit[temp]=true;

	    	for(int i=0;i<size;i++)
	        {
	            if(gra.data[temp][i]!=DBL_MAX&&!visit[i])
	            	sta.push(i);
	        }
		}
	 }

	 return false;
}


/*
 * ~Graph: 析构函数
*/
Graph::~Graph()
{
    if(data!=NULL)
    {
        for(int i=0;i<size;i++)
        {
            delete [] data[i];
        }
        delete [] data;
    }
}

