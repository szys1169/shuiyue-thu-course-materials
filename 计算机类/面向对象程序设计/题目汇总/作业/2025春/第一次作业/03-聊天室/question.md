# 聊天室

- 题组：第一次作业
- 原始页面：https://oj.cs.tsinghua.edu.cn/course/70/contest/731/problem/3

## 题目描述

小明喜欢和别人聊天，请你帮他实现一个简单的聊天室吧。

你需要实现两个类`ChatUser`和`ChatSession`。其中，`ChatUser`为聊天室的单个用户类，需要包含用户的名称，好友列表（好友列表是单向的，即A添加B后，B出现在A的好友列表中，但A不出现在B的好友列表中），收到的消息列表。而`ChatSession`类需要包含一个动态的`ChatUser*`数组来表示聊天室中的成员。

`ChatUser`需要实现如下功能：

- 添加好友。
- 删除好友。
- 向某位用户发送消息。
- 接受来自某个用户的消息。
- 打印当前收到的所有消息。
- 打印好友列表。

`ChatSession`需要实现如下功能：

- 将一个用户添加到聊天室中。
- 将一个用户从聊天室中删除。
- 在当前聊天室按照用户名查找用户。

## 题目要求

给定`main.cpp`、`ChatUser.h`、`ChatSession.h`，内容见[下载链接](_downloads/oop_2025_hw1_t4_%E5%B1%95%E5%BC%80/README.md)。完成如下要求：

1. 完成 `ChatUser` 类，包含以下方法：- `addFriend`：向自己的好友列表中添加某个用户，并且输出提示信息。
- `removeFriend`：从自己的好友列表中删除某个用户，并且输出提示信息。
- `sendMessage`：向某个用户发送一条消息，并且输出提示信息。
- `receiveMessage`：接受来自某个用户的一条消息，并且输出提示信息。
- `showMessage`：打印用户当前收到的所有消息。按发送消息的用户分类打印，按发送第一条消息的时间先后确定各用户发送的消息的打印顺序。
- `showFriends`：打印用户的好友列表。
2. 完成 `ChatSession` 类，包含以下方法：- `addUser`：将用户添加到聊天室中，并且输出提示信息。
- `removeUser`：将用户从聊天室中删除，并且输出提示信息。
- `getUserByName`：在当前聊天室按照用户名查找用户，查找失败时输出提示信息。

## 输入输出格式

输入的第一行包含一个正整数n，表示用户的数量；

接下来输入n行，每行输入一个字符串name，表示每个用户的名称；

接下来输入一个正整数m，表示操作数量；

接下来输入m行，每行先输入一个正整数op，来表示操作类型：

- op=0: 添加好友操作，再输入两个字符串A和B，表示将名称为B的用户加入名称为A的用户的好友列表；
- op=1: 删除好友操作，再输入两个字符串A和B，表示将名称为B的用户移出名称为A的用户的好友列表；
- op=2: 发送消息操作，再输入三个字符串A，B和message，表示名称为A的用户向名称为B的用户发送消息message；
- op=3: 查看消息操作，再输入一个字符串A，表示查看名称为A的用户收到的消息；
- op=4: 移除成员操作，再输入一个字符串A，表示从聊天室中移出名称为A的用户；
- op=5: 查看好友操作，再输入一个字符串A，表示查看名称为A的用户的好友列表。

如果与某一操作相关的任何一个用户A不在当前聊天室中，该操作不应产生任何实际效果，且应该打印提示信息："A not in chat"。
A向B发消息时，如果A和B都不存在，也只打印："A not in chat"。

具体提示信息输出格式参考样例。

## 数据规模与约定

保证所有输入均合法，并且2≤n≤102\leq n \leq 102≤n≤10，10≤m≤10010 \leq m \leq 10010≤m≤100。

## 输入示例

```
3
A
B
C
18
0 A B
0 A C
0 A B
5 A
1 A B
1 A B
5 B
2 A B Hello World!
2 C B Hello, I'm C.
3 B
4 B
0 A B
1 A B
2 B A Hello A!
2 A B Hello B!
3 B
4 B
5 B
```

## 输出示例

```
Add user: A // 将用户加入会话
Add user: B
Add user: C
A -> add friend -> B // A添加B为好友
A -> add friend -> C
A and B are already friends // B已经是A的好友
A's friend: B C
A -> remove friend -> B // A在好友列表中删除B
A and B are not yet friends // B已经不是A的好友
B's friend: // B好友列表为空
A -> send message -> B : Hello World!
B -> receive message -> A : Hello World!
C -> send message -> B : Hello, I'm C.
B -> receive message -> C : Hello, I'm C.
Chat B: // 由于A先向B发送的消息，故查看消息列表时，A发送的消息排在C的前面。对于所有A发送的消息，按发送时间先后顺序打印
>> From A:
>> Hello World!
>> From C:
>> Hello, I'm C.
Remove user: B // 将B移出聊天室后，后续与B相关的所有的操作均失效，并打印B not in chat
B not in chat
B not in chat
B not in chat
B not in chat
B not in chat
B not in chat
B not in chat
```

## 提交格式

1. 不修改 `main.cpp`、`ChatUser.h`、`ChatSession.h`。
2. 你需要提交 `ChatUser.cpp`, `ChatSession.cpp`以及Makefile文件。使用的Makefile必须要能生成可执行文件main（不带扩展名）。

**请将你的文件打包成一个 zip 格式的压缩包并上传。注意：你的文件应该在压缩包的根目录下，而不是压缩包的一个子文件夹下，换而言之，解压你提交的压缩包后，应该直接得到一系列 cpp 文件、h 文件等代码文件，而不是一个包含它们的文件夹。评测时，OJ会将提供的文件贴入你的目录下进行编译并执行。**
