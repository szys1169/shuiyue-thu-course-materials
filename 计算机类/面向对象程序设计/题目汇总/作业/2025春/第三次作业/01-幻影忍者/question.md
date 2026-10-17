# 幻影忍者

- 题组：第三次作业
- 原始页面：https://oj.cs.tsinghua.edu.cn/course/70/contest/777/problem/1

## 题目描述

幻影忍者们在吴大师的忍者训练场中练习多年，已经掌握了基础的忍者武术，但是为了应对复杂多样的危机，吴大师需要派出特定的忍者、携带特定的武器或坐骑来接受擂台训练，使用自身忍者技能，你需要实现不同的忍者类，并且记录他们的挑战。

已有 Dragon 、Weapon 两个类的源文件，分别记录忍者的元素龙、武器，你需要编写以下几个类的具体程序：

Ninja：忍者基类。每个忍者包含一个 Dragon 和一个 Weapon 对象。你需要实现其中的 describe 方法输出其名称描述。

Fire_Ninja：火焰忍者类，需通过继承 Ninja 类实现。同时能够使用火焰元素力量。你需要实现其中的 describe 方法以及 fire_power 方法，分别输出其名称描述及专属能力描述。

Ice_Ninja：寒冰忍者类，需通过继承 Ninja 类实现。同时能够使用寒冰元素力量。你需要实现其中的 describe 方法以及 ice_power 方法，分别输出其名称描述及专属能力描述。

## 输入样例

第一行包括一个正整数n，表示对战的局数。

接下来 *n* 行，每一行有一个整数 *a* 和两个字符串 *b*、*c* ，一个整数 *d* 和两个字符串 *e*、*f* 组成 。

*a* 表示守擂忍者的类别，0 为 Ninja，1 为 Fire_Ninja，2 为 Ice_Ninja。

*b* 代表守擂忍者元素龙的名称，*c* 代表守擂忍者武器的名称。

*d* 表示攻擂忍者的类别，0 为 Ninja，1 为 Fire_Ninja，2 为 Ice_Ninja。

*e* 代表攻擂忍者元素龙的名称，*f*  代表攻擂忍者武器的名称。

```
3
0 Dragon Fist 1 Fighting_Dragon Fire_Sword
1 Fighting_Dragon Fire_Sword 2 Lucky_Dragon Ice_Heart
2 Lucky_Dragon Ice_Heart 0 Dragon Fist
```

## 输出样例

按照输入顺序，依次输出每场对局的出战忍者。

第一行输出使用的元素龙名称。

第二行输出使用的武器名称。

第三行输出不同忍者、元素龙、武器的组合。

第四行通过 describe 方法输出名称描述，注意名称的区别。

对于不同的 Ninja 类来说，第五行可能通过调用 fire_power 或 ice_power 方法输出固定字符串`I will burn the night!`或者`You will be the dust of frozen bones!`，描述忍者的专属能力。

```
##Round 1, Ninja is coming!
Driving Dragon dragon.
Using Fist weapon.
Ninja is coming!
Ninja is with Dragon and Fist.
Driving Fighting_Dragon dragon.
Using Fire_Sword weapon.
Fire ninja is coming!
Fire ninja is with Fighting_Dragon and Fire_Sword.
I will burn the night!
##Round 2, Ninja is coming!
Driving Fighting_Dragon dragon.
Using Fire_Sword weapon.
Fire ninja is coming!
Fire ninja is with Fighting_Dragon and Fire_Sword.
I will burn the night!
Driving Lucky_Dragon dragon.
Using Ice_Heart weapon.
Ice ninja is coming!
Ice ninja is with Lucky_Dragon and Ice_Heart.
You will be the dust of frozen bones!
##Round 3, Ninja is coming!
Driving Lucky_Dragon dragon.
Using Ice_Heart weapon.
Ice ninja is coming!
Ice ninja is with Lucky_Dragon and Ice_Heart.
You will be the dust of frozen bones!
Driving Dragon dragon.
Using Fist weapon.
Ninja is coming!
Ninja is with Dragon and Fist.
```

## 限制与约定

2 ≤ *n* ≤ 200

0 ≤ *a* ≤ 2

*b*、*c* 的长度不超过 2000

## 提交格式

1. 给定 `main.cpp`、`weapon.h`、`weapon.cpp`、`dragon.h`、`dragon.cpp`，内容见：[下载链接](_downloads/download_%E5%B1%95%E5%BC%80/README.md)。
2. 你需要提交 `ninja.h/cpp`, `fire_ninja.h/cpp`, `ice_ninja.h/cpp` 以及Makefile文件。使用的Makefile必须要能生成可执行文件main（不带扩展名）。

**请将你的文件打包成一个 zip 格式的压缩包并上传。注意：你的文件应该在压缩包的根目录下，而不是压缩包的一个子文件夹下，换而言之，解压你提交的压缩包后，应该直接得到一系列 cpp 文件、h 文件等代码文件，而不是一个包含它们的文件夹。评测时，OJ会将提供的文件贴入你的目录下进行编译并执行。**
