n, m = map(int, input().split())
a = [] if m == 0 else list(map(int, input().split()))
a.sort()
if m == 0:
    print(1)
else:
    seg = []
    if a[0] != 1:
        seg.append(a[0] - 1)
    if a[-1] != n:
        seg.append(n - a[-1])
    for i in range(m - 1):
        if a[i + 1] - a[i] > 1:
            seg.append(a[i + 1] - a[i] - 1)
    if len(seg) == 0:
        print(0)
    else:
        shortest = min(seg)
        print(sum((si - 1) // shortest + 1 for si in seg))
