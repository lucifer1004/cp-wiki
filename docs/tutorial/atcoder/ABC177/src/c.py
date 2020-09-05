mod = int(1e9 + 7)


def fexp(x, y):
    ret = 1
    while y > 0:
        if y % 2 == 1:
            ret = ret * x % mod
        x = x * x % mod
        y = y // 2
    return ret


input()
a = list(map(int, input().split(' ')))
s = sum(a)
ans = 0
for i in a:
    ans = (ans + i * (s - i)) % mod
print(ans * fexp(2, mod - 2) % mod)
