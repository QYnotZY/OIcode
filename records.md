# 做题记录

## 9月2日

学习基于top cluster分解的树分块。

[P6177 Count on a tree II/【模板】树分块 from Luogu](https://www.luogu.com.cn/problem/P6177)

拿板题小试一下自己写的top cluster分解正确性，为下一题铺垫。

[#435. 【集训队作业2018】Simple Tree from UOJ](https://uoj.ac/problem/435)

tc分解后对每个簇维护一个簇路径桶即可维护答案，由于空间太大，需要根号重构来减小桶的空间。

第一次写调了比较久。应谨记查询子树时，只有簇路径上的点需要在收缩树上dfs，以及根要额外初始化。

[P5305 【GXOI/GZOI2019】 旧词 from Luogu](https://www.luogu.com.cn/problem/P5305)

维护簇内前缀和、收缩树前缀和以及懒标记，实现$O(\sqrt{n})$修改，$O(1)$查询。试验一下树分块平衡复杂度的写法。

## 9月3日

先把昨天选定的题清掉。

[P6778 【Ynoi2009】 rpdq from Luogu](https://www.luogu.com.cn/problem/P6778)

简单推式子转化后，用一次莫队二次离线后转化为旧词类似问题（即求下文的$F$），然后树分块平衡复杂度即可。

$$
\begin{align*}
\sum_{i = l}^{r} \sum_{j = i + 1}^{r} dis(i, j)
&= (\sum_{i = l}^{r} \sum_{j = i + 1}^{r} dep_i + \sum_{i = l}^{r} \sum_{j = i + 1}^{r} dep_j) - 2 \sum_{i = l}^{r} \sum_{j = i + 1}^{r} dep_{lca(i, j)} \\
&= (r - l) * \sum_{i = l}^{r} dep_i - 2 F \\
F &= \sum_{i = l}^{r} \sum_{j = i + 1}^{r} dep_{lca(i, j)}
\end{align*}
$$

同学在谈论，遂写一发整体二分。

[P1527 【国家集训队】 矩阵乘法 from Luogu](https://www.luogu.com.cn/problem/P1527)

板子题。发现还没写过，就简单写一发。

想到之前有道没写出来的分治，今天再战一番。

[P3206 【HNOI2010】 城市建设 from Luogu](https://www.luogu.com.cn/problem/P3206)

cdq分治，维护一定不会是答案的边，以及一定是答案的边，即可把剩下的边减到$O(len)$规模。

补一下NOIP吧。

[P11361 【NOIP2024】 编辑字符串 from Luogu](https://www.luogu.com.cn/problem/P11361)

贪心，难度评级让我一度不敢写上去。

## 9月4日

模拟赛。

[1.  组队 from XYD](https://xinyoudui.com/ac/contest/74700A3800008870671CA76/problem/9896)

细节多，对零和一个负数的情况都要特判。

[2.  糖果 from XYD](https://xinyoudui.com/ac/contest/74700A3800008870671CA76/problem/9897)

二分答案，钦定答案后可以快速算出每个元素的贡献。

[3.  方程的解 from XYD](https://xinyoudui.com/ac/contest/74700A3800008870671CA76/problem/9898)

Meet in the middle。

[4.  黄金之风 from XYD](https://xinyoudui.com/ac/contest/74700A3800008870671CA76/problem/9899)

从小到大转移。同行列移动无需代价，可以记录行列最优结果。

补一下以前的一道题。

[P7952 【✗✓OI R1】 天动万象 from Luogu](https://www.luogu.com.cn/problem/P7952)

对每个纯链维护平衡树，中间有合并，细节有点多。

## 9月5日

[P11362 【NOIP2024】 遗失的赋值 from Luogu](https://www.luogu.com.cn/problem/P11362)

两个钦定数字之间是独立的，统计一下贡献就行。

复习一下SAM和动态DP。

[#2102. 「TJOI2015」弦论 from LOJ](https://loj.ac/p/2102)

DP出过每个节点的路径条数，查询即搜索。

[#2955. 「NOIP2018」保卫王国 from LOJ](https://loj.ac/p/2955)

比较板的动态DP。但这是我第一次写全局平衡二叉树做法。

## 9月6日

模拟赛。

