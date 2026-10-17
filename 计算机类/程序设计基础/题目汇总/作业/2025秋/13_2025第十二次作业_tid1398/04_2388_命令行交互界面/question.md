# 命令行交互界面

> 本文件由同目录的 `题面.txt` 自动整理生成。原始文本和附件均未修改。

| 限制 | 内容 |
|---|---|
| 时间限制 | 未注明 |
| 内存限制 | 未注明 |

## 题目描述

小A准备开发一个命令行交互界面。交互界面会提示用户当前可行的操作项，由用户选择其中一个进行。选择后，用户又会得到新的提示项。比如，对于校园卡自助管理程序，用户完成登录后，会得到以下提示：[1] 余额查询[2] 卡片充值[3] 小钱包充值用户输入 “2” 后，程序又会显示：[1] 银行卡充值[2] 支付宝充值[#] 返回上一级诸如此类。小A发现，这个需求在大多数程序中都存在。因此，小A决定把这一部分变成一个通用的模块。该模块可以从文件中读取菜单配置，从而可以通过更改配置文件，完成不同的程序菜单显示需求。请你帮助小A完成这个程序。

## 输入描述

从config.txt读入。第一行一个整数n。接下来会有n行，每行表示一个配置项。每行配置项前有一个或多个#号，表示其层级关系。一个#表示顶级菜单，##表示二级菜单。随后为一个字符串x，表示菜单内容（x不包含空白符，长度<100）配置项根据其顺序关系，定义其所属的层级关系。同一级菜单选项按顺序从上到下编号为1~9。（具体可根据样例进行推理）文件最后一行，会输入一个字符串s，表示用户的操作序列。(s的长度<1000，不包含空格，可能存在非法操作)输入保证菜单最多两级，且每个选项的子菜单选项数不超过9个。

## 输出描述

输出到output.txt中。首先输出根目录菜单，然后根据操作序列，完成对应的输出。为了清晰，每两层输出之间用空行隔开。对于每一行菜单项，输出格式为"[a] b"，其中a为该菜单的编号，b为该菜单的内容。此外，特别规定* 若用户操作不合法，输出"Invalid input!"并换行，同时展示当前层级的菜单。* 所有子菜单都需要显示 "[#] BACK"选项。* 若一个选项下无下一级子菜单，则式该选项为一个“命令”。由于这个程序只是一个UI显示程序，未绑定每个命令的实际操作，因此，我们输出"Running <PATH>"，来示意命令的执行。其中PATH表示从根菜单到当前选项的路径，由不同层级的选项组成。层级的选项之间用'/'隔开。

## 样例输入

```text
12
# LOL
## Play
## Uninstall
# PUBG
## Play
## Help
## Uninstall
# Web
## LearnTsinghua
## InfoTsinghua
## Tyche
# Exit
11##94
```

## 样例输出

```text
[1] LOL
[2] PUBG
[3] Web
[4] Exit

[1] Play
[2] Uninstall
[#] BACK

Running <LOL/Play>
[1] Play
[2] Uninstall
[#] BACK

[1] LOL
[2] PUBG
[3] Web
[4] Exit

Invalid input!
[1] LOL
[2] PUBG
[3] Web
[4] Exit

Invalid input!
[1] LOL
[2] PUBG
[3] Web
[4] Exit

Running <Exit>
[1] LOL
[2] PUBG
[3] Web
[4] Exit
```

## 提示与说明

【数据范围】60%的数据，只包含1级菜单100%的数据，最多包含2级菜单【样例解释】由配置文件可推导出，菜单的结构为：[1] LOL|-- [1] Play|-- [2] Uninstall[2] PUBG|-- [1] Play|-- [2] Help|-- [3] Uninstall[3] Web|-- [1] LearnTsinghua|-- [2] InfoTsinghua|-- [3] Tyche[4] Exit最开始，程序输出顶级菜单：[1] LOL[2] PUBG[3] Web[4] Exit用户输入1，程序进入LOL子选项，展现子菜单（注意：子菜单包含[#] BACK项目）：[1] Play[2] Uninstall[#] BACK用户输入1，程序进入Play子选项。由于Play子选项下无其他子选项，因此执行该命令（即输出当前的菜单路径，不同级别之间用’/’隔开），命令执行结束后，重复出现当前选项。Running <LOL/Play>[1] Play[2] Uninstall[#] BACK用户输入#，程序执行BACK，返回上级菜单：[1] LOL[2] PUBG[3] Web[4] Exit用户输入#，由于顶级菜单没有#，因此为非法操作，输出”Invalid input!”，并重新输出当前菜单：Invalid input![1] LOL[2] PUBG[3] Web[4] Exit用户输入9，由于顶级菜单没有9，因此为非法操作，输出”Invalid input!”，并重新输出当前菜单：Invalid input![1] LOL[2] PUBG[3] Web[4] Exit用户输入4，程序进入[4] Exit选项。由于Exit选项下无其他选项，因此执行该命令（即输出当前的菜单路径），命令执行结束后，重复输出当前菜单。Running <Exit>[1] LOL[2] PUBG[3] Web[4] Exitvpn_eval((function () {
function toggle_code(h){
    var code_dom = h.getElementsByClassName('content')[0];
    var now = code_dom.style.display
    if (now == 'none'){
        code_dom.style.display = 'block'
    } else {
        code_dom.style.display = 'none'
    }
}
}
).toString().slice(14, -2), "");

