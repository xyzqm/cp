k = 2
a = list(range(2 ** k))
for _ in range(k // 2):
    a = a[::2]
    a = a[len(a)//2:]
print(bin(a[0]))
