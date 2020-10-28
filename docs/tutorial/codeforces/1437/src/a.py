def read_int():
    return int(input())


def read_ints():
    return map(int, input().split(' '))


t = read_int()
for case_num in range(t):
    l, r = read_ints()
    print('YES' if l * 2 > r else 'NO')
