  # ThreadTrees: 中序线索树

  ## 1. 线索树的基本概念和定义
  线索树是基于二叉树（或者二叉搜索树）上进行改进的一种数据结构。对于普通二叉树中的结点，在左右子结点中存在空结点时，该结点的left和right字段被置为NULL，这时left和right字段的所占用的内存空间被浪费了。    
  
  因此线索树的基本定义为: 线索树规定在左子结点/右子结点为空时，将left指向当前结点在中序遍历中的前驱结点，将right指向当前结点在中序遍历中的后继结点。  
  
  根据上述定义，线索树中的结点可以定义如下：  

  ```
  struct ThreadNode
  {
      ThreadNode(int ival=0):val(ival),left(NULL),right(NULL),lflag(0),rflag(0)
      {
      }

      int val;
      ThreadNode *left;        // 指向当前结点的左子结点或者是中序遍历中的前驱结点的指针
      ThreadNode *right;       // 指向当前结点的右子结点或者是中序遍历中的后继结点的指针
      int lflag;               // 标志变量，lflag==0表示left指向左子结点，lflag==1表示left指向中序遍历中的前驱结点
      int rflag;               // 标志变量，rflag==0表示right指向右子结点，rflag==1表示right指向中序遍历中的后继结点
  };
  ```


## 2. 线索树的构建——二叉树的线索化算法
线索树一半都是基于一个已经存在的二叉树构建的，二叉树的线索化算法的主要思想为: 
> 1. 制作给定的二叉树的一个拷贝，拷贝中的结点使用上述线索树的结点定义
> 2. 中序遍历一次该拷贝，对于中序遍历过程中访问到的每一个结点执行操作：若该结点的左子结点为空，则置标志变量lflag=1，并将left指向当前结点的前驱结点；若该结点的右子结点为空，则置标志变量rflag=1，并将right指向当前结点的后继结点

将上述主要思想和二叉树的非递归中序遍历结合起来，详细的线索化步骤如下。
> 1. 创建一个临时栈，创建临时变量nowprev指向当前访问结点的前驱结点，初始化nowprev=NULL
> 2. 从根结点开始一直向左子结点方向遍历直到遇到空结点为止，将途经的结点依次加入栈中
> 3. 循环进行以下步骤直到栈为空为止: 
>> (1) 初始化结点指针now指向栈顶结点，now就是当前正在访问和处理的结点   
>> (2) 从now->right开始，一直向左子结点方向遍历直到遇到空结点为止，将途经的结点依次加入栈中  
>> (3) 正式进行线索化: 若now->left==NULL，则令left指向中序遍历的前驱结点: now->left=nowprev; now->lflag=1；若now->right==NULL，则令right指向中序遍历的后继结点（当前结点的后继结点就是当前的栈顶结点，若栈为空则设为NULL）: now->right=sta.size()?sta.top():NULL; now->rflag=1  
>> (4) 更新临时变量nowprev: nowprev=now  


## 3. 线索树的四种基本操作——getFirstNode, getNextNode, getLastNode, getPrevNode
### 3.1. 获取中序遍历首结点——getFirstNode操作

getFirstNode操作是线索树四种基本操作之一，getFirstNode操作的功能是：

+ 输入一个线索树的根结点，返回该线索树的中序遍历的首结点

实现getFirstNode操作的思想非常简单，因为一个树在中序遍历时，输出的首结点一定是整个树中最左侧的结点，因此从根结点开始一路向左子结点的方向移动到最末端的结点，返回该结点即可。

因此，getFirstNode操作的具体算法步骤简要总结为:  

+ 初始化游标指针now指向输入的线索树的根结点: now=root，接着循环向左子结点的方向移动: now=now->left，直到当前结点now没有左子结点，即now->lflag==1时退出循环，返回结点now

具体代码实现样例如下:

```
/*
 * getFirstNode: 线索树基本操作1: 获取给定的线索树中序遍历序列中的第一个结点，该操作的算法思想（见note）非常重要，务必非常熟练地理解和掌握 
 * param root: 输入的给定线索树的根结点 
 * return: 给定的线索树的中序遍历的首结点 
 * note: 给定一个线索树，其中序遍历的首结点必然是最左侧的结点，因此一直沿着左子结点的方向直到整个树最左侧的结点，返回该结点即可 
*/
ThreadNode *ThreadTree::getFirstNode(ThreadNode *root)
{
	// 1. 初始化游标指针now指向输入的线索树的根结点 
	ThreadNode *now=root;
	
	// 2. 移动游标指针now到线索树最左侧的结点: 直接从根结点开始一直向左移动到最后一个结点即可，判断最后一个结点只需根据标志变量lflag即可 
	while(now&&!now->lflag)   // lflag==1表明当前结点没有左子结点，这时当前结点就是最左侧的结点，直接退出循环并返回即可 
	{
		now=now->left;
	}
	
	return now;
}
```

