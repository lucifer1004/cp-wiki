def exgcd(a, b):
    s = 0
    olds = 1
    t = 1
    oldt = 0
    r = b
    oldr = a
    while r:
        q = oldr // r
        oldr, r = r, oldr-q*r
        olds, s = s, olds-q*s
        oldt, t = t, oldt-q*t
    return oldr, olds, oldt


t = int(input())
for _ in range(t):
    n, s, k = map(int, input().split())
    g, a, b = exgcd(n, k)
    if s % g != 0:
        print(-1)
    else:
        a *= s // g
        b *= s // g
        lcm = n * k // g
        print(((a * n - s) % lcm + lcm) % lcm // k)
