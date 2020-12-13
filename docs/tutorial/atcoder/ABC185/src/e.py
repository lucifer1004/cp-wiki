n, m = map(int, input().split())
a = list(map(int, input().split()))
b = list(map(int, input().split()))
dp = [[0 for _ in range(m + 1)] for _ in range(n + 1)]
for i in range(n + 1):
    for j in range(m + 1):
        if i == 0 and j == 0:
            continue
        dp[i][j] = int(1e6)
        if i > 0:
            dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1)
        if j > 0:
            dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1)
        if i > 0 and j > 0:
            extra = -1 if a[i - 1] == b[j - 1] else 0
            dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + 1 + extra)
print(dp[n][m])
