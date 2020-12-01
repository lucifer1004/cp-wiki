def read_int():
    return int(input())


def read_ints():
    return map(int, input().split(' '))


t = read_int()
for case_num in range(t):
    n, x = read_ints()
    a = list(read_ints())
    ans = 0
    error = False
    pos = 0
    while pos < n:
        num = a[pos]
        if pos + 1 < n and num > a[pos + 1]:
            if x <= a[pos + 1]:
                while pos > 0 and a[pos - 1] > x:
                    pos -= 1
                if a[pos] > x:
                    a[pos], x = x, a[pos]
                    ans += 1
                else:
                    error = True
                    break
            else:
                error = True
                break
        pos += 1
    print(-1 if error else ans)
