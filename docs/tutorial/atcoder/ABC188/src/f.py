from collections import deque

X, Y = map(int, input().split())
if X >= Y:
    print(X - Y)
else:
    ans = Y - X
    dq = deque([(Y, 0)])
    vis = set([Y])
    while dq:
        u, d = dq.popleft()
        if d >= ans:
            break
        ans = min(ans, d + abs(u - X))
        if u <= X:
            continue
        if u % 2 == 0:
            if u // 2 not in vis:
                vis.add(u // 2)
                dq.append((u // 2, d + 1))
        else:
            if u + 1 not in vis:
                vis.add(u + 1)
                dq.append((u + 1, d + 1))
            if u - 1 not in vis:
                vis.add(u - 1)
                dq.append((u - 1, d + 1))
    print(ans)
