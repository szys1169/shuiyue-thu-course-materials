# XOR

- 题组：第六次作业
- 原始页面：https://oj.cs.tsinghua.edu.cn/course/70/contest/825/problem/1

## 题目描述

你在玩一个魔法卡牌游戏，每张卡牌有一个名字以及一个数字。卡牌的类 `Card` 已经在 `card.h` 中定义。

刚开始你的身前没有任何牌堆。你需要在 `cards.h` 中实现牌堆类 `Cards`，实现如下成员函数以完成以下几种操作：

- 创建一个新的空牌堆。具体地，程序会调用 `Cards()` 构造函数；
- 根据给定vector `vec` 创建一个新牌堆。具体地，程序会调用 `Cards(string name, vector<int> vec)` 构造函数，牌堆中每张牌的名字均设置为 `name`，而卡牌的数字从上到下分别设置为 `vec` 中的各个元素；
- 在牌堆顶放上一张牌。具体地，程序会调用 `put(Card card)`，将 `card` 放到牌堆的顶部；
- 输出牌堆内容。具体地，程序会调用 `print()` 函数，从上到下输出每张卡牌的名字和数字，若牌堆为空则输出 `empty`，具体输出格式可查看样例；
- 统计牌堆中牌的数量。具体地，程序会调用 `count()` 函数，返回该牌堆中牌的数量；
- 合并两个牌堆。具体地，程序会调用 `merge(Cards &other)` 函数，把 `other` 牌堆放到本牌堆放到之下，若两牌堆均非空，则本牌堆最下方的卡牌数字会神奇地异或上 `other` 牌堆最上方的卡牌数字，操作后 `other` 牌堆应为空。
- 本题对程序的运行效率没有严格的要求，但仍推荐借助 C++ 的 `std::list` 实现，利用好其中的 `splice` 函数可能会事半功倍。参考资料：

- [https://zh.cppreference.com/w/cpp/container/list](https://zh.cppreference.com/w/cpp/container/list)

## 题目要求

给定 `main.cpp`、`card.h`、`Makefile`，内容见[下载链接](_downloads/download_%E5%B1%95%E5%BC%80/README.md) (注意 `main.cpp` 可能不是最终测试所使用的 `main.cpp` )。完成 `cards` 类，包含以下方法：

- `Cards()`：创建一个新的空牌堆。
- `Cards(string name, vector<int> vec)`：根据给定vector `vec` 创建一个新牌堆。
- `put`：在牌堆顶放上一张牌。
- `print`：输出牌堆内容。
- `count`：统计牌堆中牌的数量。
- `merge`：合并两个牌堆。

## 样例输入

见下发的 `main.cpp`。

## 样例输出

```
3
(three 4) (three 0)
5
empty
(zero 7)
(two 6) (two 3) (two 12) (three 4) (three 6) (zero 6) (four 1) (four 5) (four 5)
```

## 提交格式

1. 不修改 `main.cpp`、`card.h`、`Makefile`。在实际测试时，我们会将`main.cpp`替换为另外的测试程序。
2. 你仅需要提交 `cards.h`。

**请将你的文件打包成一个 zip 格式的压缩包并上传。注意：你的文件应该在压缩包的根目录下，而不是压缩包的一个子文件夹下，换而言之，解压你提交的压缩包后，应该直接得到一系列 cpp 文件、h 文件等代码文件，而不是一个包含它们的文件夹。评测时，OJ会将提供的文件贴入你的目录下进行编译并执行。**
