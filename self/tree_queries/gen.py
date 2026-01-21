from random import randint, shuffle


t = 10
n, q = 100, 100
print(t)
for _ in range(t):
    print(n, q)
    idx = list(range(1, n + 1))
    shuffle(idx)
    for i in range(1, n):
        print(idx[randint(0, i - 1)], idx[i])
    for _ in range(q):
        l, r = randint(1, n), randint(1, n)
        if l > r:
            l, r = r, l
        print(l, r)
