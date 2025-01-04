import numpy as np
from numpy.linalg import inv
n, k, q = map(int, input().split())
G = np.zeros((n, n))

matrix = []
for _ in range(n):
    matrix.append(list(map(int, input().strip())))

dp = [np.array(matrix)]
for _ in range(k):
    dp.append(dp[-1] @ dp[-1] + dp[-1])

for mat in dp:
    print(mat)

print((dp[0] + np.identity(n)))
print(inv(dp[0] + np.identity(n)))

for _ in range(q):
    bs, s, bt, t = map(int, input().split())
    s -= 1
    t -= 1
    r = 0
    if k > max(bs, bt):
        A = inv(dp[bs - 1] + np.identity(n)) @ (dp[k] - dp[max(bs, bt)]) @ inv(dp[bt - 1] + np.identity(n))
        r = A[s][t]
    if bs < bt: # maximum is bt
        r += (inv(dp[bs - 1] + np.identity(n)) @ dp[bt - 1])[s][t]
    elif bs > bt: # maximum is bs
        r += (dp[bs - 1] @ inv(dp[bt - 1] + np.identity(n)))[s][t]
    elif s == t:
        r += 1
    print(r)
