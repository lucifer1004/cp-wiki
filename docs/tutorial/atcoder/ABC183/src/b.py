sx, sy, gx, gy = map(int, input().split())
print("{:.12f}".format(sx + (gx - sx) * sy / (sy + gy)))
