package com.pzh.graphalgorithm;

import java.util.*;

public class GraphAlgorithm 
{
	// 1. domains
	public static double INF=Double.POSITIVE_INFINITY;
	
	// 2. methods
	// 2.1 无向图中环的存在性
	/**
	 * @hasCycle: 判断给定的无向图是否存在环
	 * @param graph: 输入的无向图的邻接矩阵
	 * @param size: 输入的无向图的结点个数
	 * @note: 无向图是否存在环的最简单的判断方法就是直接使用dfs，从每一个结点开始进行一次dfs，若在dfs遍历过程中遇到已经访问过的结点，则说明原图中存在环，否则不存在环
	 */
	public static boolean hasCycle(double [][] graph, int size)
	{
		for(int i=0;i<size;i++)
		{
			Stack<Integer> sta=new Stack<Integer> ();
			boolean [] visit=new boolean [size];
			
			sta.push(i);
			
			while(!sta.empty())
			{
				int now=sta.pop();
				
				if(visit[now]==true)
					return true;
				
				visit[now]=true;
				
				for(int k=0;k<size;k++)
				{
					if(graph[now][k]!=INF)    // 这里无需判断是否已经访问过，否则对环的判断有影响
						sta.push(k);
				}
			}
		}
		return false;
	}
	
	// 2.2 有向图中环的存在性
	/**
	 * @diHasCycle: 判断给定的有向图是否存在环
	 * @param digraph: 输入的有向图的邻接矩阵
	 * @param size: 输入的有向图的结点个数
	 * @note: 判断有向图是否存在环的方法同样不唯一，常见的一种方法是使用拓扑排序：若对给定的有向图进行拓扑排序后得到完整的拓扑排序序列，则说明原图中不存在环
	 */
	public static boolean diHasCycle(double [][] digraph, int size)
	{
		Stack<Integer> sta=new Stack<Integer> ();
		ArrayList<Integer> res=new ArrayList<Integer> ();
		boolean [] visit=new boolean [size];
		
		int [] degree=new int [size];   // 记录图中各个结点的入度
		for(int i=0;i<size;i++)
		{
			int count=0;
			for(int k=0;k<size;k++)
			{
				if(digraph[k][i]!=INF)
					count+=1;
			}
			degree[i]=count;
		}
		
		for(int i=0;i<size;i++)
		{
			if(degree[i]==0)
				sta.push(i);
		}
		
		while(!sta.empty())
		{
			int now=sta.pop();
			
			if(visit[now]==true)
				continue;
			
			visit[now]=true;
			res.add(now);
			
			for(int i=0;i<size;i++)
			{
				if(digraph[now][i]!=INF)
					degree[i]-=1;
				if(degree[i]==0&&visit[i]==false)
					sta.push(i);
			}
		}
		
		if(res.size()!=size)
			return true;
		else
			return false;
	}
	
	// 2.3 有向图的连通性
	/**
	 * @isConnect: 判断给定的无向图是否连通
	 * @param graph: 输入的无向图的邻接矩阵
	 * @param size: 输入的无向图的结点个数
	 * @return: 若输入的无向图为连通的，则返回true；否则返回false
	 * @note: 判断无向图的连通性只需要进行一次dfs或者bfs即可，若一次遍历后所遍历的结点数量等于图中总的结点数量，则给定的无向图是连通的，否则不是连通的
	 */
	public static boolean isConnect(double [][] graph, int size)
	{
		int count=0;
		
		Stack<Integer> sta=new Stack<Integer> ();
		boolean [] visit=new boolean [size];
		
		sta.push(0);
		
		while(!sta.empty())
		{
			int now=sta.pop();
			
			if(visit[now]==true)
				continue;
			
			count+=1;
			visit[now]=true;
			
			for(int i=0;i<size;i++)
			{
				if(graph[now][i]!=INF)   // 这里也可以加上条件&&visit[i]==false来进行进一步优化，减少执行时间，但是不加也可以正常进行dfs
					sta.push(i);
			}
		}
		
		if(count==size)
			return true;
		else
			return false;
	}
	
	// 2.4 有向图的三类连通性：弱连通性，单向连通性，强连通性
	/**
	 * @diWeakConnect: 判断给定的有向图是否为弱连通的
	 * @param digraph: 输入的有向图的邻接矩阵
	 * @param size: 输入的有向图的结点个数
	 * @return: 若输入的有向图为弱连通的，则返回true；否则返回false
	 * @note 1: 有向图的弱连通性的标准定义是：将有向图中的有向边换成无向边后，得到的无向图是连通的，则这时称该有向图是弱连通的
	 * @note 2: 最常见的判断弱连通性的方法是将原有向图转化为无向图进行判断，该具体的算法步骤为：
	 *           （1）将原有向图中的有向边转化无向边，（2）直接调用无向图的连通性判断方法进行判断
	 */
	public static boolean diWeakConnect(double [][] digraph, int size)
	{
		double [][] data=new double [size][size];
		for(int i=0;i<size;i++)
		{
			for(int k=0;k<size;k++)
			{
				if(digraph[i][k]!=INF)
					data[i][k]=data[k][i]=digraph[i][k];
			}
		}
		
		return GraphAlgorithm.isConnect(data, size);
	}
	
