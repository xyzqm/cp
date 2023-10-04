m = int(input())
cur = 1
ans = 0
for i in range(len(m)):
    for j in range(10):
        if ((ans + j * cur) ** 3) % (cur * 10) == m % (cur * 10):
            ans += j * cur
            break
        cur *= 10
print(ans)