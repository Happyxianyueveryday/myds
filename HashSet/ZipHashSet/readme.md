## ZipHashSet: 拉链法哈希集合

## 1. 代码文件
```
· HashElement.h: 哈希表元素抽象基类，需要加入哈希表的元素继承该基类并重写其中的方法
· TestElement.h: 继承HashElement抽象基类，本处测试中使用的哈希表元素类
· HashSet.h: 哈希集合抽象基类
· ZipHashSet.h: 继承HashSet.h，使用拉链法实现的哈希集合类
```

## 2. 拉链法哈希表的哈希扩容算法
此版本的拉链法哈希表实现中参照的是java 1.7版本的哈希表。具体介绍哈希扩容算法之前，首先介绍以下几个基本概念.

+ 元素数量size: 哈希表中的元素个数。
+ 桶数量capacity: 拉链法哈希表中桶的数量，或者说是桶数组的长度。
+ 负载因子load_factor: 拉链法哈希表的装载因子，范围为\(0, 1]。
+ 阈值threshold: 阈值等于桶数量乘以装载因子，即threshold=capacity\*load_factor。

然后，哈希扩容的核心触发条件为：

+ 当哈希表中的元素数量size大于阈值threshold时，也即: size>capacity\*load_factor时，触发哈希扩容。

具体的哈希扩容过程为：
(1) 新建
(2) 
(3) 