	/**
	 * @diSingleConnect: 判断给定的有向图是否为单向连通的
	 * @param digraph: 输入的有向图的邻接矩阵
	 * @param size: 输入的有向图的结点个数
	 * @return: 若输入的有向图为单向连通的，则返回true；否则返回false
	 * @note 1: 有向图的单连通性是指：对于有向图中任意的两个结点a和b，都必定存在一条从a到b的路径或者是从b到a的路径
	 * @note 2: 最常见的判断单连通性的算法是基于拓扑排序算法来进行判断，该算法的基本步骤为：
	 * 		  （1）对原有向图进行一次拓扑排序（2）在拓扑排序中，每次从图中删除一个结点和对应的边后，检查图中的入度为0的结点个数，若结点个数为0或者1，则继续进行拓扑排序，若结点个数为2或者以上，则说明原有向图不是单连通的，直接返回false
	 * @note 3: 这里简单解释一下为什么在拓扑排序过程中遇到两个或者以上入度为0的点就说明有向图不是单连通的，因为如果在拓扑排序过程中遇到两个或者以上入度为0的点，那么这些点之间就是无法通过当前还在图中的结点相连的，因为这些点的入度均为0，另外，这些点之间也不可能通过拓扑排序过程中之前从图中删除的点相连，因为拓扑排序中每次删除的结点都是入度为0的结点，因此不存在从这些点到这些已删除结点的路径
	 */
	public static boolean diSingleConnect(double [][] digraph, int size)
	{
		double [][] data=new double [size][size];
		for(int i=0;i<size;i++)
		{
			for(int k=0;k<size;k++)
			{
				data[i][k]=digraph[i][k];
			}
		}
		
		int [] degree=new int [size];          // 各个结点的入度的数组
		boolean [] visit=new boolean [size];   // 记录各个结点是否已经从图中被删除的数组
		
		Stack<Integer> sta=new Stack<Integer> ();
		
		for(int i=0;i<size;i++)      // 初始化各个结点的入度的数组
		{
			int count=0;
			for(int k=0;k<size;k++)  
			{
				if(data[k][i]!=INF)
					count+=1;
			}
			degree[i]=count;
			if(degree[i]==0)
				sta.push(i);
		}
		
		while(sta.size()>0&&sta.size()<2)
		{
			int now=sta.pop();
			
			if(visit[now]==true)
				continue;
			
			visit[now]=true;
			
			for(int i=0;i<size;i++)
			{
				if(data[now][i]!=INF&&visit[i]==false)
				{
					data[now][i]=INF;
					degree[i]-=1;
					if(degree[i]==0)
						sta.push(i);
				}
			}
		}
		
		if(sta.size()>=2)
			return false;
		else
			return true;
	}
	
	/**
	 * @diStrongConnect: 判断给定的有向图是否为强连通的
	 * @param digraph: 输入的有向图的邻接矩阵
	 * @param size: 输入的有向图的结点个数
	 * @return: 若输入的有向图为强连通的，则返回true；否则返回false
	 * @note 1: 有向图的强连通性是指：对于给定有向图中的任意两个结点a和b，均同时存在从结点a到结点b的路径和从结点b到结点a的路径，则称该有向图是强连通的
	 * @note 2: 判断一个有向图是否为强连通一般直接使用求解强连通分量算法进行，请具体参考下面的有向图的强连通分量的求解算法，弱求解到藏剑强连通分量仅有一个，且该强连通分量中包含有向图中的所有结点，则原有向图就是强连通的
	 */
	public static boolean isStrongConnect(double [][] digraph, int size)
	{
		 ArrayList<ArrayList<Integer>> res=GraphAlgorithm.getStrongWeight(digraph, size);    // 从有向图中获得强连通分量
		 
		 if(res.size()==1&&res.get(0).size()==size)   // 若获取的强连通分量仅有一个，且包含所有结点，则原有向图就是强连通的
			 return true;
		 else                                         // 否则原有向图不是强连通的
			 return false;
	}
	
