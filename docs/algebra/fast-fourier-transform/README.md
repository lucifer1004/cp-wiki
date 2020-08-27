# 快速傅里叶变换

快速傅里叶变换（Fast Fourier Transform, FTT）在CP中最主要的应用是计算多项式乘法。

## 多项式的系数表示和点值表示

假设$f(x)$为$x$的$n$阶多项式，则其可以表示为：

$$f(x)=\sum_{i=0}^na_ix^i$$

这里的$n+1$个系数$\{a_0,a_1,\cdots,a_n\}$就称为多项式$f(x)$的系数表示。

另一方面，我们也可以把$f(x)$看成是一个关于$x$的函数，我们可以取$n+1$个不同的$x_i$，用$\{(x_0,f(x_0)),(x_1,f(x_1)),\cdots(x_n,f(x_n))\}$这$n+1$个数值对来唯一确定$f(x)$，这种表示形式就称为多项式$f(x)$的点值表示。

## 点值表示与多项式乘法的关系

假设我们现在要求的是$F(x)=f(x)\cdot g(x)$，如果我们已知$f(x)$和$g(x)$的点值表示，那么我们可以非常容易地得到$F(x)$的点值表示为

$$\{(x_0,f(x_0)g(x_0)),(x_1,f(x_1)g(x_1)),\cdots,(x_n,f(x_n)g(x_n))\}$$

注意这里的$n$实际上要取到$f(x)$和$g(x)$的阶数之和。

现在的关键问题是，如何快速将这一点值表示转换为系数表示。

## FFT的实现

为了解决这一问题，我们首先考虑其逆问题，也即：如何从系数表示快速计算点值表示。

### FFT

暴力计算$n$对点值的总时间复杂度为$O(n^2)$。如何优化呢？我们希望我们选择的$n$个$x_i$之间存在一定的关系，使得我们可以复用$x_i^k$的计算结果。那么，应该如何选择呢？

前人的经验告诉我们，可以选择单位复根$\omega_n^i$。它有三个重要的性质：

$$\omega_n^n=1$$

$$\omega_n^i=\omega_{2n}^{2i}$$

$$\omega_{2n}^{n+i}=-\omega_{2n}^i$$

利用上述这三个性质，我们可以实现计算过程的简化。

不妨考虑一个最高阶为7阶的多项式

$$f(x)=a_0+a_1x^1+a_2x^2+a_3x^3+a_4x^4+a_5x^5+a_6x^6+a_7x^7$$

可以把奇偶项分别处理

$$
\begin{aligned}
  f(x) &=(a_0+a_2x^2+a_4x^4+a_6x^6)+x(a_1+a_3x^2+a_5x^4+a_7x^6) \\
  &=G(x^2)+xH(x^2)
\end{aligned}
$$

从而

$$
\text{DFT}(f(x))=\text{DFT}(G(x^2))+x\text{DFT}(H(x^2))
$$

这时把单位复根$\omega_n^k$（$k<n/2$）代入，可以得到

$$
\begin{aligned}
\text{DFT}(f(\omega_n^k))&=\text{DFT}(G(\omega_n^{2k}))+\omega_n^k\text{DFT}(H(\omega_n^{2k})) \\
&=\text{DFT}(G(\omega_{n/2}^k))+\omega_n^k\text{DFT}(H(\omega_{n/2}^k))
\end{aligned}
$$

而另一方面，代入$\omega_n^{k+n/2}$可以得到

$$
\begin{aligned}
\text{DFT}(f(\omega_n^{k+n/2}))&=\text{DFT}(G(\omega_n^{2k+n}))+\omega_n^k\text{DFT}(H(\omega_n^{2k+n})) \\
&=\text{DFT}(G(\omega_{n/2}^{k+n/2}))+\omega_n^{k+n/2}\text{DFT}(H(\omega_{n/2}^{k+n/2})) \\
&=\text{DFT}(G(\omega_{n/2}^k))-\omega_n^k\text{DFT}(H(\omega_{n/2}^k))
\end{aligned}
$$

因此，我们只要求得$\text{DFT}(G(\omega_{n/2}^k))$和$\text{DFT}(H(\omega_{n/2}^k))$，就可以同时求得$\text{DFT}(f(\omega_n^k))$和$\text{DFT}(f(\omega_n^{k+n/2}))$，这样就把问题规模缩小了一半。

