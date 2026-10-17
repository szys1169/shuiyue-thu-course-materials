# Markdown

> 本文件由同目录的 `题面.txt` 自动整理生成。原始文本和附件均未修改。

| 限制 | 内容 |
|---|---|
| 时间限制 | 未注明 |
| 内存限制 | 未注明 |

## 题目描述

Markdown是一个简单的标记语言。不像Word，Markdown完全用纯文本的方式，来表达内容和格式。其支持基本的常用格式，如标题、加粗、斜体、列表等，能很方便的应对日常写作的需求。那么今天，我们就来实现一个简化版本的Markdown编译器！简化的Markdown包含两类格式：1. 标题与段落格式。所有以'#'开头的行，被认为是标题行。	若以'# '开头，则认为是一级标题，转换后，需要在标题文字前后"<h1>""</h1>"，如：		"# Title abc" --> "<h1>Title abc</h1>"	若以'## '开头，则认为是二级标题，转换后，需要在标题文字前后"<h2>""</h2>"，如：		"## Title abc" --> "<h2>Title abc</h2>"	若以'### '开头，则认为是三级标题，转换后，需要在标题文字前后"<h3>""</h3>"，如：		"### Title abc" --> "<h3>Title abc</h3>"	最高只有三级标题。	除此以外，其他行被认为是段落行。转换后，需要在标题文字前后""""，如：		""good morning" --> "good morning""	特别注意首个空格问题，即		正确示例："### Title abc" --> "<h3>Title abc</h3>"		错误示例："### Title abc" --> "<h3> Title abc</h3>"        保证所有的标题，最后一个#和Title之间都有一个空格2. 字体格式	所有的字符都可以有以下三种格式：		斜体：用'*'包含的字符被认为是斜体，转换后需要用"<em>""</em>"包裹，如：			"*good *" --> "<em>good </em>"		加粗：用'**'包含的字符被认为是加粗，转换后需要用"<strong>""</strong>"包裹，如：			"**good **" --> "<strong>good </strong>"		加粗斜体：用'***'包含的字符被认为是加粗斜体，转换后需要用"<strong><em>""</em></strong>"包裹，如：			"***good***" --> "<strong><em>good</em></strong>"	所有的字体格式不会嵌套，不会跨行。正文内容中保证不存在'*'，所有的'*'均表示字体格式。为了简化问题，规定标题中不存在字体格式。文件中的所有空行将被忽略。不存在连续两个空格。

## 输入描述

从文件input.txt读入。内容为用简化Markdown格式书写的文件，每行不超过1000个字符。保证输入数据符合题目要求。注意：每行的结尾可能为'\n'，也可能为'\r' '\n'。请注意去除读入后每行末尾的所有'\r', '\n'。输入文件最后一行可能没有换行符。

## 输出描述

将转换后的文本，输出到文件output.txt。每行的结尾限定为'\n'。

## 样例输入

```text
# good morning

what a **beautiful** day! *wow*

## lalala

one ***line ***q***w***q

another line qwq
```

## 样例输出

```text
<h1>good morning</h1>
<p>what a <strong>beautiful</strong> day! <em>wow</em></p>
<h2>lalala</h2>
<p>one <strong><em>line </em></strong>q<strong><em>w</em></strong>q</p>
<p>another line qwq</p>
```

## 提示与说明

【数据组成说明】80%的数据，仅包含标题与段落格式，不存在字体格式。10%的数据，字体格式中只有斜体，不包含加粗和加粗斜体。10%的数据，包含上述所有格式。【增加一组针对80%数据的样例】Sample Input# Title1lala## Title2haha### Title3heheSample Output<h1>Title1</h1>lala<h2>Title2</h2>haha<h3>Title3</h3>hehe

