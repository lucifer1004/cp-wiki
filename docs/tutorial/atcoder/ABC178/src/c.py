mod = 1000000007


def fexp(x, y):
    ans = 1
    while y > 0:
        if y % 2 == 1:
            ans = ans * x % mod
        x = x * x % mod
        y //= 2
    return ans


n = int(input())
ans = fexp(10, n) - 2 * fexp(9, n) + fexp(8, n)
ans %= mod
if ans < 0:
    ans += mod
print(ans)
