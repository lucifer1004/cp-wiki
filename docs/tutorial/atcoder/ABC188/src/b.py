n = int(input())
a = list(map(int, input().split()))
b = list(map(int, input().split()))
print('Yes' if sum(ai * bi for ai, bi in zip(a, b)) == 0 else 'No')
