def read_int():
    return int(input())


def read_ints():
    return map(int, input().split(' '))


t = read_int()
for case_num in range(t):
    n = read_int()
    s = input()
    tot = 0
    for i in range(n - 1):
        if s[i] == s[i + 1]:
            tot += 1
    print((tot + 1) // 2)
