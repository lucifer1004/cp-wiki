def read_int():
    return int(input())


def read_ints():
    return map(int, input().split(' '))


def solve(x, y):
    xcost = x[1] - x[0] + x[3] - x[2]
    ycost = y[1] - y[0] + y[3] - y[2]
    xlo = max(0, x[2] - x[1])
    xhi = x[3] - x[0]
    ylo = max(0, y[2] - y[1])
    yhi = y[3] - y[0]
    ans = xcost + ycost
    if ylo > xhi:
        ans += 2 * (ylo - xhi)
    elif xlo > yhi:
        ans += 2 * (xlo - yhi)
    return ans


t = read_int()
for case_num in range(t):
    x = []
    y = []
    for i in range(4):
        xi, yi = read_ints()
        x.append((xi, i))
        y.append((yi, i))
    x.sort()
    y.sort()
    xl = set([x[0][1], x[1][1]])
    yl = set([y[0][1], y[1][1]])
    xs = list(map(lambda x: x[0], x))
    ys = list(map(lambda x: x[0], y))
    if len(xl.intersection(yl)) != 1:
        print(min(solve([xs[0], xs[2], xs[1], xs[3]], ys),
                  solve(xs, [ys[0], ys[2], ys[1], ys[3]])))
    else:
        print(solve(xs, ys))
