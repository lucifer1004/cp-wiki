# Google Kick Start 2022 Round A 题解

## Problem A - [Speed Typing](https://codingcompetitions.withgoogle.com/kickstart/round/00000000008cb33e/00000000009e7021)

### 方法一：单指针

我们用单指针指向目标串的当前待匹配位置，然后遍历原串。如果原串中的字符与当前待匹配的字符相同，则将指针后移。

如果最后完全匹配成功，答案就是原串和目标串的长度差。否则无解。

复杂度：

- 时间复杂度为$\mathcal{O}(|S|+|T|)$。
- 空间复杂度为$\mathcal{O}(1)$。

::: details 参考代码（C++）

<<< @/docs/tutorial/kick-start/2022A/src/a.cpp

:::

## Problem B - [Challenge Nine](https://codingcompetitions.withgoogle.com/kickstart/round/00000000008cb33e/00000000009e7997)

### 方法一：数学+贪心

我们知道能够一个数能被 9 整除，等价于其各位之和也能被 9 整除。因此我们首先可以找出需要填补的那个数字。如果原本已经能被 9 整除，那么我们可以添加 0 也可以添加 9。为了让得到的新数字最小，我们显然应该添加 0。

对于具体的插入位置，我们可以贪心寻找：如果原数的某个位置比我们将要插入的这个数字大，那么我们将新数字插入在它前面的结果一定是最优的。

需要特别注意的是，如果要插入的数字是 0，我们不能将它放在开头，而只能放在第一个数字之后。

复杂度：

- 时间复杂度为$\mathcal{O}(N)$。
- 空间复杂度为$\mathcal{O}(N)$。

::: details 参考代码（C++）

<<< @/docs/tutorial/kick-start/2022A/src/b.cpp

:::

## Problem C - [Palindrome Free Strings](https://codingcompetitions.withgoogle.com/kickstart/round/00000000008cb33e/00000000009e762e)

### 方法一：动态规划

任何一个长度不小于 5 的回文串，必然包含一个长度为 5 的回文串，或包含一个长度为 6 的回文串。因此，我们首先找出所有长度为 5 和 6 的回文串并记录，然后在动态规划过程中维护当前最后六位的可能情况即可。

复杂度：

- 时间复杂度为$\mathcal{O}(2^K\cdot|S|)$，其中 $K=5$。
- 空间复杂度为$\mathcal{O}(2^K)$。

::: details 参考代码（C++）

<<< @/docs/tutorial/kick-start/2022A/src/c.cpp

:::

## Problem D - [Interesting Integers](https://codingcompetitions.withgoogle.com/kickstart/round/00000000008cb33e/00000000009e73ea)

### 方法一：数位动态规划

这种 $[L, R]$ 区间的问题，一般都可以转化为 $F(R)-F(L-1)$，本题中 $F(x)$ 表示 $[1,x]$ 范围内满足要求的数的个数。

下面考虑如何求 $F(x)$。这种问题的一般求解方法是数位 DP。

- 我们需要考察数位积与数位和的关系。在数位和一定的情况下，我们只需要记录当前数位积与数位和的最大公约数即可。
- 我们得到的数不能超过 $x$，这种有上限/下限的问题，可以用一个标志位来记录当前前缀是否与上限/下限相等，并分别处理。
- 前缀的零不参与乘积。所以我们还需要一个标志位来记录当前数是否已经大于零。

假设上限为 $N$ 位，显然数位和的最大值为 $9N$。那么，我们可以枚举数位和 $sum$，对于每一个确定的数位和，我们进行形如 $dp[p][s][z][same]$ 的四维 DP，其中：

- $p$ 表示当前数位积与目标数位和 $sum$ 的最大公约数
- $s$ 表示当前数位和
- $z$ 为当前是否大于零的标志位
- $same$ 为当前前缀是否与上限相等的标志位

之后，从上限的第一位到最后一位依次进行动态规划的计算即可。这一次动态规划对最后答案的贡献为 $dp[sum][sum][1][0]+dp[sum][sum][1][1]$。具体的转移可以参考代码。

复杂度：

- 时间复杂度为$\mathcal{O}(S^{5/2}\cdot ND)$，其中 $S\le9\times12=108$，$N$ 为上限的位数，$D=10$。
- 空间复杂度为$\mathcal{O}(S^2)$。

::: details 参考代码（C++）

<<< @/docs/tutorial/kick-start/2022A/src/d.cpp

:::

<Utterances />
