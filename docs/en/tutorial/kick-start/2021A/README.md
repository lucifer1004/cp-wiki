# Google Kick Start 2021 Round A Tutorial

## Problem A - [K-Goodness String](https://codingcompetitions.withgoogle.com/kickstart/round/0000000000436140/000000000068cca3)

First, we need to calculate the current score $K_c$. Since in one operation we can increase or decrease the score by $1$, the answer is $|K_c-K|$.

- Time complexity is $\mathcal{O}(|S|)$.
- Space complexity is $\mathcal{O}(1)$.

::: details Code (C++)

<<< @/docs/tutorial/kick-start/2021A/src/a.cpp

:::

## Problem B - [L Shaped Plots](https://codingcompetitions.withgoogle.com/kickstart/round/0000000000436140/000000000068c509)

First, we calculate the length of longest continuous $1$ starting from each cell via simple dynamic programming, namely, $W[i][j]$, $E[i][j]$, $N[i][j]$ and $S[i][j]$.

Then we enumerate each cell and count the L-shaped plots centering at the cell. There are four types of L-shaped plots considering the orientation:

- WN
- WS
- EN
- ES

And for each type, we need to consider which side to be the longer side.

- Time complexity is $\mathcal{O}(RC)$.
- Space complexity is $\mathcal{O}(RC)$.

::: details Code (C++)

<<< @/docs/tutorial/kick-start/2021A/src/b.cpp

:::

## Problem C - [Rabbit House](https://codingcompetitions.withgoogle.com/kickstart/round/0000000000436140/000000000068cb14)

Obviously, the highest cell should not be increased. With this insight, we can solve this problem in a Dijkstra-like manner.

We use a max-heap to store the cells to be processed. When we process a cell with height $h$, we need to ensure that all its neighbors are at least as high as $h-1$. If the height of any of its neighbors is increased, then we should enqueue that cell with the new height.

In the end, we accumulate the difference between each cell's final height and original height to get the answer.

- Time complexity is $\mathcal{O}(RC\log(RC))$.
- Space complexity is $\mathcal{O}(RC\log(RC))$.

::: details Code (C++)

<<< @/docs/tutorial/kick-start/2021A/src/c.cpp

:::

## Problem D - [Checksum](https://codingcompetitions.withgoogle.com/kickstart/round/0000000000436140/000000000068c2c3)

The hardest part of this problem is to recognize that it is actually a Minimum Spanning Tree (actually Maximum Spanning Tree, but they are equivalent) problem.

The first observation is that we can consider the known numbers to be unknown with a cost of $0$, and solve an equivalent problem in which all numbers are unknown.

The second observation is that we need to check exactly $(N-1)^2$ cells for a $N\times N$ matrix:

- If we check fewer than $(N-1)^2$, then at least $2N$ cells are unknown, while we can induce at most $2N-1$ cells.
- If we check more than $(N-1)^2$, then there is at least a row/column whose cells are all checked, which is unnecessary.

Now, instead of determining the $(N-1)^2$ cells to be checked, we try to determine the $2N-1$ cells which are induced. We want the sum of their costs to be maximized so that the sum of the checked cells can be minimized.

An insight is that, if we consider the $N$ rows and $N$ columns to be nodes, and the cells to be undirected edges (cell $(i,j)$ is considered to be an edge $r_i\leftrightarrow c_j$), then there will be exactly $2N$ nodes, while we need to choose $2N-1$ edges from all edges such that the sum of their weights is maximized. Very close to MST!

To confirm that it is exactly MST, we need to check whether loops are allowed. Since there are no edges that connect two rows or two columns, a loop must be in the form $r_0\leftrightarrow c_0\leftrightarrow r_1\leftrightarrow c_1\cdots\leftrightarrow r_0$. If a loop occurs, then all the rows and columns in this loop would have at least two unknown cells, which is unsolvable.

So we need to choose $2N-1$ edges in a graph with $2N$ nodes and loops are not allowed. Now we are confirmed that this is an MST.

The MST part is quite trivial, both Kruskal and Prim can work fluently.

- Time complexity is $\mathcal{O}(N^2\log N)$.
- Space complexity is $\mathcal{O}(N^2\log N)$.
 
::: details Code (C++)

<<< @/docs/tutorial/kick-start/2021A/src/d.cpp

:::

<Utterances />