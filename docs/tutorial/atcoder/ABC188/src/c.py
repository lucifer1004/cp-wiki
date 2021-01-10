n = int(input())
a = list(map(int, input().split()))
half = 1 << (n - 1)
left_win = 0
for i in range(half):
    if a[i] > a[left_win]:
        left_win = i
right_win = half
for i in range(half, 1 << n):
    if a[i] > a[right_win]:
        right_win = i
if a[left_win] > a[right_win]:
    print(right_win + 1)
else:
    print(left_win + 1)
