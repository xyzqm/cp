import random

print(1)
n = 100000
k = random.randint(1, n - 1)
print(n, k)
for i in range(1, n):
    # print(i)
    print(random.randint(1, i))
