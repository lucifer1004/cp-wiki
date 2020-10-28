def read_int():
    return int(input())


def read_ints():
    return map(int, input().split(' '))


inf = int(1e9)
t = read_int()
for case_num in range(t):
    n = read_int()
    a = list(read_ints())
    a.sort()
    dp = [0 for _ in range(n * 2 + 1)]
    for t in a:
        ndp = [inf for _ in range(n * 2 + 1)]
        lo = inf
        for i in range(n * 2):
            lo = min(lo, dp[i])
            ndp[i + 1] = min(ndp[i + 1], lo + abs(i + 1 - t))
        dp = ndp
    print(min(dp))
