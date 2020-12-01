def read_int():
    return int(input())


t = read_int()
for case_num in range(t):
    x = read_int()
    lo = 1
    hi = x
    found = False
    while lo <= hi:
        mid = (lo + hi) >> 1
        dist = mid * (mid + 1) // 2
        if dist == x:
            found = True
            print(mid)
            break
        if dist < x:
            lo = mid + 1
        else:
            hi = mid - 1
    if not found:
        if lo * (lo + 1) // 2 - x >= 2:
            print(lo)
        else:
            print(lo + 1)
