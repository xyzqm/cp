from random import randint


n = 200000
print(n, n)

for i in range(1, n):
    print(randint(1, i))
    # print(randint(1, i), i + 1

for _ in range(n):
    print(1, randint(1, n))
