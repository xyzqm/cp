from random import randint


n = 10
print(n)

for i in range(1, n):
    print(randint(1, i), i + 1)
