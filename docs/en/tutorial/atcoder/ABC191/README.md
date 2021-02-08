# AtCoder Beginner Contest 191 Editorial

## Problem A -  [Vanishing Pitch](https://atcoder.jp/contests/abc191/tasks/abc191_a)

To avoid dealing with floats, we can calculate the invisible range of distance instead. If $D$ falls within this range, then Aoki cannot hit the ball.

- Time complexity is $\mathcal{O}(1)$.
- Space complexity is $\mathcal{O}(1)$.

::: details Code (Rust)

<<<@/docs/tutorial/atcoder/ABC191/src/a.rs

:::

## Problem B - [Remove It](https://atcoder.jp/contests/abc191/tasks/abc191_b)

Just perform the simulation. Actually we even do not need an array. We can just read from the stream and process the numbers one by one.

- Time complexity is $\mathcal{O}(N)$.
- Space complexity is $\mathcal{O}(N)$ or $\mathcal{O}(1)$ if we read the numbers one by one.

::: details Code (Rust)

<<<@/docs/tutorial/atcoder/ABC191/src/b.rs

:::

## Problem C - [Digital Graffiti](https://atcoder.jp/contests/abc191/tasks/abc191_c)

It would be a lot easier if we could explicitly draw the outline. How can we achive that?

My trick here is to extend the board, so that 

```
....
.#..
.##.
....
```

becomes

```
.........
.........
..###....
..###....
..#####..
..#####..
..#####..
.........
.........
```

A big advantage is that in the new pattern, each side of the polygon has a minimum length of $3$. As a result, we just need to count the number of turning points to get the number of sides. They must equal!

How do we find turing points?

We define a `#` cell which is in touch with a `.` cell in any of the 8 directions (diagonals included) as an **outer cell**. These cells form the outline of the pattern. Of course, a turning point must be an **outer cell**.

We can observe that all turning points must form a right angle with two of its 4-direction neighbors, which should also be **outer cell**s, Thus we can find all the turning points by checking if they can form a right angle.

- Time complexity is $\mathcal{O}(HW)$.
- Space complexity is $\mathcal{O}(HW)$.

::: details Code (Rust)

<<<@/docs/tutorial/atcoder/ABC191/src/c.rs

:::

## Problem D - [Circle Lattice Points](https://atcoder.jp/contests/abc191/tasks/abc191_d)

The idea is easy to come up with. We can do a sweeping line either along the $x$-axis or the $y$-axis.

Supposing that we sweep along the $y$-axis from the lowest integer point to the highest integer point. We can easily find the two intersections of our current line $y=y_0$ and the circle, which should be $(X-\sqrt{R^2-(Y-y_0)^2}, y_0)$ and $(X+\sqrt{R^2+(Y-y_0)^2},y_0)$. We can then find the number of interger points between these two points.

However, the floating point precision is a bit annoying. Many contestants got **AC** on most test cases but could not pass the rest due to this issue.

My solution is to avoid the usage of floats from the beginning. Since there are at most $4$ digits after the decimal point, we can multiply all the numbers by $10000$ and they would fit in `i32`, which means their squares can fit in `i64`.

An offset can be used to further avoid negative number divisions, which is also a source of error.

Finally, instead of calculating the radius, we can use binary search to find the leftmost and the rightmost integer points.

- Time complexity is $\mathcal{O}(R\log R)$.
- Space complexity is $\mathcal{O}(1)$.

::: details Code (Rust)

<<<@/docs/tutorial/atcoder/ABC191/src/d.rs

:::

## Problem E - [Come Back Quickly](https://atcoder.jp/contests/abc191/tasks/abc191_e)

Problem E proved to be much easier than Problem D. We can solve it by running a Dijkstra from each town.

- Time complexity is $\mathcal{O}(N^2\log M)$.
- Space complexity is $\mathcal{O}(N+M)$.

::: details Code (Rust)

<<<@/docs/tutorial/atcoder/ABC191/src/e.rs

:::

## Problem F - [GCD or MIN](https://atcoder.jp/contests/abc191/tasks/abc191_f)

An important observation is $\gcd(x,y)\leq\min(x,y)$. So the minimum of all numbers $\min{A_i}$ proves to be the maximum answer we could get.

Since all the possible answers must be a factor of some number in the array, we can find the factors of every number within $\mathcal{O}(N\sqrt{\max{A_i}})$ iterations.

Not all factors can be the final answer. Supposing that a factor $k<\min{A_i}$ can be the final answer,

- $k$ must be a factor of some number $A_i$.
- $k$ comes from a series $\gcd$ operations, e.g., $\gcd(A_{p_1},A_{p_2},\dots)$. $k$ cannot be $A_i$ itself since we have $k<\min{A_i}$.
- Since the order of $\gcd$ operations does not matter, the first time we meet $k$, supposing that we are dealing with the number $A_i$, we can set $memo[k]$ to $A_i$. Note that here we have $memo[k]\geq k$.
- Our goal is to get $k$ in the end ($memo[k]=k$), so each time we have the chance to perform a $\gcd$ operation (meaning that $k$ is also a factor of some other number $A_j$), we should perform the $\gcd$ operation to reduce the number $memo[k]$ to $\gcd(memo[k],A_j)$. Since both $memo[k]$ and $A_j$ can be divided by $k$, it is assured that $memo[k]$ can be divided by $k$. We do the $\gcd$ operation whenever possible because $\gcd(x,y)\leq\min(x,y)$, and we want to reduce the value $memo[k]$.

After processing all the numbers, we check our $memo$ and count for how many factors $memo[k]=k$ holds.

And the final answer would be that count plus $1$ (by using $\min$ operations only).

- Time complexity is $\mathcal{O}(N\sqrt{\max{A_i}}\log{\max{A_i}})$.
- Space complexity is $\mathcal{O}(Nd)$, where $d$ is the maximum number of factors of a single number.

::: details Code (C++)

<<<@/docs/tutorial/atcoder/ABC191/src/f.cpp

:::

::: details Code (Rust)

<<<@/docs/tutorial/atcoder/ABC191/src/f.rs

:::

<Utterances />