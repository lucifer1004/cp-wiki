import sys


def read_int():
    return int(sys.stdin.readline())


def read_ints():
    return map(int, sys.stdin.readline().split(' '))


t = read_int()
for case_num in range(t):
    n, s = read_ints()
    a = [0] + [int(i) for i in str(n)]
    ds = sum(a)
    cost = 0
    idx = len(a) - 1
    radix = 1
    while ds > s:
        if a[idx] > 0:
            cost += (10 - a[idx]) * radix
            ds -= a[idx]
            a[idx] = 0
            ds += 1
            a[idx - 1] += 1
            i = idx - 1
            while a[i] >= 10:
                a[i - 1] += 1
                a[i] -= 10
                ds -= 9
                i -= 1
        radix *= 10
        idx -= 1
    print(cost)
