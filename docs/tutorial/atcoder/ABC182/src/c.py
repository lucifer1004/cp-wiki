s = input()
n = int(s)
if n % 3 == 0:
    print(0)
else:
    a = list(map(int, list(s)))
    c = [0] * 3
    for i in a:
        c[i % 3] += 1
    if c[n % 3] >= 1 and len(a) > 1:
        print(1)
    elif c[3 - n % 3] >= 2 and len(a) > 2:
        print(2)
    else:
        print(-1)
