# 分数运算

- 题组：第二次作业
- 原始页面：https://oj.cs.tsinghua.edu.cn/course/70/contest/751/problem/2

## 题目描述

给定两个非负的分数 A=A1A2A=\frac{A_1}{A_2}A=A2​A1​​ 和 B=B1B2B=\frac{B_1}{B_2}B=B2​B1​​，你需要求出 A+BA+BA+B、ABABAB、AB\frac{A}{B}BA​ ，并且判断这两个分数的大小。

对于输出的分数，需要化为最简形式，即输出分数的分子与分母最大公因数为 111。特别地，如果该分数为 000，输出 `0/1`；如果是一个不合法的分数（即除以 000 得到的分数），输出 `nan`。

你需要实现的是`Factor.h`和`Factor.cpp`。`main.cpp`已经给定了：

```
//main.cpp
#include "Factor.h"
#include <iostream>

int main()
{
    using namespace std;
    Factor A, B;
    cin >> A;
    cin >> B;
    cout << A + B << endl;
    cout << A * B << endl;
    cout << A / B << endl;
    if (A < B)
        cout << "smaller" << endl;
    if (A > B)
        cout << "bigger" << endl;
    if (A == B)
        cout << "equal" << endl; 
    return 0;
}
```

编译命令是`g++ -std=c++11 Factor.cpp main.cpp -o main`。

## 输入格式

第一行一个非负分数 AAA，格式为A1/A2A_1\text{/}A_2A1​/A2​。

第二行一个非负分数 BBB，格式为B1/B2B_1\text{/}B_2B1​/B2​。

这里保证 0≤A1,B1≤1040\leq A_1,B_1\leq 10^40≤A1​,B1​≤104，1≤A2,B2≤1041\leq A_2,B_2\leq 10^41≤A2​,B2​≤104，且均为整数。

## 输出格式

第一行输出两个分数的和。

第二行输出两个分数的积。

第三行输出 AB\frac{A}{B}BA​ 的结果。

第四行，如果 A>BA>BA>B 输出 `bigger`，如果 A<BA<BA<B 输出 `smaller`，如果 A=BA=BA=B 输出 `equal`。

以上输出分数的格式，如果不是不合法的分数，也为 `A/B`。

## 输入样例

```
1/8
3/8
```

## 输出样例

```
1/2
3/64
1/3
smaller
```

## 要求

`main.cpp`可以在[这里](./main.cpp)下载。

你需要提交`Factor.h`和`Factor.cpp`，请将你的文件打包成一个zip压缩包并上传。你不需要提交`main.cpp`和`Makefile`。评测时，OJ会将提供的`main.cpp`贴入你的目录下进行编译并执行。

## 评分标准

OJ自动评测占100%。
