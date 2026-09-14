<!-- 来源：https://dsa.cs.tsinghua.edu.cn/oj/problem.shtml?id=9670 -->

# CST 2-2-3 Triangulation

---

### **题目描述**

多边形三角剖分（Polygon triangulation）是计算几何中的一个基本问题，也就是如下图实例那样，将一个多边形的**内部**切分为若干个不相交的三角形。

<table class="table-bordered table-striped table">
<thead>
<tr>
<th style="text-align: center;"><img src="attachment/6c9a/6c9a8eb511fe2e2c27314fe5df557dbad5bdd10f.png" alt="" height="150" width="400"></th>
</tr>
</thead>
<tbody>
<tr>
<td style="text-align: center;"><strong>图1. 多边形的三角剖分</strong></td>
</tr>
</tbody>
</table>

通过端点依次连接的一组线段，称作**多边形链**（polygonal chain）；这些线段称作**边**（edge），其端点称作**节点**（vertex）。若不相连的节点/边互不相交，则称作**简单多边形链**（simple polygonal chain）。特别地，首、尾端点重合的多边形链称作**多边形**；若对应于简单多边形链，则称作**简单多边形**（simple polygon）。简单多边形必然恰好将平面分为两个连通域，分别称作其**内部**（interior）和**外部**（exterior）。由n条边（n个节点）构成的简单多边形，也简称n边形（n-gon）。

<table class="table-bordered table-striped table">
<thead>
<tr>
<th style="text-align: center;"><img src="attachment/4290/4290df177e93777d2d806a7057303c842e92c6c5.png" alt="" height="200" width="600"></th>
</tr>
</thead>
<tbody>
<tr>
<td style="text-align: center;"><strong>图2. 简单多边形</strong></td>
</tr>
</tbody>
</table>

在简单多边形中，每对不相邻节点之间的开线段都称作一条对角线（diagonal）；其中完全属于多边形内部者，称作内对角线（internal diagonal）。所谓简单多边形的三角剖分，可以理解为极大的一组互不相交的内对角线。 可以证明，任一简单多边形都存在三角剖分。进一步地，尽管n边形的姿态各异，且每一个往往有多种三角剖分的方式，但使用对角线的总数却总是 n−3n-3。

本作业只考虑简单多边形的一种特例—— xx-**单调多边形**： 多边形链 CC 在垂直投影到某条直线 L\mathcal L 上之后，若所有节点的投影能够保持原先的次序，则称之为沿直线 L\mathcal L 单调（monotone w.r.t. L）。简单多边形 PP 若能分解为两条相对于 xx 轴的单调链，则称之为 xx-单调多边形。

<table class="table-bordered table-striped table">
<thead>
<tr>
<th style="text-align: center;"><img src="attachment/d901/d901b5125e31bbd13cdd262b9285b7eaf898d28b.png" alt="" height="100" width="375"></th>
<th style="text-align: center;"><img src="attachment/87fe/87fe7e1bf4c8c2636e22aa64dfba1046ef2a76f0.png" alt="" height="100" width="170"></th>
</tr>
</thead>
<tbody>
<tr>
<td style="text-align: center;"><strong>图3. 单调多边形链</strong></td>
<td style="text-align: center;"><strong>图4. 单调多边形</strong></td>
</tr>
</tbody>
</table>

实际上，我们可以在 O(n)\mathcal O(n) 时间内构造出任一简单多边形的（一种）三角剖分，对单调多边形而言这自然更不在话下[1]。

#### **算法描述**

以图4中由 1717 个节点构成的 xx-单调多边形为例。其中内角不小于 π\pi 的节点，称作优节点（reflex vertex），其余称作劣节点（non-reflex vertex）。除首、尾节点外完全由优节点组成的多边形链，称作优链（reflex chain）。

这里采用扫描线算法：假想着有一条竖线从左而右地扫过n边形，逐一处理遇到的每个节点，并贪心地通过连接当前节点和某个此前已经扫过的节点，引入一些**对角线**。每引入一条对角线，都相应地切出一个三角形。为此，需要使用一个栈 SS，来记录多边形在当前扫描线左侧——虽已扫过却仍待处置——的那部分。作为算法的一项不变性，SS 中的节点总是来自于同一条单调链，且构成一条优链。

在处理每个节点 viv_i 时，算法无非分三种情况作相应的处理：

情况1. 若 viv_i 与 SS 中节点不属于同一条单调链，则 SS 中每个节点与 viv_i 之间的连边，必然都是一条内对角线。于是，我们便可以在清空 SS 的过程中引入这些内对角线，再令原先的栈顶节点和 viv_i 入栈；

情况2. 若 viv_i 与 SS 中节点同属一条单调链，则又可细分为两种子情况：