### 3.2 获取中序遍历后继结点——getNextNode操作

getNextNode操作是线索树四种基本操作之一，getNextNode操作的功能是：

+ 输入一个线索树中的结点，返回输入结点在中序遍历中的后继结点

根据线索树的定义，不难看出如下事实: 

+ 如果输入结点pos的rflag字段为1，即pos->rflag==1，这时根据线索树的定义，pos->right就一定指向中序遍历的下一个结点，只要沿着pos->right就一定能到达中序遍历的后继结点，因此直接返回pos->right作为结果。
+ 如果输入结点pos的rflag字段为0，即pos->rflag==0，这时由于输入的结点pos已经访问过（隐含说明pos的左子树在pos之前也已经访问过），因此根据中序遍历的递归定义，接下来就要访问结点pos的右子树，因此中序遍历的后继结点就是输入结点pos的右子树pos->right的中序遍历首结点，因此返回getFirstNode(pos->right)作为结果。

因此，getNextNode操作的具体算法步骤简要总结为:  

+ 如果输入结点pos的rflag字段为1，即pos->rflag==1，返回pos->right作为结果
+ 如果输入结点pos的rflag字段为0，即pos->rflag==0，返回getFirstNode(root->right)作为结果

具体代码实现样例如下:

```
/*
 * getNextNode: 线索树基本操作2: 获取在中序遍历中当前结点的下一个结点，该操作的算法思想（见note）非常重要，务必非常熟练地理解和掌握 
 * param pos: 输入的线索树结点 
 * return: 给定的结点在中序遍历中的下一个结点 
 * note: 给定一个线索树中的某个结点，要获得该结点在中序遍历中的下一个结点，站在中序遍历的角度上思考，其思路非常简单：
 *       (1) 若输入结点pos的rflag==1，根据二叉线索树结点的定义，这时沿着right必定能够达到后继结点，故直接返回pos->right；
 *       (2) 若输入结点pos的rflag==0，这时当前结点存在右子树，因为当前结点pos已经输出，因此中序遍历中的后继结点是当前结点的右子树pos->right中的中序遍历首结点，故直接返回getFirstNode(pos->right) （为什么不用处理左子树？因为左子树由getFirstNode方法处理了，可以使用一个示例来附辅助理解） 
*/          
ThreadNode *ThreadTree::getNextNode(ThreadNode *pos)
{
	if(pos->rflag)	
	return pos->right;
	else
	return getFirstNode(pos->right);
}
```

### 3.3 获取中序遍历最后一个结点——getLastNode操作
getLastNode操作是线索树四种基本操作之一，getLastNode操作的功能是：

+ 输入一个线索树的根结点，返回该线索树的中序遍历的最后一个结点

实现getLastNode操作的思想非常简单，因为中序遍历的最后一个结点必定是整个二叉树中最右侧的结点，因此只需要从输入的根结点开始，一路沿着右子结点的方向移动到最末端的结点，该末端结点就是整个二叉树中最右侧的结点，直接返回该结点即可。

因此，getLastNode的具体算法步骤简要描述为: 

+ 初始化游标指针now指向输入的线索树的根结点，然后循环向右子结点的方向移动游标指针now: now=now->right，直到当前结点now没有右子结点，即now->rflag==1时退出循环，最后直接返回结点now

具体代码实现样例如下: 
```
/*
 * getLastNode: 线索树基本操作3: 获取给定的线索树中序遍历序列中的最后一个结点
 * param root: 输入的给定线索树的根结点 
 * return: 给定的线索树的中序遍历的最后一个结点
 * note: 给定一个线索树，其中序遍历的最后一个结点必然是整个线索树中最右侧的结点，因此一直沿着右子结点的方向直到整个树最右侧的结点，返回该结点即可 
*/
ThreadNode *ThreadTree::getLastNode(ThreadNode *root)
{
	ThreadNode *now=root;	
	
	while(now&&!now->rflag)
	{
		now=now->right;
	}
	
	return now;
}   
```



### 3.4 获取中序遍历的前驱结点——getPrevNode操作

getPrevNode操作是线索树四种基本操作之一，getPrevNode操作的功能是：

+ 输入一个线索树中的结点，返回输入结点在中序遍历中的前驱结点

根据线索树的定义，假设输入的结点为pos，不难看出如下事实: 

+ 当输入的结点pos的lflag字段为1，即pos->lflag==1时，这时根据线索树的定义，pos->left就指向当前结点在中序遍历中的前驱结点，因此沿着pos->left一定能访问到当前结点pos的前驱结点，故直接返回pos->left

