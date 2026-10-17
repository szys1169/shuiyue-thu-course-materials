# 《交换代数导引》学习指南

**Introduction to Commutative Algebra**
M. F. Atiyah, I. G. MacDonald（Addison-Wesley, 1969；Westview Press 重印）

> 全书宗旨：素理想（prime ideal）是中心概念；模论与局部化（localization）是贯穿全书的两大方法；许多结论带有几何（仿射概形 / scheme）背景。

---

## 一、中文目录（与原书完全对应）

**引言 Introduction**（原书 vii 页）—— 交换代数的来源（代数几何与代数数论）、本书写法说明

**记号与术语 Notation and Terminology**（ix）

### 第 1 章　环与理想 Rings and Ideals（p.1）★核心

- 环与环同态 Rings and ring homomorphisms
- 理想、商环 Ideals. Quotient rings
- 零因子、幂零元、单位 Zero-divisors. Nilpotent elements. Units
- 素理想与极大理想 Prime ideals and maximal ideals
- 幂零根与 Jacobson 根 Nilradical and Jacobson radical
- 理想的运算 Operations on ideals
- 扩张与收缩 Extension and contraction
- 习题 Exercises（10）

### 第 2 章　模 Modules（p.17）★核心

- 模与模同态 Modules and module homomorphisms
- 子模与商模 Submodules and quotient modules
- 子模的运算 Operations on submodules
- 直和与直积 Direct sum and product
- 有限生成模 Finitely generated modules
- 正合列 Exact sequences
- 模的张量积 Tensor product of modules
- 纯量的限制与扩张 Restriction and extension of scalars
- 张量积的正合性 Exactness properties of the tensor product
- 代数 Algebras
- 代数的张量积 Tensor product of algebras
- 习题（31）

### 第 3 章　分式环与分式模 Rings and Modules of Fractions（p.36）★核心

- 局部性质 Local properties
- 分式环中理想的扩张与收缩 Extended and contracted ideals in rings of fractions
- 习题（43）

### 第 4 章　准素分解 Primary Decomposition（p.50）★核心

- （正文无分节，直接进入准素理想与分解理论）
- 习题（55）

### 第 5 章　整相关与赋值 Integral Dependence and Valuations（p.59）★核心

- 整相关 Integral dependence
- 上升定理 The going-up theorem
- 整闭整环、下降定理 Integrally closed integral domains. The going-down theorem
- 赋值环 Valuation rings
- 习题（67）

### 第 6 章　链条件 Chain Conditions（p.74）

- 习题（78）

### 第 7 章　Noether 环 Noetherian Rings（p.80）★核心

- Noether 环中的准素分解 Primary decomposition in Noetherian rings
- 习题（84）

### 第 8 章　Artin 环 Artin Rings（p.89）★核心

- 习题（91）

### 第 9 章　离散赋值环与 Dedekind 整环 Discrete Valuation Rings and Dedekind Domains（p.93）

- 离散赋值环 Discrete valuation rings
- Dedekind 整环 Dedekind domains
- 分式理想 Fractional ideals
- 习题（99）

### 第 10 章　完备化 Completions（p.100）

- 拓扑与完备化 Topologies and completions
- 滤链 Filtrations
- 分次环与分次模 Graded rings and modules
- 相伴分次环 The associated graded ring
- 习题（113）

### 第 11 章　维数理论 Dimension Theory（p.116）

- Hilbert 函数 Hilbert functions
- Noether 局部环的维数理论 Dimension theory of Noetherian local rings
- 正则局部环 Regular local rings
- 超越维数 Transcendental dimension
- 习题（125）

**索引 Index**（127）

---

## 二、重点内容与学习优先级

### 全书主线

1. **素理想是中心概念**：它同时统一了算术中的"素数"与几何中的"点"。
2. **局部化是主要技术**：把环在素理想处"局部化" = 几何上"在某点附近聚焦"。第 3 章与第 11 章是它的两大应用点。
3. **模论视角**：本书按现代取向，大量结论用模和正合列陈述（如张量积、局部化、维数理论），学几何前必须掌握。
4. **行文紧凑**：原书"省略例行验证"，很多定理与重要结论以习题形式出现——务必配合 Carlson / Gaillard 两份笔记使用。

### 三档优先级

