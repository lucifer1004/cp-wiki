from sys import stdin, stdout


def read_int():
    return int(stdin.readline().strip())


t = read_int()
for case_num in range(t):
    n = read_int()
    counter = [0 for _ in range(26)]

    for i in range(n):
        s = stdin.readline().strip()
        for c in s:
            counter[ord(c) - ord('a')] += 1
    ok = True
    for count in counter:
        if count % n != 0:
            ok = False
            break
    stdout.write('YES\n' if ok else 'NO\n')
