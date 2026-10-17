# 字符序列处理

> 本文件由同目录的 `题面.txt` 自动整理生成。原始文本和附件均未修改。

| 限制 | 内容 |
|---|---|
| 时间限制 | 未注明 |
| 内存限制 | 未注明 |

## 题目描述

补全代码：函数 process_chars - 将小写改大写，大写保持不变，数字转成#，其他非字母非数字的字符转成 小数点。函数 count_chars - 统计字符数组中 字母个数、数字个数、非字母非数字字符个数，以三个指针变量返回。#include <iostream>
#include <cstring>
using namespace std;

// 统计原字符串中字母、数字、非字母非数字的个数
void count_chars(const char a[], int *p_letter, int *p_digit, int *p_other)
{
    // 填补代码 ①
}

// 将小写改大写，大写保持不变，数字变为#，其他变为.
void process_chars(char a[])
{
    // 填补代码 ②
}

int main()
{
    char s[100];
    cin.getline(s, 100);

    int letters = 0, digits = 0, others = 0;
    count_chars(s, &letters, &digits, &others);

    process_chars(s);
    cout << s << endl;

    cout << "Letters: " << letters
         << ", Digits: " << digits
         << ", Others: " << others;
    return 0;
}

## 输入描述

输入一个字符数组（数组长度小于100）

## 输出描述

输出处理完的字符串，以及字符数组中 字母个数、数字个数、非字母非数字字符个数

## 样例输入

```text
C++ is fun 2025 :)
```

## 样例输出

```text
C...IS.FUN.####...
Letters: 6, Digits: 4, Others: 8
```

## 提示与说明

除待填充部分外，其他代码系统已提供，点击“我要交代码”可以看到已有代码和填充区域。

