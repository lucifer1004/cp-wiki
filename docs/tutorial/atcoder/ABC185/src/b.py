n, m, t = map(int, input().split())
last = 0
now = n
for _ in range(m):
    ai, bi = map(int, input().split())
    now -= ai - last
    if now <= 0:
        print('No')
        exit(0)
    now += bi - ai
    if now > n:
        now = n
    last = bi
now -= t - last
print('Yes' if now > 0 else 'No')
