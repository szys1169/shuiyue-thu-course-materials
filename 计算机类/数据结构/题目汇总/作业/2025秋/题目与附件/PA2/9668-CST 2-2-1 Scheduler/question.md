<!-- 来源：https://dsa.cs.tsinghua.edu.cn/oj/problem.shtml?id=9668 -->

# CST 2-2-1 Scheduler

---

### **描述**

在现代操作系统中，进程调度系统会将时间切分为很小的片段，并分配给不同的进程。比如，若将时间片段的长度取作 1010 ms，则每一秒就被切分为 100100 个片段。将它们分配给 100100 个进程，则每个进程在每一秒内都能够运行 1010 ms，于是用户就会“感觉”这 100100 个进程在同时运行。

这里我们来实现一个简单的调度系统，为此你需要维护一个调度队列，同时支持以下功能：

<table class="table-bordered table-striped table">
<thead>
<tr>
<th><strong>命令</strong></th>
<th><strong>命令示例</strong></th>
<th><strong>功能说明</strong></th>
</tr>
</thead>
<tbody>
<tr>
<td><code>Create pid</code></td>
<td><code>Create 10</code></td>
<td>创建一个编号为 <code>pid</code> 的进程，将其置于调度队列的<strong>末尾</strong>。</td>
</tr>
<tr>
<td><code>Tick</code></td>
<td><code>Tick</code></td>
<td>取出队列头部的进程，<strong>输出其编号</strong>（假装它运行了一个时间片段），再将其放到调度队列的末尾。</td>
</tr>
<tr>
<td><code>Pause pid</code></td>
<td><code>Pause 10</code></td>
<td>将编号为 <code>pid</code> 的进程从调度队列中移出（模拟它被暂停）。</td>
</tr>
<tr>
<td><code>Resume pid</code></td>
<td><code>Resume 10</code></td>
<td>将编号为 <code>pid</code> 的进程放入调度队列<strong>头部</strong>（模拟它被重启）</td>
</tr>
</tbody>
</table>

### **输入**

第一行仅有一个整数 NN，即命令的总数。

接下来的 NN 行，各有一条命令。

所有命令都合法，具体来说：

- `Create` 命令中，每个 `pid` 只会被创建一次。
- 执行 `Tick` 命令时，调度队列非空。
- 执行 `Pause` 命令时，在调度队列中确实有编号为 `pid` 的进程。
- 执行 `Resume` 命令时，编号为 `pid` 的进程已被创建，且不在调度队列中。

### **输出**

对于每次 `Tick` 命令，输出调度队列头部进程的编号。

### **输入样例**

```
10
Create 1
Create 2
Create 3
Tick
Pause 3
Tick
Tick
Resume 3
Tick
Tick
```

### **输出样例**

```
1
2
1
3
2
```

### **样例解释**

<table class="table-bordered table-striped table">
<thead>
<tr>
<th style="text-align: center;"><strong>命令</strong></th>
<th style="text-align: center;"><strong>执行命令后：调度队列</strong></th>
<th style="text-align: center;"><strong>执行命令后：不在调度队列的进程</strong></th>
<th style="text-align: center;"><strong>输出</strong></th>
</tr>
</thead>
<tbody>
<tr>
<td style="text-align: center;"><code>Create 1</code></td>
<td style="text-align: center;"><code>[1]</code></td>
<td style="text-align: center;"><code>[]</code></td>
<td style="text-align: center;"></td>
</tr>
<tr>
<td style="text-align: center;"><code>Create 2</code></td>
<td style="text-align: center;"><code>[1, 2]</code></td>
<td style="text-align: center;"><code>[]</code></td>
<td style="text-align: center;"></td>
</tr>
<tr>
<td style="text-align: center;"><code>Create 3</code></td>
<td style="text-align: center;"><code>[1, 2, 3]</code></td>
<td style="text-align: center;"><code>[]</code></td>
<td style="text-align: center;"></td>
</tr>
<tr>
<td style="text-align: center;"><code>Tick</code></td>
<td style="text-align: center;"><code>[2, 3, 1]</code></td>
<td style="text-align: center;"><code>[]</code></td>
<td style="text-align: center;"><code>1</code></td>
</tr>
<tr>
<td style="text-align: center;"><code>Pause 3</code></td>
<td style="text-align: center;"><code>[2, 1]</code></td>
<td style="text-align: center;"><code>[3]</code></td>
<td style="text-align: center;"></td>
</tr>
<tr>
<td style="text-align: center;"><code>Tick</code></td>
<td style="text-align: center;"><code>[1, 2]</code></td>
<td style="text-align: center;"><code>[3]</code></td>
<td style="text-align: center;"><code>2</code></td>
</tr>
<tr>
<td style="text-align: center;"><code>Tick</code></td>
<td style="text-align: center;"><code>[2, 1]</code></td>
<td style="text-align: center;"><code>[3]</code></td>
<td style="text-align: center;"><code>1</code></td>
</tr>
<tr>
<td style="text-align: center;"><code>Resume 3</code></td>
<td style="text-align: center;"><code>[3, 2, 1]</code></td>
<td style="text-align: center;"><code>[]</code></td>
<td style="text-align: center;"></td>
</tr>
<tr>
<td style="text-align: center;"><code>Tick</code></td>
<td style="text-align: center;"><code>[2, 1, 3]</code></td>
<td style="text-align: center;"><code>[]</code></td>
<td style="text-align: center;">3</td>
</tr>
<tr>
<td style="text-align: center;"><code>Tick</code></td>
<td style="text-align: center;"><code>[1, 3, 2]</code></td>
<td style="text-align: center;"><code>[]</code></td>
<td style="text-align: center;"><code>2</code></td>
</tr>
</tbody>
</table>

### **数据范围**

1≤N≤1061 \le N \le 10^6

1≤1 \le `pid` ≤106\le10^6

0≤0 \le `Tick` 命令总数 ≤100,000\le 100,000

### **资源限制**

时间限制：1 sec

空间限制：256 MB