| 优先级 | 章节 | 理由 |
| --- | --- | --- |
| ★★★ 精读（骨架） | 第 1–5 章 | 环、模、局部化、准素分解、整相关，是全部后续内容的地基 |
| ★★★ 精读（结构理论） | 第 7、8 章 | Noether 环（Hilbert 基定理、准素分解）与 Artin 环结构定理 |
| ★★ 选读（专题入口） | 第 9–11 章 | 分别通向代数数论（Dedekind 整环）、代数几何（完备化）、维数理论（正则局部环） |
| ★ 了解 | 第 6 章 | 篇幅短，为第 7、8 章做准备 |

### 各章必掌握的核心点

- **第 1 章**：极大理想的存在性（Zorn 引理）、`Nil(R)` 与 `J(R)`、素理想的等价刻画、理想运算（和、积、交、商、根）、扩张/收缩的对应性质。典型习题 1.1–1.12、1.15、1.22、1.26。
- **第 2 章**：正合列的判定与分裂、有限生成模、张量积的存在性/右正合性、平坦模（习题 2.19 起）、**Nakayama 引理（习题 2.6）**、纯量扩张。典型习题 2.1–2.13。
- **第 3 章**：分式环 `S⁻¹A` 的万有性质、局部化与素理想的对应、局部性质（有限生成、平坦性等"局部性"判定）。典型习题 3.1–3.9、3.12–3.15。
- **第 4 章**：准素理想、准素分解的存在性（命题 4.5）、第一/第二唯一性定理（4.10、4.11）、极小准素分解、孤立与嵌入素理想。
- **第 5 章**：整元素与整闭包、**going-up（5.11）**、整闭整环、**going-down（5.16）**（需正规性条件）、赋值环与整闭包的关系。典型习题 5.1–5.9、5.12–5.14。
- **第 6 章**：ACC/DCC、Noether 模 ⇔ 所有子模有限生成、有限生成模的链条件行为。
- **第 7 章**：**Hilbert 基定理（7.5）**、Noether 环中准素分解的存在性（7.13）、相伴素理想、Kronecker 维数转场。
- **第 8 章**：**Artin 环结构定理（8.7）**：Artin ⇔ Noether 且维数为 0；Artin 环 = 有限个 Artin 局部环的直积。
- **第 9 章**：DVR 的等价刻画（命题 9.2）、Dedekind 整环 = 维数 ≤1 的整闭 Noether 整环、分式理想与理想类群、`Z` 与 `k[x]` 的类比。
- **第 10 章**：`I`-进拓扑、完备化与逆极限、滤链与 Artin–Rees 引理（习题 10.7）、分次环与相伴分次环、完备化的平坦性。
- **第 11 章**：Hilbert 函数与 Hilbert 多项式、Noether 局部环维数的三种等价定义（Krull 维数 = 参数系长度 = Hilbert 多项式次数）、**正则局部环（11.24 起）**、超越维数。

### 学习建议

1. 按"精读 → 结构理论 → 专题"推进；若时间有限，第 9–11 章可先只读结论、回看时再补证明。
2. **习题是本书精华**：许多后续教材直接引用 AM 的习题结论（如 Nakayama、平坦性、Artin–Rees）。建议每章至少完成"课程选定"范围内的习题（可参考本目录下 `carlson_solutions.pdf` 与 `gaillard_notes.pdf`）。
3. 遇到被省略的验证，先自己补，再对照 Gaillard 笔记。

---

## 三、与课程讲义（Lectures 文件夹）的对照

课程 18 讲课件可视为 AM 的"现代版讲法"：用范畴/同调语言重述 AM 第 1–3、5–7 章的主干，并补充了大量 AM 没有的内容。逐讲对照如下（AM 编号为原书命题/定理/推论的编号）。

