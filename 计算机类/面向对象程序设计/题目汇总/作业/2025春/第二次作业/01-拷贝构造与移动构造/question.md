# 拷贝构造与移动构造

- 题组：第二次作业
- 原始页面：https://oj.cs.tsinghua.edu.cn/course/70/contest/751/problem/1

## 题目描述

有一段缺损的程序，其中缺少三个全局函数f1,f2和f3的实现。本题需要观察stdout.txt中输出结果隐含的逻辑关系，然后根据这些关系将这三个函数的返回值类型、参数类型和函数体补充至func.h中。程序的其他部分（包括main.cpp，Test.h）均不能修改，补充的答案不唯一，任意一种即可。

文件下载：[下载链接](_downloads/download_%E5%B1%95%E5%BC%80/README.md)

文件说明：main.cpp中主要是对函数f1,f2和f3的调用，部分代码如下：

```
#include <iostream>
#include "Test.h" 
#include "func.h" 

using namespace std;

int main()
{
    cout << "------entering main------" << endl;
    Test a;
    Test b;
    
    cout << "------before call f1------" << endl;
    
    cout << "f1():" << endl;
    Test A = f1(a);
    
    cout << "------after f1 return------" << endl;
......
```

stdout.txt包含程序的输出，主要反映了各类构造函数、析构函数的调用情况，部分内容如下：

```
------entering main------
Test(): this->buf @ 0x1e1550
Test(): this->buf @ 0x1e1570
------before call f1------
f1():
Test(const Test&) called. this->buf @ 0x1e1590
a.buf @ 0x1e1590
Test(Test&&) called. this->buf @ 0x1e1590
Test(Test&&) called. this->buf @ 0x1e1590
~Test(): this->buf @ 0
~Test(): this->buf @ 0
......
```

## 编译选项

g++ main.cpp -o main -lm -O2 -DONLINE_JUDGE -fno-elide-constructors -std=c++11

## 提交文件

提交一个文件 func.h，实现全局函数f1,f2和f3，要求该文件能和提供的其他文件共同编译，且输出结果中的内存申请情况应与标准输出相同（具体的内存地址可以不同）。

你应该将你的文件打包成一个zip压缩包并上传。注意：你的文件应该在压缩包的根目录下，而不是压缩包的一个子文件夹下。评测时，OJ会将提供的main.cpp贴入你的目录下进行编译并执行。

## 评分标准

OJ评分占100%。
