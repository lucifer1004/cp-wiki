t = int(input())
for case_num in range(1, t + 1):
    n = int(input())
    a = list(map(int, input().split()))
    ans = 2
    cnt = 2
    for i in range(2, n):
        if a[i] - a[i - 1] == a[i - 1] - a[i - 2]:
            cnt += 1
        else:
            cnt = 2
        ans = max(ans, cnt)
    print("Case #{}: {}".format(case_num, ans))
