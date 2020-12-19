def read_int():
    return int(input())


def read_ints():
    return map(int, input().split(' '))


h, w = read_ints()
lo = 100
s = 0
for i in range(h):
    row = list(read_ints())
    lo = min(lo, min(row))
    s += sum(row)
print(s - lo * h * w)
