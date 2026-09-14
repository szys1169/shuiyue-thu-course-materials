<!-- 来源：https://dsa.cs.tsinghua.edu.cn/oj/problem.shtml?id=9512 -->

# CST 2-1-1 Queues

---

### **题目背景**

各种软件系统都往往需要在数据库中维护大量的队列，比如在选课系统中，每门课程都需要一个候补队列；在 12306 售票系统中，对每趟列车都需要一个候补队列。维护这些数据需要面临存储空间优化、IO 效率、数据灾备等各种问题。我们从这些场景中抽象出一个高度简化的“队列维护问题”，希望你在这个简单场景下编写的程序能满足一些简单的时间、内存限制。

为避免输入和输出效率对时间、内存占用的影响，这里采用交互形式，提供一个交互库，你只需要按要求实现一个类。

### **题目描述**

你需要在给出的实验框架中实现一个 `QueueManager` 类，对外提供如下操作接口：

- `QueueManager(unsigned int m)`： 创建 mm 个空队列，从 11 至 mm 依次编号；队列内的元素从 11 开始自前向后编号。
- `QueueManager.push(unsigned int k,unsigned int x)`： 在第 kk 个队列末尾插入 xx，1≤k≤m,x≥11 \le k \le m, x \ge 1。
- `QueueManager.pop(unsigned int k)`： 删除第 kk 个队列首元素。如果队列为空，则什么都不做。1≤k≤m1 \le k \le m。
- `QueueManager.query(unsigned int k, unsigned int i)`： 返回第 kk 个队列中的第 ii 个元素，1≤k≤m,i≥11 \le k \le m, i \ge 1。 若队列长度不足 ii，则返回队尾元素。若队列为空，则返回 0。

### **实验框架与提交说明**

请从这里下载实验框架：[framework.zip](../附件/d3527e043eeb54451ee3a9a769235ff06f328a5e.zip)，内含 `main.cpp`，`manyqueue.h`，`manyqueue.cpp`，`readme.txt`。`main.cpp` 保持不变，只能修改 `manyqueue.h` 和 `manyqueue.cpp` 以实现 `main.cpp` 所需求的功能。

命令行环境下可以用以 `g++ main.cpp manyqueue.cpp -o main` 方式编译。使用 IDE 则需要配置一个项目，包含全部源代码文件。

`QueueManager` 类的 API 已经在 `QueueManager.h` 中提供，你需要在 `QueueManager.cpp` 中, 给出 `QueueManager` API 的具体实现。

可以在 `QueueManager.h` 中为 `QueueManager` 类添加新的成员变量、成员函数，也可以定义新的类，但不得修改 `QueueManager` 原有的 API（包括函数名称、参数类型），否则会导致编译错误。

提交之前，须将 `manyqueue.cpp` 和 `manyqueue.h` 压缩为 zip文件。不必提交 `main.cpp`，即使提交了也会被统一的版本覆盖。

### **输入格式**

在本地调试阶段，你可以按照上述方式编译实验框架，然后按照下面的格式输入：

- 第一行仅有一个正整数 nn，n≤5×106n \le 5 \times 10^{6}，表示接下来将依次执行 nn 次操作；
- 第二行也仅有一个正整数 mm， m≤104m \le 10^{4}，表示共有 mm 个队列；
- 接下来的 nn 行，将依次指定一次操作。有三种可能，分别对应于此前约定的三个接口：  `push k x` `pop k` `query k i`  行首的函数名是字符串，kk、xx 和 ii 是对应的整数参数，其间都用一个空格相隔。

### **输出格式**

实验框架对每次 query 操作会输出一行查询结果，而其他操作则没有输出。你可以自己添加一些调试输出。

### **输入样例**

```
20
3
push 2 1211887465
push 2 978065099
push 3 553217709
pop 2
push 2 1098264680
push 2 830700501
pop 3
pop 1
push 2 196680741
push 1 2016887377
push 1 706909629
push 2 2111655898
pop 1
query 2 7
query 3 1
push 3 1775356439
push 3 218231269
query 1 1
push 3 699598561
query 3 3
```

### **输出样例**

```
2111655898
0
706909629
699598561
```

该样例即是 OJ 上的第一个测试点，请特别留意其中查询超过队尾、查询空队列等特殊情况。

### **数据范围**

mm 不超过 10410^4，操作次数 nn 不超出 5×1065 \times 10^6 。

任意时刻，所有队列的总长度均不超过 5×1055 \times 10^5。

kk，ii，xx 均不超过 `unsigned int` 范围。1≤k≤m,x≥1,i≥11 \le k \le m, x \ge 1, i \ge 1。

### **资源限制**

时间限制：2.5 s

内存限制：32 MB

注意，内存限制是对整个程序的限制，由于种种原因你实际能够使用的内存空间可能没有 32 MB。

### **提示**

- 尽量使所有队列所占用的内存空间，不超过队列中所有元素所占用内存空间的 44 倍。
- 使用向量来实现队列，并通过动态扩容、缩容以满足内存限制。
- “循环”利用向量中的内存空间，使每个队列实际的内存占用和元素的数目一致。
- 也可考虑适时地搬迁队列中的元素，以在均摊意义上满足时间、内存限制。