	// 2.5 有向图的强连通分量
	/**
	 * @getStrongWeight: 获取输入的有向图的强连通分量
	 * @param digraph: 输入的有向图的邻接矩阵
	 * @param size: 输入的有向图的结点个数
	 * @return: 原有向图中的各个强连通分量中所包含的结点
	 * @note: 判断有向图的强连通性最经常使用的是使用两次dfs的算法来进行解决，具体算法步骤如下所示。
	 *        （1）第一次改良dfs过程：从每个未访问的结点开始对原有向图进行一次改良dfs遍历，获得改良dfs遍历序列
	 *        （2）将原有向图进行反向，即将所有的有向边的方向反转
	 *        （3）第二次普通dfs过程：按照（1）中得到的改良dfs遍历序列的倒序，从每个未访问的结点开始进行一次普通dfs遍历，从每个结点开始的每次dfs遍历均得到一个原有向图的强连通分支
	 */
	public static ArrayList<ArrayList<Integer>> getStrongWeight(double [][] digraph, int size)
	{
		ArrayList<ArrayList<Integer>> res=new ArrayList<ArrayList<Integer>> ();
		
		ArrayList<Integer> dfs_res=GraphAlgorithm.dfs(digraph, size);     // 进行第一次dfs遍历，获得原有向图的dfs遍历序列
		
		double [][] reverse=new double [size][size];     // 将原有向图进行反转    
		for(int i=0;i<size;i++)                     
		{
			for(int k=0;k<size;k++)
			{
				reverse[i][k]=digraph[k][i];
			}
		}
		
		boolean [] visit=new boolean [size];
		for(int i=dfs_res.size()-1;i>=0;i--)       // 对反转后的原有向图进行第二次dfs遍历，按照第一次改良dfs遍历得到的倒序，从每个未访问的结点开始进行dfs，每次从某个结点开始的dfs遍历均组成一个强连通分支
		{
			int root=dfs_res.get(i);	// dfs普通遍历开始的根结点 ，注意根结点是dfs_res[i]而不是i本身
			if(visit[root]==false)      // 注意从未访问的结点开始进行一次dfs遍历，每次从某个结点开始的一次dfs均得到一个强连通分支
			{
				Stack<Integer> sta=new Stack<Integer> ();
				ArrayList<Integer> element=new ArrayList<Integer> ();    // 当前的强连通分支序列
				sta.push(root);    
				
				while(!sta.empty())
				{
					int now=sta.pop();
					
					if(visit[now]==true)
						continue;
					
					visit[now]=true;
					element.add(now);
					
					for(int k=0;k<size;k++)
					{
						if(reverse[now][k]!=INF&&visit[k]==false)
							sta.push(k);
					}
				}
				
				res.add(element);
			}
		}
		return res;
	}
	
	/**
	 * @dfs: 求解有向图强连通分量的附属方法：对原有向图进行一次改良的dfs遍历 
	 * @param digraph: 输入的有向图的邻接矩阵
	 * @param size: 输入的有向图的结点个数
	 * @return: 有向图的改良dfs遍历序列
	 * @note 1: 所谓改良dfs遍历，就是指在访问了当前结点所指向的后继结点之后，再访问当前结点的dfs遍历，改良dfs遍历主要的应用就是在上述的两次dfs求解有向图强连通分量算法中，以及基于dfs的拓扑排序中，改良的dfs遍历得到一个在逻辑上和普通dfs遍历逆序的序列
	 * @note 2: 改良dfs遍历推荐使用递归实现，减少出错的可能性，其基本步骤如下所示：
	 * 			（1） 将当前结点标记为已访问
	 *   		（2）递归访问当前结点所指向的邻居结点
	 *   		（3）正式访问当前结点，将当前结点的值加入到结果中
	 *   		需要特别注意，标记为已访问的步骤在递归访问邻居结点之前，而正式访问并加入结果的步骤在访问邻居结点之后
	 */
	private static ArrayList<Integer> dfs(double [][] digraph, int size)
	{
		ArrayList<Integer> res=new ArrayList<Integer> ();
		boolean [] visit=new boolean [size];
		
		for(int i=0;i<size;i++)
		{
			if(visit[i]==false)
				GraphAlgorithm.real_dfs(digraph, size, visit, res, i);
		}
		
		return res;
	}
	
	private static void real_dfs(double [][] digraph, int size, boolean [] visit, ArrayList<Integer> res, int pos)
	{
		if(visit[pos]==false)
		{
			visit[pos]=true;    // 注意先标注为已访问，但是最终的访问放在递归之后
			for(int i=0;i<size;i++)
			{
				if(digraph[pos][i]!=INF&&visit[i]==false)
					GraphAlgorithm.real_dfs(digraph, size, visit, res, i);
			}
			res.add(pos);
		}
	}
	