| 讲次 | 课件主题 | 对应 AM 内容 | 备注 |
| --- | --- | --- | --- |
| 01 | 基础环论复习：环、理想、商环、同态、理想运算、CRT、素/极大理想、单位/零因子/幂零元、约化环 | 第 1 章 §1.1–1.6 | 缺 Jacobson 根 `J(R)`、理想的根、§1.7 扩张与收缩 |
| 02 | 模论基础：模、同态、`Hom`、子模/商模、生成、零化子、循环模/单模 | 第 2 章 §2.1–2.3 | `A[x]`-模为补充内容 |
| 03 | 直积/直和、自由模、秩、矩阵/行列式、"环上的线性代数" | 第 2 章 §2.4–2.5 | 矩阵、行列式、秩部分超出 AM |
| 04 | PID 上模的结构定理 | —（AM 未涉及） | 抽象代数内容，AM 不讨论 |
| 05 | 张量积、张量–Hom 伴随 | 第 2 章 §2.7–2.8 | 伴随关系在 AM 中只是习题 |
| 06 | 双模的张量–Hom 伴随、纯量扩张/余扩张 | 第 2 章 §2.8–2.9 | 双模、coextension 超出 AM |
| 07 | 范畴与函子 | —（AM 未涉及） | 现代语言工具 |
| 08 | 自然变换、Yoneda 引理、伴随函子 | —（AM 未涉及） | 同上 |
| 09 | 模范畴上的函子、正合列、蛇引理、左/右正合函子 | 第 2 章 §2.6（正合列） | 蛇引理、范畴核/余核超出 AM |
| 10 | 投射/内射/平坦模、Baer 判据、挠模、faithfully flat | 平坦性：第 2、3 章习题（faithfully flat 见第 3 章习题 16） | 投射/内射模 AM 正文不出现 |
| 11 | 有限表现模、Noether 环/模、Hilbert 基定理 | 第 6 章 §6.1 + 第 7 章 (7.5) | 有限表现为补充概念 |
| 12 | 有限生成代数、有限代数、Zariski 引理 | 第 5 章 §5.1 + 推论 5.24 | Zariski 引理 = AM 推论 5.24（另见 7.9） |
| 13 | Zariski 拓扑、Hilbert 零点定理、Spec | AM 中为零点定理 (5.24)、(7.9)–(7.10)；Zariski 拓扑/Spec 多为习题 | 课件把它当作主线讲 |
| 14 | 分式环（局部化） | 第 3 章 §3.1–3.3 | 课件直接引用 AM 习题 3.3 |
| 15 | 分式模、局部性质 | 第 3 章 §3.1 后半、§3.4–3.5 | M=0、单/满射、平坦性的局部判定 |
| 16 | Cayley–Hamilton、Nakayama 引理 | 命题 2.4（行列式技巧）+ 命题 2.6（Nakayama） | AM 不叫 Cayley–Hamilton，即 2.4 |
| 17 | 整扩张、整闭包、正规整环 | 第 5 章 §5.1–5.3 | 规范化例子（`k[x,y]/(y²−x³)`）超出 AM 正文 |
| 18 | 整扩张的性质：极大性、不可比、lying-over、going-up/down | (5.7)–(5.11)、(5.16) | 即 Cohen–Seidenberg 定理 |

### 教材有、课件目前没有的内容（自学重点缺口）

1. **第 4 章 准素分解**：课件完全没有覆盖，但它是 Noether 环理论（第 7 章）与维数理论的基石，属于最值得补的一章。
2. **第 1 章尾部**：Jacobson 根 `J(R)`、理想根（radical）、扩张/收缩的完整理论（课件只在局部化处零散涉及）。
3. **第 5 章 §5.4 赋值环**：课件只用到 Zariski 引理（5.24），赋值环本身（5.18–5.23）没讲。
4. **第 7 章 Noether 环中的准素分解（7.13）** 与相伴素理想。
5. **第 8 章 Artin 环**（8.7 结构定理）。
6. **第 9 章 DVR 与 Dedekind 整环**（课件第 10 讲只在例子中提到 Dedekind 整环中理想是投射的）。
7. **第 10 章 完备化**（含 Artin–Rees 引理 10.9）。
8. **第 11 章 维数理论**（Hilbert 函数、正则局部环）。
9. 第 6 章的 DCC / Artin 模部分（课件只讲了 ACC / Noether）。

### 课件有、教材没有的内容

- PID 上模的结构定理（第 4 讲）
- 范畴论全套：范畴、函子、自然变换、Yoneda 引理、伴随函子（第 7–8 讲）
- 同调代数入门：蛇引理、左/右正合、投射/内射模、Baer 判据、投射生成子/内射余生成子（第 9–10 讲）
- Quillen–Suslin 定理等现代结果（第 10 讲提及）
- 显式命名 Cayley–Hamilton 定理（AM 只以命题 2.4 的行列式技巧出现）
- 挠模、可除模、faithfully flat 的系统讨论（AM 中仅在习题出现）

### 使用建议

- 学课件时对照 AM 编号（2.4、2.6、3.x、5.8–5.11、5.16、5.24、7.5、7.9–7.10、10.9），课件省略的细节正好由 AM 补上。
- 课件落下的大块（尤其第 4 章准素分解）建议在学完第 3 章局部化后立刻补读 AM 第 4 章，再回到第 7 章。
- 若目标是代数几何：第 10 章完备化与第 11 章维数理论必须补；若目标是代数数论：优先补第 9 章。
