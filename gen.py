import random

n = 4
print(1, 1)
k = random.randint(1, n - 1)
print(n, k)
for i in range(2, n + 1):
    print(random.randint(1, i - 1), i)

print(*random.sample(range(1, n + 1), k=k))
