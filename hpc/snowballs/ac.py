def ac():
    n = int(input())
    a = list(map(int, input().split()))
    sum, res = 0, 0
    for x in a:
        res += sum * x
        sum += x
    ways = 1
    for i in range(1, n): ways = ways * i % 998244353
    print(res, ways)

for _ in range(int(input())):
    ac()
