# UOJ002 - Hard to Get Up

[Submit Your Solution](http://uoj.ac/problem/2)

::: tip

This problem is from NOI 2014.

:::

## Description

A warrior is to slay an evil dragon which hinders people from getting up easily. The dragon has $n$ gates defending it from attacks. On each gate there is an operation $op$ and a parameter $t$. $op$ can be $\text{OR}$, $\text{XOR}$ or $\text{AND}$，while $t$ is a non-negative integer. 

The warrior needs to pass the gates one by one. If his attack power is $x$ before passing the gate, then his attack damage becomes $x\ op\ t$ after passing it. The damage taken by the dragon is the final result after all $m$ operations.

The warrior can freely choose his attack power from $[0,m]$, which must be an integer. However, the intermediate results and the final damage can be larger than $m$. Please help the warrior calculate the highest damage he can make if he chooses his attack power optimally.

## Input

In the first line, there are two integers $n$ ($2\leq n\leq10^5$) and $m$ ($2\leq m<2^{30}$), representing the number of gates and the upper bound of the warrior's attack power.

The following $n$ lines each contain a string $op$ and a non-negative integer $t$ ($0\leq t<2^{30}$) separated by a whitespace. $op$ is one of $\text{OR}$, $\text{XOR}$ or $\text{AND}$, and $t$ is the corresponding parameter.

## Output

An integer, the highest damage the warrior can make.

## Samples

### Input 1

```txt
3 10
AND 5
OR 6
XOR 7
```

### Output 1

```txt
1
```

### Sample Explanation

If the warrior chooses $4$ as his initial attack power, then we have 

$$
\begin{aligned}
4\text{ AND }5=4 \\
4\text{ OR }6=6 \\
6\text{ XOR }7=1
\end{aligned}
$$

So the final damage is $1$.

Similarly, we can calculate that the final damage is $0$ if the initial attack power is $1,3,5,7,9$ and $1$ if the initial attack power is $0,2,4,6,8,10$. So the highest damage the warrior can make is $10$.

## Tutorial

::: details Hint 1

Consider each bit separately.

:::

::: details Hint 2

If for a set bit of $m$, it is not worse to choose $0$, we should choose $0$. More than that, we are free to choose from $0$ and $1$ for the bits following. 

:::

::: details Code (C++)

<<<@/docs/en/tutorial/uoj/002/src/002.cpp

:::

<Utterances />