(a). 若栈顶 vi−1v_{i-1} 为优节点，则令 viv_i 入栈；

(b). 反之若栈顶 vi−1v_{i-1} 系劣节点，则可弹出 vi−1v_{i-1} 并引入内对角线 vi−2viv_{i-2}v_i。这种情况可能重复多次，直至转入子情况(a)，或者栈中已不足两个节点（算法终止）。

请自行证明：算法执行的过程中，以下不变性始终满足： **不变性.** ∀i≥2\forall i\ge 2，令 viv_i 是算法刚处理过的节点。viv_i 左侧尚未剖分的区域由两条 xx-单调链构成：其一为优链，恰好存放在辅助栈中；另一条链只有一条边，其左端点栈底节点 uu，而右端点在 viv_i 右侧。

<table class="table-bordered table-striped table">
<thead>
<tr>
<th style="text-align: center;"><img src="attachment/f2f3/f2f3b9ab5fb1dee33cef45ac8790316238c1c990.png" alt="" height="200" width="600"></th>
</tr>
</thead>
<tbody>
<tr>
<td style="text-align: center;"><strong>图5. 算法的不变性</strong></td>
</tr>
</tbody>
</table>

<table class="table-bordered table-striped table">
<thead>
<tr>
<th style="text-align: center;"><img src="attachment/215b/215bf6ac5fb0d33142afaa2a3346d9530111219e.png" alt="" height="250" width="600"></th>
</tr>
</thead>
<tbody>
<tr>
<td style="text-align: center;"><strong>图6. 算法执行过程</strong></td>
</tr>
</tbody>
</table>

你需要实现剖分 xx-单调多边形的上述算法[1]。

### **输入输出格式描述**

**输入格式**

第一行一个正整数 nn，表示多边形的节点数。

随后的 nn 行各有两个整数，依次给出各节点的坐标 (xi,yi)(x_i, y_i)。

**输出格式**

n−2n-2 行，每行用六个整数 x1y1x2y2x3y3x_1 y_1 x_2 y_2 x_3 y_3 表示一个切分出来的三角形。

注意：合法的多边形的三角剖分方案可能不唯一。本作业仅接收算法[1]给出的三角剖分方案作为正确答案。在方案一致的情况下，输出三角形的顺序、三角形端点的顺序均不限。

### **样例输入输出**

**输入样例**

```
20
137876341 -216903
223594534 64903
233111412 -593438
267623903 -63349
268791140 -605783
312017344 -200746
344361022 -499733
352011687 -538670
445833341 995114
416815266 589802
373656738 64671
279774421 198087
194934036 392113
154654782 327371
90910600 472940
47304081 535725
34312708 666509
0 0
111486754 -893838
127443712 -850039
```

**输出样例**

```
0 0 34312708 666509 47304081 535725
0 0 47304081 535725 90910600 472940
0 0 90910600 472940 111486754 -893838
90910600 472940 111486754 -893838 127443712 -850039
90910600 472940 127443712 -850039 137876341 -216903
90910600 472940 137876341 -216903 154654782 327371
137876341 -216903 154654782 327371 194934036 392113
137876341 -216903 194934036 392113 223594534 64903
223594534 64903 233111412 -593438 267623903 -63349
194934036 392113 223594534 64903 267623903 -63349
267623903 -63349 268791140 -605783 279774421 198087
194934036 392113 267623903 -63349 279774421 198087
268791140 -605783 279774421 198087 312017344 -200746
279774421 198087 312017344 -200746 344361022 -499733
279774421 198087 344361022 -499733 352011687 -538670
279774421 198087 352011687 -538670 373656738 64671
352011687 -538670 373656738 64671 416815266 589802
352011687 -538670 416815266 589802 445833341 995114
```

### **数据范围和时空限制**

- 为方便同学们解题，本题允许使用STL。
- 3≤n≤1063\le n\le 10^6。
- ∀i,−109≤xi,yi≤109\forall i, -10^9\le x_i, y_i\le 10^9 ，坐标均保证是整数。
- 保证没有两个节点有同样的 xx 坐标。
- 保证不存在连续三点共线的情况。
- 节点输入顺序为一条多边形链，起始节点随机，逆时针方向。

时间限制：1.5s

内存限制：256 MB

### **参考文献**

[1] Garey, Michael R., David S. Johnson, Franco P. Preparata, and Robert E. Tarjan. "Triangulating a simple polygon." *Information Processing Letters* 7, no. 4 (1978): 175-179.

### **演示**

你可以借助 [这个演示工具](../附件/369388f4ba3d90cf3daa81dcb13bea688335ecfb.html) 验证你的实现的正确性。试试将上述输入输出保存成txt文件，然后上传。
