n = int(input())
a = list(map(int, input().split()))
hi = 0
ans = 0
for i in range(2, max(a) + 1):
    cnt = 0
    for j in a:
        if j % i == 0:
            cnt += 1
    if cnt > hi:
        hi = cnt
        ans = i
print(ans)
