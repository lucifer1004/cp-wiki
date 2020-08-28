# Aho-Corasick Automaton

## Exercises

### [Luogu P5357 - AC Automaton](https://www.luogu.com.cn/problem/P5357)

### [CF1400F - x-prime Substrings](https://codeforces.com/contest/1400/problem/F)

::: details Hint 1

We can enumerate all x-prime strings via DFS.

:::

::: details Hint 2

We can build an Aho-Corasick automaton with the generated strings.

:::

:::: details Hint 3

Consider two types of transitions:

- Discard the current digit, and increase the cost by $1$.
- Keep the current digit, and move on the Aho-Corasick automaton. This transition is prohibited if the target position is marked.

::: tip Tips

In this specific problem, no $x$-prime string is a suffix of another $x$-prime string, otherwise they will have different digit sums. In consequence, we do not need to follow `fail` pointers when moving on the automaton. However, do note that this is seldom the case, or you might get WA on other ACA problems (~~like me on [ADAJOBS](#spoj-ada-and-jobs)~~).

:::

::::

::: details Code (C++)

<<<@/docs/string/aho-corasick/src/CF1400F.cpp

:::

### [SPOJ - Ada and Jobs](https://www.spoj.com/problems/ADAJOBS/)

The challenge lies in that tasks are added dynamically, but we cannot afford reconstructing the whole automaton every time a new word is added.

::: details Hint 1

Store all operations offline. When constructing the automaton, assign every stop node a timestamp indicating its order. Meanwhile, store the number of words in the dictionary at the time a query is made. In this way, we only need to build the ACA once. During matching, we need to find a stop node whose timestamp is no larger than the timestamp of the query.

:::

::: details Hint 2

During matching, we do not need to go all the way up along the `fail` pointers. Instead, we can push down the timestamp during construction.

:::

::: details Code (C++)

<<<@/docs/string/aho-corasick/src/SPOJ-ADAJOBS.cpp

:::
