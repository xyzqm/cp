import itertools

n, m = map(int, input().split())
g = [[] for _ in range(n + 1)]
edges = []

for _ in range(m):
    u, v = map(int, input().split())
    g[u].append(v)
    g[v].append(u)
    edges.append((u, v))

for (b, c) in edges:
    opt_a, opt_d = [], []
    for u in g[b]:
        if len(opt_a) > 1: break
        if u != c: opt_a.append(u)
    for u in g[c]:
        if len(opt_d) > 1: break
        if u != b: opt_d.append(u)

    for (a, d) in itertools.product(opt_a, opt_d):
        if a != d:
            print(a, b, c, d, sep="\n")
            quit()
print(-1)
