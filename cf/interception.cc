// https://codeforces.com/gym/104848/problem/K
#include <bits/stdc++.h>
#include "flow.cc"
const ll inf = 1e9;

const int N = 302;
Flow<2 * N> f;
int g[N][N], v[N];
void U(int u, int v) { g[u][v] = g[v][u] = 1; }

void ac() {
    int n, m; cin >> n >> m;
    memset(g, 0, sizeof g);
    U(0, 1), U(n, n + 1);
    vector<pair<int, int>> gg;
    while (m--) {
        int u, v; cin >> u >> v;
        U(u, v);
        gg.push_back({u, v});
    }
    vector<FE> fg;
    for (int i = 0; i <= n + 1; i++) {
        fg.push_back({i, i + n + 2, i > 0 && i <= n ? 1 : inf});
        memset(v, 0, sizeof v);
        queue<int> q; q.push((v[i] = 1, i));
        while (q.size()) {
            int x = q.front(); q.pop();
            if (i != x) fg.push_back({i + n + 2, x, inf});
            if (v[x] < 4) for (int y = 0; y <= n + 1; y++) if (g[x][y] && !v[y]) q.push((v[y] = v[x] + 1, y));
        }
    }
    cout << f.init(2 * n + 4, 0, 2 * n + 3, fg).flow() << " ";
    vector<int> c; // vertices in cut
    int l = 0; while (f.g[l]) l++;
    for (int i = 1; i <= n; i++) if (f.h[i] > l && f.h[i + n + 2] < l) c.push_back(i);
    assert(c.size() == (ll)1e18 - f.e[0]);
    vector<int> r;
    for (int u : c) if (u > 1 && u < n) {
        int t = accumulate(g[u], g[u] + N, 0);
        for (int v : c) t -= g[u][v];
        if (!t) r.push_back(u);
    }
    cout << r.size() << endl;
    for (int x : r) cout << x << " ";
    cout << endl;
}

int main() {
    int t; cin >> t;
    while (t--) ac();
}