	/**
	 * @main: 单元测试方法
	 */
	public static void main(String [] args)
	{
		double INF=Double.POSITIVE_INFINITY;        // 两个结点之间若无边，则设置为正无穷
		
		// 1. 测试无向图中环存在性的判断
		System.out.println("测试无向图中环存在性的判断：");
		double data1[][] = {{0,2,4,1,INF,INF,INF},
			       {2,0,INF,3,10,INF,INF},
			       {4,INF,0,2,INF,5,INF},
			       {1,3,2,0,7,8,4},
			       {INF,10,INF,7,0,INF,6},
			       {INF,INF,5,8,INF,0,1},
			       {INF,INF,INF,4,6,1,0}};   
		int size1=7;
		
		System.out.println(GraphAlgorithm.hasCycle(data1, size1));
		
	    // 2. 测试有向图中环存在性的判断
		System.out.println("测试有向图中环存在性的判断：");
		double [][] data2= {{INF,1,INF,1,INF},      // 测试用有向图1，参见王道数据结构，p216
				   {INF,INF,1,1,INF},
				   {INF,INF,INF,INF,1},
				   {INF,INF,1,INF,1},
				   {INF,INF,INF,INF,INF}};

		double [][] data3= {{INF,3,2,INF,INF,INF},   // 测试用有向图2，参见王道数据结构，p219
				   {INF,INF,INF,2,3,INF},
				   {INF,INF,INF,4,INF,3},
				   {INF,INF,INF,INF,INF,2},
				   {INF,INF,INF,INF,INF,1},
				   {INF,INF,INF,INF,INF,INF}};
		
		double [][] data4= {{INF,1,INF,1,INF,INF,INF,INF,INF,INF},   // 测试用有向图3，参见数据结构与算法分析，p248
				            {INF,INF,1,INF,INF,1,INF,INF,INF,INF},
				            {1,INF,INF,1,1,INF,INF,INF,INF,INF},
				            {INF,INF,INF,INF,1,INF,INF,INF,INF,INF},
				            {INF,INF,INF,INF,INF,INF,INF,INF,INF,INF},
				            {INF,INF,1,INF,INF,INF,INF,INF,INF,INF},
				            {INF,INF,INF,INF,INF,1,INF,1,INF,INF},
				            {INF,INF,INF,INF,INF,1,INF,INF,INF,1},
				            {INF,INF,INF,INF,INF,INF,INF,1,INF,INF},
				            {INF,INF,INF,INF,INF,INF,INF,INF,1,INF}};
		
		double [][] data5= {{INF,1,INF},{INF,INF,1},{1,INF,INF}};     // 测试用有向图4，三角形有向有环图
		
		int size2=5;
		int size3=6;
		int size4=10;
		int size5=3;
		
		System.out.println(GraphAlgorithm.diHasCycle(data2, size2));
		System.out.println(GraphAlgorithm.diHasCycle(data3, size3));
		System.out.println(GraphAlgorithm.diHasCycle(data4, size4));
		System.out.println(GraphAlgorithm.diHasCycle(data5, size5));
		
		// 3. 测试无向图的连通性判断
		System.out.println("测试无向图中连通性的判断：");
		double [][] data6= {{INF,1,INF},{1,INF,INF},{INF,INF,INF}};      // 测试用无向图2，不连通       
		int size6=3;
		
		System.out.println(GraphAlgorithm.isConnect(data1, size1));
		System.out.println(GraphAlgorithm.isConnect(data6, size6));
		
		// 4. 测试有向图的弱连通性，单向连通性和强连通性判断
		System.out.println("测试有向图中弱连通性的判断：");
		System.out.println(GraphAlgorithm.diWeakConnect(data2, size2));
		System.out.println(GraphAlgorithm.diWeakConnect(data3, size3));
		System.out.println(GraphAlgorithm.diWeakConnect(data4, size4));
		System.out.println(GraphAlgorithm.diWeakConnect(data5, size5));
		
		System.out.println("测试有向图中单向连通性的判断：");
		System.out.println(GraphAlgorithm.diSingleConnect(data2, size2));
		System.out.println(GraphAlgorithm.diSingleConnect(data3, size3));
		System.out.println(GraphAlgorithm.diSingleConnect(data4, size4));
		System.out.println(GraphAlgorithm.diSingleConnect(data5, size5));
		
		System.out.println("测试有向图中强连通性的判断：");
		System.out.println(GraphAlgorithm.isStrongConnect(data4, size4));
		System.out.println(GraphAlgorithm.isStrongConnect(data5, size5));
		
		// 5. 计算有向图中的强连通分支
		System.out.println("计算有向图中的强连通分支：");
		System.out.println("有向图data4的强连通分支为：");
		ArrayList<ArrayList<Integer>> res=GraphAlgorithm.getStrongWeight(data4, size4);
		
		for(int i=0;i<res.size();i++)
		{
			System.out.print("强连通分支"+String.valueOf(i)+": ");
			for(int k=0;k<res.get(i).size();k++)
			{
				System.out.print(String.valueOf(res.get(i).get(k))+" ");
			}
			System.out.println("");
		}
	}
}
