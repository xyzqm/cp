import random

n, m, l, q = 1000000, 500, 100000, 100000
print(n, m, l, q)
vals = [random.randint(1, n) for _ in range(m)]
vals.sort()
print(*vals)
for _ in range(q):
    print(random.randint(1, n), random.randint(1, n))
