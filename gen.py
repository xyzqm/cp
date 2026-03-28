import random

n = 1000
print(n)
for i in range(2, n + 1):
    print(random.randint(1, i - 1), i)
