n, x = map(int, input().split())
s = input()
for c in s:
    if c == 'o':
        x += 1
    else:
        x = max(0, x - 1)
print(x)
