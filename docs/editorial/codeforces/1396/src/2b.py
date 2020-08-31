from sys import stdin, stdout


def read_int():
    return int(stdin.readline().strip())


def read_ints():
    return map(int, stdin.readline().strip().split(' '))


n = read_int()
a = list(read_ints())
a.sort()
s = sum(a)
cost = s - n
j = 2
while pow(j, n - 1) <= s * 2:
    b = [1]
    for k in range(n - 1):
        b.append(b[-1] * j)
    tot = sum([abs(a[i] - b[i]) for i in range(n)])
    cost = min(cost, tot)
    j += 1
print(cost)
