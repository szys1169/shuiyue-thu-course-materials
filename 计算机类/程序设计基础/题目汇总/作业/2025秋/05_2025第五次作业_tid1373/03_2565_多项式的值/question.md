# 多项式的值

> 本文件由同目录的 `题面.txt` 自动整理生成。原始文本和附件均未修改。

| 限制 | 内容 |
|---|---|
| 时间限制 | 未注明 |
| 内存限制 | 未注明 |

## 题目描述

给定一个最高次数为 N（N ≤ 5）的多项式，其系数按升幂存放在长度足以容纳这 N+1 个值的一维数组中：数组下标 0 对应常数项 a₀数组下标 1 对应一次项系数 a₁…数组下标 n 对应 n 次项系数 aₙ补全代码：函数 Eval_Polynomial 计算给定多项式在点 x 处的值并返回。   #include <bits/stdc++.h>using namespace std;double Eval_Polynomial(const double a[], int n, double x){    // 填空：计算多项式值}int main(){    double x;    cin >> x;    double a[6];    int n;    cin >> n;    for(int i = 0; i < n + 1; i ++) cin >> a[i];        // 求多项式在 x 处的值    double res = Eval_Polynomial(a, n, x);    cout << fixed << setprecision(3) << res << endl;    return 0;}

## 输入描述

共三行，第一行一个双精度浮点数 x，表示求值点。第二行一个整数N，表示多项式最高次数。第三行 N+1 （N ≤ 5）个双精度浮点数表示多项式的系数， 依次是a₀、a₁…aₙ，每两个系数中间用空格分开。

## 输出描述

多项式在指定点 x 处的值，保留三位小数。

## 样例输入

```text
1.0
3
2.0 1.0 2.0 3.0
```

## 样例输出

```text
8.000
```

