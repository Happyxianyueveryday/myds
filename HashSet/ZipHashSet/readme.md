# ZipHashSet: 拉链法哈希集合

## 1. 代码文件
```
· HashElement.h: 哈希表元素抽象基类，需要加入哈希表的元素继承该基类并重写其中的方法
· TestElement.h: 继承HashElement抽象基类，本处测试中使用的哈希表元素类
· HashSet.h: 哈希集合抽象基类
·ZipHashSet.h: 继承HashSet.h，使用拉链法实现的哈希集合类
```

## 2. 更新日志
#### (1). 增加哈希扩容算法，哈希扩容算法遵守和java标准容器一致的扩容规则。
```
扩容算法详解：
1. 何时进行扩容？

2. 如何进行扩容？
```

#### (2). 增加移动拷贝构造函数和移动赋值运算符。
```
关于移动拷贝构造函数和移动赋值运算符可以参见我的另外一篇总结文章：https://github.com/Happyxianyueveryday/cppnote/tree/master/4.%20%E5%8F%B3%E5%80%BC%E5%BC%95%E7%94%A8%E4%B8%8E%E7%A7%BB%E5%8A%A8%E8%AF%AD%E4%B9%89
```
