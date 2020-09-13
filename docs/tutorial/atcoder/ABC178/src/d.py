mod = 1000000007


def fexp(x, y):
    ans = 1
    while y > 0:
        if y % 2 == 1:
            ans = ans * x % mod
        x = x * x % mod
        y //= 2
    return ans


fac = [1]
rev = [1]

for i in range(1, 2006):
    fac.append(fac[-1] * i % mod)
    rev.append(fexp(fac[-1], mod - 2))


def C(n, k):
    if n < k:
        return 0
    return fac[n] * rev[k] % mod * rev[n - k] % mod


def distribute(n, m):
    return C(n - 1, m - 1)


n = int(input())
if n < 3:
    print(0)
else:
    ans = 0
    parts = 1
    while n - parts * 2 >= 0:
        rest = n - parts * 2
        ans += distribute(rest, parts)
        ans %= mod
        parts += 1
    print(ans)
