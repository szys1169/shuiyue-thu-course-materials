# 简单的软件工程团队

- 题组：2025OOP期末考试（任老师班）补交
- 原始页面：https://oj.cs.tsinghua.edu.cn/course/70/contest/729/problem/0

# 题目说明

[English Version](./english.pdf)

软件的开发，往往离不开团队的分工协作。在开发团队里，存在着形形色色的岗位，如前端、后端、测试员、产品经理等等，他们各有职责，互相密切合作、频繁交流，方才能成就一个个大工程。

在本题中，我们要利用OOP的知识，模拟一个极其简单的软件开发团队，主要包含两种角色：程序员`Coder`和测试员`Tester`，二者分别作为一个类，且均继承自基类`Agent`。现在，我们已经帮大家实现好了`main.cpp`、`Makefile`、`agent.h`（包含`Agent`基类的声明和大部分接口的定义），它们可以从[这里](_downloads/agent_%E5%B1%95%E5%BC%80/README.md)下载。需要大家继续编写一下三个文件：

`agent.cpp`: 在这个文件里，你需要完成`agent.h`所未定义好的接口，即`static Agent::Agent* create_agent(int agent_type, int id, string& codes)`。其中`agent_type`为0-1整数，代表即将创建的agent类别，0为程序员，1为测试员；`id`为agent的编号；`codes`是一个字符串的引用，在本题中，**所有agent的`codes`均指向同一字符串，即团队共同编写的代码字符串**。

`coder.h`: 在这个文件里，你需要完成`Coder`类及其接口的声明和定义：

- `Coder` 构造所需信息与基类 `Agent` 一致，即 `int id` 与 `string& codes`，分别为agent编号、所有agent共同编写的代码字符串的引用；
- `Coder` 的 `action` 接口，应从标准输入中接受一串代码（本题中用无空格的英文字符串替代），并将其添加到`string& codes`所指的字符串最后；
- `Coder` 的 `report` 接口，应输出字符串 `Coder {agent_id}: {char_coded} characters coded`，`{agent_id}`和`{char_coded}`分别为agent的编号、当前程序员在其历史上所有`action`接口调用中，所“编写”代码的字符数总和。

`tester.h`: 在这个文件里，你需要完成`Tester`类及其接口的声明和定义：

- `Tester` 构造所需信息，除基类 `Agent` 已有的两个外，还应包含一个字符 `char marker` 与一个0-1整数 `int flag`，此二者均为执行测试所需信息；
- `Tester` 的 `action` 接口，将执行测试，具体过程，是计算当前代码 `string& codes` 中包含多少个 `marker` 字符，若字符数的奇偶性与 `flag` 相同，则通过测试，反之不通过；
- `Tester` 的 `report` 接口，应输出字符串 `Tester {agent_id}: {test_passed} tests passed`，`{agent_id}`和`{test_passed}`分别为agent的编号、当前测试员在`action`接口中测试通过的次数。

# 输入格式

第一行为两个整数 `n`, `m`

接下来的 `n` 行，每行以一个整数开头，分为两种情况：

- 若该行开头的整数为 0，则创建一个程序员，且该行将没有其他信息
- 若该行开头的整数为 1，则创建一个测试员，且该行将还有两个输入，即字符`marker`和0-1整数`flag`

接下来的 `m` 行，每行以两个整数开头，第一个整数为`agent_id`，第二个整数为0或1：

- 若第二个整数为 0，则执行编号为`agent_id`的agent的`action`接口，在此基础上，若该agent还是一位程序员，则该行还会有一个字符串输入，作为程序员在本次操作中“编写”的程序
- 若第二个整数为 1，则执行编号为`agent_id`的agent的`report`接口，进行输出

# 输出格式

即各agent的`report`接口输出，每条信息占一行

# 数据规模

1≤n≤1001\leq n \leq 1001≤n≤100，1≤m≤10001\leq m \leq 10001≤m≤1000

在程序员的`action`操作中，所“编写”的程序字符串，为一个长度不超过10的小写英文字母串

# 输入输出样例

输入（[链接](./0.in)）和输出（[链接](./0.out)）

# 提交格式

- 你需要提交三个文件，包含 `agent.cpp`、`coder.h`、`tester.h`
- 你应该将你的文件打包成一个 zip 压缩包并上传。注意：你的文件应该在压缩包的根目录下，而不是压缩包的一个子文件夹下；评测时，OJ 会将提供的 `main.cpp`、`Makefile`、`agent.h` 贴入你的目录下进行编译并执行
