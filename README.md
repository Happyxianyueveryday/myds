# myds

### 1. 介绍

基本数据结构的手写实现。

第二次的实现相对于第一次的主要关注点在于各种数据结构的良好组织上，并且修复了一些存在的问题。

本项目中的数据结构组织和关系如下（随时间更新）：

### 2. 目录（随时间更新）

...表示已完成但是待测试，√表示已经完成和测试。

```
cpp特性部分：
root/
  SmartPointer/ -- 智能指针
    shared_ptr -- 共享对象所有权的智能指针 √
    unique_ptr -- 独享对象所有权的智能指针 √
    weak_ptr -- 无对象所有权的弱指针（同时包含shared_ptr的标准实现版本） √

数据结构部分：
root/ 
  List/ -- 链表抽象类 √
    StaticList -- 静态链表 √
    LinkedList -- 链表 √
  Stack/ -- 栈抽象类 √
    ArrayStack -- 数组栈 √ 
    LinkedStack -- 链表栈 √
  Queue/ -- 队列抽象类 √ 
    ArrayQueue -- 数组队列 √
    LinkedQueue -- 链表队列 √
  Tree/ -- 树 √
    BinaryTree/ -- 二叉树 √
      BSTree -- 二叉搜索树 √
      ThreadedTree/  -- 线索树抽象类 √
        PreThreadedTree -- 前序线索树 √
        InThreadedTree -- 中序线索树 √
        PostThreadedTree -- 后序线索树 √
      HuffmanTree -- 哈夫曼树  √
    MultiTree -- 多叉树  √
  Sort -- 排序 √
  Search --查找 √
  Graph/ -- 图抽象类 √
    DiGraph/ -- 有向图 √
      DAG --有向无环图 √
    NdGraph -- 无向图 √
  HashSet/ -- 哈希表 √
    ArrayHashSet -- 基于开放定址法的哈希表 √
    ZipHashSet -- 基于拉链法的哈希表 √
  Heap -- 堆（优先队列）√
```
