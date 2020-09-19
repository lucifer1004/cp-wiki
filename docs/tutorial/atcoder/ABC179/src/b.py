n = int(input())
cnt = 0
ok = False
for _ in range(n):
    x, y = map(int, input().split())
    if x == y:
        cnt += 1
        if cnt >= 3:
            ok = True
    else:
        cnt = 0
print('Yes' if ok else 'No')
