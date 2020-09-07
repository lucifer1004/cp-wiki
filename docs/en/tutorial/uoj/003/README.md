# UOJ003 - Magic Forest

[Submit Your Solution](http://uoj.ac/problem/3)

::: tip

This problem is from NOI 2014.

:::

## Description

You want to visit a hermit living in the Magic Forest. The forest can be seen as an undirected graph which has $n$ ($2\leq n\leq5\times10^4$) nodes and $m$ ($0\leq m\leq10^5$) edges. Initially, you are at node $1$ while the hermit lives at node $n$.

There are some monsters living in the Magic Forest, too. When someone passes an edge, the monsters will attack him. Luckily, you can take some guarding sprites with you when you depart. There are two types of sprites, type-A and type-B, and you can take as many as you want.

Every edge $e_i$ has two values $a_i$ and $b_i$, which means that you need at least $a_i$ type-A sprites and $b_i$ type-B sprites to pass this edge. What is the minimal number of sprites you will need to take, if you choose the route optimally?

## Input

- The first line contains two integers, the number of nodes $n$, and the number of edges $m$.
- The following $m$ lines each contain four integers $x_i,y_i,a_i,b_i$, describing an undirected edge between $x_i$ and $y_i$, which requires at least $a_i$ type-A sprites and at least $b_i$ type-B sprites.

Note that there might be multiple edges and self loops.

## Output

One integer, the minimal number of sprites required to visit the hermit. If you can never reach the hermit, output $-1$ instead.

## Samples

### Input 1

```txt
4 5
1 2 19 1
2 3 8 12
2 4 12 15
1 3 17 8
3 4 1 17
```

### Output 1

```txt
32
```

### Sample Explanation

- Choosing $1\rightarrow2\rightarrow4$ requires $19+15=34$ sprites.
- Choosing $1\rightarrow3\rightarrow4$ requires $17+17=34$ sprites.
- Choosing $1\rightarrow2\rightarrow3\rightarrow4$ requires $19+17=36$ sprites.
- Choosing $1\rightarrow3\rightarrow2\rightarrow4$ requires $17+15=32$ sprites.

So at least $32$ sprites are needed.

## Tutorial

<Utterances />
