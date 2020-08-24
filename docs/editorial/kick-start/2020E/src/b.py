t = int(input())
for case_num in range(1, t + 1):
    n, a, b, c = map(int, input().split())
    if a + b - c > n or (a == b and a == c and c < min(n, 2)):
        print("Case #{}: IMPOSSIBLE".format(case_num))
        continue
    rev = False
    if a > b:
        tmp = a
        a = b
        b = tmp
        rev = True
    arrangement = [n - 1] * (a - c) + [n] + [1] * (n - (a + b - c)) + \
        [n] * (c - 1) + [n - 1] * (b - c)
    if rev:
        arrangement = arrangement[::-1]
    ans = ' '.join(map(str, arrangement))
    print("Case #{}: {}".format(case_num, ans))
