# 军队集结

- 题组：第五次作业
- 原始页面：https://oj.cs.tsinghua.edu.cn/course/70/contest/803/problem/3

### 题目描述

艾泽拉斯大陆上生活着人族和兽族两个种族，现在存在着四种单位：人族步兵，人族指挥官，兽族步兵，兽族指挥官。每名步兵最多受到一名同族指挥官的指挥。

目前，我们已经编写了步兵基类Footman、指挥官基类Commander、指挥关系基类Belong，还有AbstractFactory和Game类。

现在我们需要用一种模式方法来建立军队，能方便添加新的兵种类型和新的种族类型。

你需要观察已有的文件（主要是`main.cpp`中的`test`函数），补全兵营基类Casern(`Casern.h`)，各种子类(`YourCasern.h`、`YourFactory.h`)，其中`//TODO`处为代码填写部分，使得输出正确。

你只能修改`Casern.h`、`YourCasern.h`和`YourFactory.h`，其他修改均无效。

文件下载：[下载链接](_downloads/download_%E5%B1%95%E5%BC%80/README.md)

提示:

```
dynamic_cast <type-id> (expression)
```

该运算符把expression转换成type-id类型的对象。如果 downcast 是安全的（也就说，如果基类指针或者引用确实指向一个派生类对象）这个运算符会传回适当转型过的指针。如果 downcast 不安全，这个运算符会传回空指针。

### 输入格式

无输入

### 正确输出

```
test1 ok!
test2 ok!
```

## 提交文件

提交一个zip文件，包含`Casern.h`、`YourCasern.h`和`YourFactory.h`文件。注意直接打包文件，不要包含文件夹。

你只能修改`Casern.h`、`YourCasern.h`和`YourFactory.h`，其他修改均无效。

我们会将你提交的文件和我们预先设置好的文件一起编译运行。

## 评分标准

我们会有1个样例测试点，即下发给各位的程序。另外有3个隐藏测试点，会相应的更改`main.cpp`与`Game.cpp`中内容进行测试，一般来说，如果你能正确实现通过样例测试点，也应该能够通过隐藏测试点。

考试100%为OJ评分。
