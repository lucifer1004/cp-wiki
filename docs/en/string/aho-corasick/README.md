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

::: details Hint 3

Consider two types of transitions:

- Discard the current digit, and increase the cost by $1$.
- Keep the current digit, and move on the Aho-Corasick automaton. This transition is prohibited if the target position is marked.

:::

::: details Code (C++)

<<<@/docs/string/aho-corasick/src/CF1400F.cpp

:::
