r1, c1 = map(int, input().split())
r2, c2 = map(int, input().split())
if r1 == r2 and c1 == c2:
    print(0)
elif r1 + c1 == r2 + c2 or r1 - c1 == r2 - c2 or abs(r1 - r2) + abs(c1 - c2) <= 3:
    print(1)
elif (r1 + c1 + r2 - c2) % 2 == 0:
    print(2)
else:
    for i in range(-3, 4):
        for j in range(-3, 4):
            if abs(i) + abs(j) > 3:
                continue
            r = r1 + i
            c = c1 + j
            if r + c == r2 + c2 or r - c == r2 - c2 or abs(r - r2) + abs(c - c2) <= 3:
                print(2)
                exit(0)
    print(3)