+ 当输入的结点pos的lflag字段为0，即pos->lflag==0时，这时说明当前结点pos存在左子树，回顾一下中序遍历的定义，在访问当前结点pos之前，应当首先访问完当前结点pos的左子树，因此，当前结点pos在中序遍历中前驱结点就是左子树pos->left放入中序遍历序列中的最后一个结点（注意结合中序遍历的过程进行理解），左子树的最后一个结点可以通过getLastNode操作实现，故直接返回getLastNode(pos->left)

因此可以总结出getPrevNode操作实现的算法步骤: 

+ 如果输入结点pos的lflag字段为1，即pos->lflag==1，直接返回pos->left
+ 如果输入结点pos的rflag字段为0，即pos->lflag==0，直接返回getLastNode(root->left)

具体的代码实现如下:

```
/*
 * getPrevNode: 线索树基本操作4：获取在中序遍历中当前结点的上一个结点
 * param pos: 输入的线索树结点 
 * return: 给定的结点在中序遍历中的上一个结点 
 * note: 给定一个线索树中的某个结点，要获得该结点在中序遍历中的上一个结点，站在中序遍历的角度上思考，其思路非常简单：
 *       (1) 若输入结点pos的lflag==1，根据二叉线索树结点的定义，这时沿着left必定能够达到后继结点，故直接返回pos->left；
 *       (2) 若输入结点pos的lflag==0，这时当前结点存在左子树，因为当前结点pos已经输出，因此中序遍历中的前驱结点是当前结点的左子树pos->left中的中序遍历的最后一个结点，故直接返回getLastNode(pos->left)
*/          
ThreadNode *ThreadTree::getPrevNode(ThreadNode *pos)
{
	if(pos->lflag)	
	return pos->left;
	else
	return getLastNode(pos->left);
}
```


## 4. 线索树的中序遍历

线索树的中序遍历算法非常简单，借助于上面介绍的线索树的两种基本操作——getFirstNode和getNextNode即可实现，算法步骤简述为: 

+ 首先使用getFirstNode方法获取整个线索树中序遍历的首结点，然后不断使用getNextNode方法获取当前结点在中序遍历中的后继结点，直到遇到空结点NULL为止 

具体代码实现样例如下:

```
/* 
 * inorder: 对当前的线索树进行中序遍历，返回中序遍历结果
 * note: 本算法直接使用上述的线索树的两种基本操作进行完成，首先使用getFirstNode方法获取整个线索树中序遍历的首结点，然后不断使用getNextNode方法获取中序遍历中的后继结点，直到遇到空结点NULL为止 
*/
vector<int> ThreadTree::inorder()
{
	vector<int> res;
	
	ThreadNode *now=getFirstNode(treeroot);
	
	while(now)
	{
		res.push_back(now->val);
		now=getNextNode(now);
	}
	
	return res;
}

```

## 5. 线索树的反向中序遍历

线索树的反向中序遍历实现和中序遍历类似，只需使用线索树的getLastNode操作和getPrevNode操作即可完成，算法步骤简述为: 

+ 首先使用getLastNode方法获取整个线索树中序遍历的最后一个结点，然后不断使用getPrevNode方法获取当前结点在中序遍历中的前驱结点，直到遇到空结点NULL为止 

具体代码实现样例如下:

```
/* 
 * inverse_inorder: 对当前的线索树进行反向中序遍历
 * note: 本算法直接使用上述的线索树的两种基本操作进行完成，首先使用getLastNode方法获取整个线索树中序遍历的最后一个结点，然后不断使用getPrevNode方法获取中序遍历中的前驱结点，直到遇到空结点NULL为止
*/
vector<int> ThreadTree::inverse_inorder()  
{
	vector<int> res;
	
	ThreadNode *now=getLastNode(treeroot);
	
	while(now)
	{
		res.push_back(now->val);
		now=getPrevNode(now);
	}
	
	return res;
}
```


## 6. 线索树的析构

线索树的析构算法既可以使用普通二叉树的析构方法，也可以利用线索树的特殊性质，借助于上面介绍的线索树的两种基本操作——getFirstNode和getNextNode即可实现，算法步骤简述为:

+ 首先使用getFirstNode方法获取整个线索树中序遍历的首结点，释放当前结点，然后使用getNextNode方法获取中序遍历中的后继结点，直到遇到空结点NULL为止

具体代码实现样例如下:
```
/*
 * ~ThreadTree: 析构函数 
 * note: 同样可以按照中序遍历的顺序来进行析构，使用getFirstNode和getNextNode两个方法进行遍历的同时进行删除即可 
*/
ThreadTree::~ThreadTree()
{
	ThreadNode *now=getFirstNode(treeroot);
	
	while(now)
	{
		ThreadNode *temp=now;
		now=getNextNode(now);
		delete now;
	} 
}
```

