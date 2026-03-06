import random

print(1)
n, k = 20, 4
print(n, k, random.randint(1, n // k))
for i in range(n):
    print(random.randint(1, k), end=' ')
    # print(i)

print()