使用同样的方法对$\text{DFT}(G(\omega_{n/2}^k))$和$\text{DFT}(H(\omega_{n/2}^k))$进行递归求解，我们有

$$T(n)=2T(n/2)$$

可知总的时间复杂度为$O(n\log n)$。

在这一过程中，我们默认$n/2$总是整数，因此我们需要$n=2^k$。所以在计算之前，我们要先对系数补0，使得总的项数变为2的幂次。

### 逆FFT

将FFT的运算过程看做一个矩阵乘法，逆FFT，也即从点值表示求取系数表示的过程，可以视为左乘逆矩阵。在点值表示的点选取为$\omega_n^k$时，FFT矩阵$\mathbb{A}(\omega_n^k)$的逆矩阵恰好为$\frac{1}{n}\mathbb{A}(\omega_n^{-k})$，因此可以复用FFT的计算过程，只需要加上一个标志变量来表示当前是在进行FFT还是IFFT。

### 模板题：[洛谷 P3803 - 多项式乘法（FFT）](https://www.luogu.com.cn/problem/P3803)

下面给出了本题的递归实现。

::: details 参考代码（C++）

<<< @/docs/algebra/fast-fourier-transform/src/LG-P3803-Recursion.cpp

:::

上述递归方法的常数较大，不能通过洛谷P3803的最后两个测试点。

为了改写非递归方法，我们引入蝴蝶变换的概念。

### 蝴蝶变换

继续使用前面的例子，经过第一步分治，将原来的系数分为两组：
$$\{a_0,a_2,a_4,a_6\},\{a_1,a_3,a_5,a_7\}$$

继续进行第二步分治，得到四组系数：
$$\{a_0,a_4\},\{a_2,a_6\},\{a_1,a_5\},\{a_3,a_7\}$$

最后一步分治，得到八组系数：
$$\{a_0\},\{a_4\},\{a_2\},\{a_6\},\{a_1\},\{a_5\},\{a_3\},\{a_7\}$$

所谓蝴蝶变换，指的就是从${a_0,a_1,\cdots,a_{n-1}}$这一原始系数序列，变换得到最后一步分治后的系数序列。

观察后可以发现，在蝴蝶变换的最终结果中，系数下标的二进制表示恰好是其所在位置二进制表示的逆序，因此，可以利用这一规律来求取蝴蝶变换的结果。

直接利用规律来计算的复杂度是$O(n\log n)$，如果从小到大递推实现，复杂度则为$O(n)$。

### FFT的非递归实现

下面给出了洛谷P3803的非递归实现。

::: details 参考代码（C++）

<<< @/docs/algebra/fast-fourier-transform/src/LG-P3803-Iteration.cpp

:::

::: details 参考代码（Kotlin）

<<< @/docs/algebra/fast-fourier-transform/src/LG-P3803-Iteration.kt

:::

由于语言差异，Kotlin版本并不能通过洛谷的测试。

## 学习资源

### [Matters Computational](https://www.springer.com/gp/book/9783642147630)

- 第二十一章 快速傅里叶变换

## 练习题

裸FFT并不可怕，本身FFT的码量并不算大，背一背也不是多大的事，关键是如何看出一道题目是FFT。

### [SPOJ - ADAMATCH](https://www.spoj.com/problems/ADAMATCH/)

如果暴力枚举子串，时间复杂度为$O(|r|^2)$，显然不行。如何降低复杂度呢？

::: details 提示一

首先考虑字母`'A'`。不妨把字符串为`'A'`的位置设为$1$，其余位置设为$0$。看起来似乎可以进行多项式乘法，但乘法的结果似乎没有明显的意义。

:::

::: details 提示二

如果把`r`串逆序呢？看看此时乘积的每一项有怎样的含义。

:::

::: details 参考代码（C++）

<<< @/docs/algebra/fast-fourier-transform/src/SPOJ-ADAMATCH.cpp

:::

### [SPOJ - TSUM](https://www.spoj.com/problems/TSUM/)

如果暴力枚举，时间复杂度为$O(n^3)$，显然不行。如何降低复杂度呢？

::: details 提示一

加法可以变为多项式的乘法。

:::

::: details 提示二

如何去除包含重复元素的项？

:::

::: details 参考代码（C++）

<<< @/docs/algebra/fast-fourier-transform/src/SPOJ-TSUM.cpp

:::

<Utterances />
