# PDF解析与显示情况

本地PyMuPDF结构与首/中/末页抽样检查：11份报告结构告警，其中10份读取时需容错；7份的抽样共10页渲染为白页，部分首页有明显字形/排版异常。这里只报告该解析器的表现，不能据此断言原稿页面应为空白或所有查看器都无法显示。没有改写原件，原始字节源与旧目标一致；本批迁移验收证明字节保存，不等于原件完整可读、内容正确或已修复。逐件状态与抽样页见《PDF解析与显示情况.md》。未逐页视觉核对解析计数1481页。

文件标记仅针对本地PyMuPDF，原件未修改；未跨查看器比较，未把诊断告警当作数学内容审查。全部25原件源与旧云盘字节相同。

| 原文件 | 读取容错 | 结构告警 | 抽样白页（PDF页序） |
|---|---|---|---|
| GRI_Spr2022_LectX1_Ch1_Part9.pdf | 否 | 未报 | 抽样未见 |
| GRI_Spr2022_Lects01-02_Ch1_Part1 (1).pdf | 否 | 未报 | 抽样未见 |
| GRI_Spr2022_Lects01-02_Ch1_Part1.pdf | 是 | 有 | 47 |
| GRI_Spr2022_Lects04-05_Ch1_Part4.pdf | 否 | 未报 | 抽样未见 |
| GRI_Spr2022_Lects04_Ch1_Part3.pdf | 否 | 有 | 抽样未见 |
| GRI_Spr2022_Lects06_Ch1_Part5.pdf | 是 | 有 | 抽样未见 |
| GRI_Spr2022_Lects07-08_Ch1_Part6fix.pdf | 是 | 有 | 91 |
| GRI_Spr2022_Lects09_Ch1_Part7.pdf | 是 | 有 | 34,67 |
| GRI_Spr2022_Lects10-11_Ch1_Part8.pdf | 否 | 未报 | 抽样未见 |
| GRI_Spr2022_Lects11-12_Ch2_Part1.pdf | 否 | 未报 | 抽样未见 |
| GRI_Spr2022_Lects13-14_Ch2_Part2.pdf | 否 | 未报 | 抽样未见 |
| GRI_Spr2022_Lects14-15_Ch2_Part3.pdf | 否 | 未报 | 抽样未见 |
| GRI_Spr2022_Lects15-16_Ch2_Part4.pdf | 否 | 未报 | 抽样未见 |
| GRI_Spr2022_Lects16-17_Ch2_Part5.pdf | 否 | 未报 | 抽样未见 |
| GRI_Spr2022_Lects18-19_Ch3_Part1.pdf | 是 | 有 | 抽样未见 |
| GRI_Spr2022_Lects19-20_Ch3_Part2.pdf | 是 | 有 | 41,80 |
| GRI_Spr2022_Lects20-21_Ch3_Part3.pdf | 是 | 有 | 57 |
| GRI_Spr2022_Lects21-23_Ch3_Part4.pdf | 是 | 有 | 78 |
| GRI_Spr2022_Lects23-25_Ch3_Part5.pdf | 否 | 未报 | 抽样未见 |
| GRI_Spr2022_Lects25-26_Ch4_Part1new.pdf | 否 | 未报 | 抽样未见 |
| GRI_Spr2022_Lects25_Ch3_Part6.pdf | 否 | 未报 | 抽样未见 |
| GRI_Spr2022_Lects27-28_Ch4_Part3.pdf | 否 | 未报 | 抽样未见 |
| GRI_Spr2022_Lects27_Ch4_Part2.pdf | 是 | 有 | 抽样未见 |
| GRI_Spr2022_Lects28-29_Ch4_Part4.pdf | 否 | 未报 | 抽样未见 |
| GRI_Spr2022_Lects29-30_Ch4_Part5.pdf | 是 | 有 | 59,30 |
