#include <bits/stdc++.h>
using namespace std;

void ac() {
    int n; cin >> n;
    auto g = vector(n + 1, vector<int>());
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> nx(n + 1), d(n + 1);
    auto furthest = [&](this auto self, int x, int p = 0) -> int {
        int lst = x;
        nx[x] = d[x] = 0;
        for (int y : g[x]) if (y != p) if (int z = self(y, x); d[y] + 1 > d[x]) nx[x] = y, lst = z, d[x] = d[y] + 1;
        return lst;
    };
    int x = furthest(1);
    for (furthest(x); x; x = nx[x]) if (g[nx[x]].size() > 2) {
        println("{} {} {}", x, nx[x], *ranges::find_if(g[nx[x]], [&](int y) { return y != x && y != nx[nx[x]]; }));
        return;
    }
    println("-1");
}

int32_t main() {
    int t; cin >> t;
    while (t--) ac();
}
