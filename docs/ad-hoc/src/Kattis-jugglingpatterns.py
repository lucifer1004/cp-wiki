import sys

for raw_line in sys.stdin:
    line = raw_line.strip()
    tot = sum([int(i) for i in line])
    n = len(line)
    if tot % n != 0:
        print('{}: invalid # of balls'.format(line))
        continue
    balls = tot // n
    s = set()
    ok = True
    for i, c in enumerate(line):
        s.add((i + int(c)) % n)
    if len(s) == n:
        print('{}: valid with {} balls'.format(line, balls))
    else:
        print('{}: invalid pattern'.format(line))
