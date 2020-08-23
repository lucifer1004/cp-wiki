# AtCoder Beginner Contest 174 题解

## Problem A - Air Conditioner

过水，略。

## Problem B - Distance

过水，略。

## Problem C - Repsept

暴力，略。

## Problem D - Alter Altar

### 题目描述

一个`R`-`W`串，可以进行两种操作：1. 交换任意两个字符，2. 改变任意一个字符。问最少操作几次，可以使得串中不包含`WR`？

### 题解

可以发现，使用操作1总不劣于操作2的。最终需要把串变为`R...RW...W`的形式，所以先统计`R`的个数$r$，然后统计前$r$个字符中`R`的个数$r'$，最后的结果就是$\Delta r=r-r'$。

## Problem E - Logs

### 题目描述

有$N$根木条，每条长为$L_i$，最多锯$K$次，问锯完后最长的木条最短有多长（结果进位为整数）。

### 题解

经典二分。二分查找最后的答案，判断所需要的次数是否超过$K$次。

::: spoiler 参考代码（C++）

<<< @/docs/editorial/atcoder/ABC174/src/e.cpp

:::

## Problem F - Range Set Query

### 题目描述

给定数组$A$，进行$Q$次询问，每次需要回答$[L_i,R_i]$区间内不同数字的个数。

### 题解

经典题。离线做法是按查询区间右端点排序然后依次处理，过程中用树状数组记录和更新当前状态。同一个数字，只有最后一次出现是有效的。

::: spoiler 参考代码（C++）

<<< @/docs/editorial/atcoder/ABC174/src/f.cpp

:::

<Utterances />
