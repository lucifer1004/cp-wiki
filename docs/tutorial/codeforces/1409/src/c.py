def read_int():
    return int(input())


def read_ints():
    return map(int, input().split(' '))


t = read_int()
for case_num in range(t):
    n, x, y = read_ints()
    d = y - x
    for i in range(n - 1, 0, -1):
        if d % i == 0:
            d //= i
            l = min(n - (i + 1), (x - 1) // d)
            ans = [x - l * d + i * d for i in range(n)]
            print(' '.join(map(str, ans)))
            break
