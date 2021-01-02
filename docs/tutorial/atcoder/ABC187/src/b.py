n = int(input())
x = []
y = []
for _ in range(n):
    xi, yi = map(int, input().split())
    x.append(xi)
    y.append(yi)

ans = 0
for i in range(n):
    for j in range(i + 1, n):
        if abs(y[j] - y[i]) <= abs(x[j] - x[i]):
            ans += 1
print(ans)
