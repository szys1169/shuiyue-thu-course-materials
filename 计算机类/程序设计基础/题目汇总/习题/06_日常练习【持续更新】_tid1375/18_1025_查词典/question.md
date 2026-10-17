# 查词典

> 本文件由同目录的 `题面.txt` 自动整理生成。原始文本和附件均未修改。

| 限制 | 内容 |
|---|---|
| 时间限制 | 未注明 |
| 内存限制 | 未注明 |

## 题目描述

你在查英文词典时，一般都是先随手一翻，如果你要查的单词以s开头，而你不幸翻到了j，你就会继续往后翻，这是因为你能确定你要的单词不会出现在你手翻到的当前页的前面。
       计算机比你牛一点，它随手一翻，能正好翻到词典中间，然后根据所要查找单词与当前单词在词典中的位置关系，从而将后续查找范围缩小到前半部分或后半部分。这便是折半查找（也叫二分查找）的思想。
       现在给出一个词典，用机器的话说，也就是一个按词典序排列的字符串数组。然后给出查找其中若干个词的请求，请你编程给出查找结果。

## 输入描述

第一行一个正整数n，表示词典大小，即单词数量
       接下来n行，每行一个单词
       再接下来一行，为一个正整数m，表示查找请求的数量
       接下来m行，每行一个请求查找的单词。

## 输出描述

对于m个请求输出m行，每行为其请求查找的结果，如果找到了，就输出单词在词典中的位置下标，下标从0开始。如果没找到则输出-1

## 样例输入

```text
</font>
<font size="3" face="Times New Roman">5</font>
<font size="3" face="Times New Roman">chensheng</font>
<font size="3" face="Times New Roman">daimingyang</font>
<font size="3" face="Times New Roman">liuyuchen</font>
<font size="3" face="Times New Roman">xumingxing</font>
<font size="3" face="Times New Roman">zhangyongchao</font>
<font size="3" face="Times New Roman">3</font>
<font size="3" face="Times New Roman">liuyuchen</font>
<font size="3" face="Times New Roman">zhangyongchao</font>
<font size="3" face="Times New Roman">xumingxin</font>
<font size="3" face="Times New Roman"> </font>
<font size="3">
```

## 样例输出

```text
</font>
<font size="3" face="Times New Roman">2</font>
<font size="3" face="Times New Roman">4</font>
<font size="3" face="Times New Roman">-1</font>
<font size="3" face="Times New Roman"> </font>
<font size="3">
```

## 提示与说明

数据规模】
1<=n<=100000
1<=m<=100000
单词中只包含26个英文小写字母
单词最长不超过20个字符
输入的n个单词保证按字典序从小到大排序，保证不存在相同单词

