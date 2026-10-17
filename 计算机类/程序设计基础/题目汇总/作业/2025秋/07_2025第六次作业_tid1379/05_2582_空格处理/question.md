# 空格处理

> 本文件由同目录的 `题面.txt` 自动整理生成。原始文本和附件均未修改。

| 限制 | 内容 |
|---|---|
| 时间限制 | 未注明 |
| 内存限制 | 未注明 |

## 题目描述

输入一行空格分隔的英语单词串（只含空格与字母），不超过100个字符。要求编写函数，对输入的一行单词序列（单词中间以空格分隔），要求删除行首和行尾的空格，去掉单词中多余的空格（单词间只保留一个空格），每个单词的首字母大写，其余字母小写。函数返回值类型为字符指针，指向在函数中的动态分配内存（保存处理后的字符串）。#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

// 补充函数 format_line

int main()
{
    char input_line[100];
    cin.getline(input_line, 100);

	char* result_str = format_line(input_line);
	cout << result_str << endl;

	delete[] result_str;
    return 0;
}

## 输入描述

输入一行空格分隔的英语单词串（只含空格与字母），不超过100个字符。

## 输出描述

输出处理后的英语单词串。

## 样例输入

```text
fundamentals   of  programming
```

## 样例输出

```text
Fundamentals Of Programming
```

## 提示与说明

根据main函数中的调用方式补充函数头和函数体。

