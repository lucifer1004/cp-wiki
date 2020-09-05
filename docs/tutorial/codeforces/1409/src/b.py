import sys


def read_int():
    return int(sys.stdin.readline())


def read_ints():
    return map(int, sys.stdin.readline().split(' '))


t = read_int()
for case_num in range(t):
    a, b, x, y, n = read_ints()
    n1 = min(n, a - x)
    ans = (a - n1) * (b - min(n - n1, b - y))
    n2 = min(n, b - y)
    ans = min(ans, (b - n2) * (a - min(n - n2, a - x)))
    print(ans)
