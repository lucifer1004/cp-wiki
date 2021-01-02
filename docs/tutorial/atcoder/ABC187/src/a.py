def dsum(n):
    return sum(int(x) for x in str(n))

a, b = map(int, input().split())
print(max(dsum(a), dsum(b)))
