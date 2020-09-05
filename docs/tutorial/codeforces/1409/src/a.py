def read_int():
    return int(input())


def read_ints():
    return map(int, input().split(' '))


t = read_int()
for case_num in range(t):
    a, b = read_ints()
    delta = abs(a - b)
    print(delta // 10 + (1 if delta % 10 != 0 else 0))
