n = int(input())
a = list(map(int, input().split()))
a.sort()
r = sum(a)
ans = 0
l = 0
for i in range(n):
    r -= a[i]
    ans += r - (n - 1 - i) * a[i] + i * a[i] - l
    l += a[i]
print(ans // 2)
