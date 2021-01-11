# AtCoder Beginner Contest 188 Editorial

[Video Editorial](https://www.youtube.com/watch?v=AV8LJWgWL7I)

<iframe width="560" height="315" src="https://www.youtube.com/embed/AV8LJWgWL7I" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

## Problem A -  [Three-Point Shot](https://atcoder.jp/contests/abc188/tasks/abc188_a)

Check if $|X-Y|\leq2$.

Time complexity is $\mathcal{O}(1)$.

::: details Code (Python 3)

<<<@/docs/tutorial/atcoder/ABC188/src/a.py

:::

## Problem B - [Orthogonality](https://atcoder.jp/contests/abc188/tasks/abc188_b)

Just calculate the inner product,

Time complexity is $\mathcal{O}(N)$.

::: details Code (Python 3)

<<<@/docs/tutorial/atcoder/ABC188/src/b.py

:::

## Problem C - [ABC Tournament](https://atcoder.jp/contests/abc188/tasks/abc188_c)

Find the maximum of the lower half and the upper half, and compare them. The index of the smaller value is the answer we need.

Time complexity is $\mathcal{O}(2^N)$.

::: details Code (Python)

<<<@/docs/tutorial/atcoder/ABC188/src/c.py

:::

## Problem D - [Snuke Prime](https://atcoder.jp/contests/abc188/tasks/abc188_d)

:::tip

Editorial for this problem has been completely **rewritten**.

:::

Consider at first we have an infinite time span $[0,+\infty)$. The services will split the span into several non-overlapping segments. For example, if we have servcies $[1,4]$ and $[3,8]$, the final segments would be (note that we discard the leftmost segment, which should be $[0,0]$ in this case):

$$
[1,2],[3,4],[5,8],[9,+\infty)
$$

Which can also be seen as:

$$
[1,3),[3,5),[5,9),[9,+\infty)
$$

 To represent these segments, we only need their left endpoints, that is, $1,3,5,9$. And these left endpoints come from either $a_i$ or $b_i+1$. This is because only the start or the end of a service will make a difference. A service $[a_i,b_i]$ can also be seen as $[a_i,b_i+1)$, in which $b_i+1$ is the first day that is not included, which means it is a start of a new segment. On the $a_i$-th day, the total cost will increase by $c_i$, while on the $b_i+1$-th day, the total cost will decrease by $c_i$.

After we get the segments, we need to calculate the cost for each segment, and compare it with $C$, the price of the subscription. The time span of a segment can be easily determined from the start of the current segment and the start of the next segment.

To deal with the segments, we have two choices.

1. (More overhead) We can discretize the endpoints and use a difference array to find the cost of each segment.
2. (Clearer) We can use a map to store the change happening to the total cost on each critical day ($a_i$ or $b_i+1$, which is the start endpoint of a segment), then handle the segments one by one.

Both methods have a time complexity of $\mathcal{O}(N\log N)$, since in both cases we need a sorted list of the timestamps.

::: details Code (C++, Discretization)

<<<@/docs/tutorial/atcoder/ABC188/src/d.cpp

:::

::: details Code (C++, Map)

<<<@/docs/tutorial/atcoder/ABC188/src/d2.cpp

:::

## Problem E - [Peddler](https://atcoder.jp/contests/abc188/tasks/abc188_e)

Do dynamic programming in a reverse order (from $N$ to $1$).

Time complexity is $\mathcal{O}(N+M)$.

::: details Code (C++)

<<<@/docs/tutorial/atcoder/ABC188/src/e.cpp

:::

## Problem F - [+1-1x2](https://atcoder.jp/contests/abc188/tasks/abc188_f)

- If $X\geq Y$, the answer if $X-Y$.
- Otherwise, we use BFS to solve this problem. To reduce the number of states, we start from $Y$ instead of $X$. For each current value $Y'$, first try updating the answer with $d+|Y'-X|$. If $Y'>X$, then further consider the following cases:
    - If $Y'$ is even, use $\div2$ (reverse of $\times2$)
    - Otherwise, use $+1$ or $-1$.
    Specially, if the steps of the front element is equal to or larger than the answer, we can stop the search.

::: details Code (Python)

<<<@/docs/tutorial/atcoder/ABC188/src/f.py

:::

<Utterances />
