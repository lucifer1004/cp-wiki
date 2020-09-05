s = input()
t = input()
ls = len(s)
lt = len(t)
ans = lt
for i in range(ls - lt + 1):
    diff = 0
    for j in range(lt):
        if s[i + j] != t[j]:
            diff += 1
    ans = min(ans, diff)
print(ans)
