# Makefile与四则运算

- 题组：第一次作业
- 原始页面：https://oj.cs.tsinghua.edu.cn/course/70/contest/731/problem/1

### 题目描述

现在已有sum.cpp、minus.cpp、product.cpp、divide.cpp、functions.h五个文件。

文件内容见[下载链接](_downloads/download_%E5%B1%95%E5%BC%80/README.md)

你需要编写一个Makefile和一个main.cpp文件完成程序的编译和执行过程，要求：

- 在linux系统下，Makefile文件能正常运行且编译成功，生成名为main的可执行文件（以下可执行文件名始终不变），编译器为g++。
- 使用make命令，能够联合编译多个源文件，最后运行main可执行文件，接收两个整数输入，并输出二者之和（详见后文样例）。
- 使用make debug命令，能够联合编译多个源文件，最后运行main可执行文件，接收两个整数输入，并输出调试信息和二者之和。
- 使用make minus / make product / make divide命令，能够联合编译多个源文件，最后运行main可执行文件，接收两个整数输入，先输出二者之和，再分别输出二者之差 / 乘积 / 商（整除）。
- 使用make clean命令，能够清理之前生成的文件，还原成最初的样子。

提示：你可能会用到 g++/gcc 的一些[编译选项](https://gcc.gnu.org/onlinedocs/gcc/Preprocessor-Options.html)。在sum.cpp等文件中，给了一个DEBUG编译选项的范例，在你编写main.cpp的过程中可以参考。

**注意：你Makefile文件在结束任务后必须返回0。若返回非0值，则认为make失败，评测系统会给出Make Error的提示。**

**提示：OJ 有时会报 No Source，实际上就是编译不通过。**

### make输入样例

```
4 3
```

### make输出样例

```
7
```

### make debug输入样例

```
4 3
```

### make debug输出样例

```
running sum(a = 4, b = 3)
7
```

### make divide输入样例

```
4 3
```

### make divide输出样例

```
7
1
```

### 提交要求

编写Makefile和main.cpp文件，压缩为一个zip文件并提交，满足上述需求。

**注意：你的压缩包里只能包含上述2个文件，多余的文件会被 OJ 移除。**

### 评分标准

OJ自动评测占100%。
