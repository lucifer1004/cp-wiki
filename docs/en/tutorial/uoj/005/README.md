# UOJ005 - Zoo

[Submit Your Solution](http://uoj.ac/problem/5)

::: tip

This problem is from NOI 2014.

:::

## Description

The zoo director is teaching animals the KMP algorithm. In KMP, we have $next[i]$ meaning the length of the longest substring of $s[1..i]$ which is both prefix and suffix of $s[1..i]$ and is not $s[1..i]$ itself. The zoo director is not satisfied with that and further asks animals to find $num[i]$, which is the number of substrings of $s[1..i]$ which are both prefix and suffix of $s[1..i]$, and the prefix and the suffix do not overlap. Can you write a program for that to help the animals?

You only need to output $\prod_{i=1}^L(num[i]+1)\mod(10^9+7)$.

## Input

- The first line contains one integer $t$ ($t\leq5$), number of test cases.
- The following $t$ lines each contain a string $s$ ($|s|\leq10^6$) which consists of lower case letters only.

## Output

$t$ lines for $t$ test cases. Every line contains one integer, the result $\prod_{i=1}^L(num[i]+1)\mod(10^9+7)$ for string $s$ in this test case.

## Samples

### Input 1

```txt
3
aaaaa
ab
abcababc
```

### Output 1

```txt
36
1
32
```

## Tutorial

::: details Hint 1

Use Z-Algorithm.

:::

::: details Hint 2

Each $z[i]$ (we need to constraint it below $i$ since overlapping is not allowed) will contribute $1$ to $num[i\dots i+z[i]-1]$. So we can use a difference array and then get the values of each $num[i]$.

:::

::: details Code (C++)

<<<@/docs/en/tutorial/uoj/005/src/005.cpp

:::

<Utterances />
