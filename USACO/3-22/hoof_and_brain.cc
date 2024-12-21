// https://usaco.org/index.php?page=viewproblem2&cpid=1237
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 1;

// DSU
int p[N];
int fa(int x) { return p[x] = (x == p[x] ? x : fa(p[x])); }

int n;
set<int> g[N], rg[N];
bool cut[N];

int main() {
    int m; cin >> n >> m;
    while (m--) {
        int u, v; cin >> u >> v;
        g[u].insert(v);
        rg[v].insert(u);
    }
    stack<int> q;
    for (int i = 1; i <= n; i++) if (!g[i].size()) q.push(i);
    while (q.size()) {
        int x = q.top(); q.pop();
        assert(!g[x].size() && !cut[x]);
        cut[x] = true;
        for (int y : rg[x]) {
            g[y].erase(x);
            if (!g[y].size()) q.push(y);
        }
        rg[x].clear();
    }
    for (int i = 1; i <= n; i++) if (g[i].size() == 1) q.push(i);
    iota(p, p + N, 0);
    while (q.size()) {
        int u = q.top(); q.pop();
        assert(g[u].size() == 1);
        int v = *g[u].begin();
        u = fa(u), v = fa(v);
        if (u == v) continue;
        if (rg[u].size() < rg[v].size()) {
            swap(u, v);
        }
        // merge v into u
        for (int x : rg[v]) {
            // assert(g[x].find(v) != g[x].end() || g[x].find(u) != g[x].end());
            g[x].erase(v);
            g[x].insert(u);
            rg[u].insert(x);
            if (g[x].size() == 1) q.push(x), rg[u].erase(x);
        }
        p[v] = u;
        // for (int i = 1; i <= n; i++) assert(g[fa(i)].find(v) == g[fa(i)].end());
    }
    int t; cin >> t;
    while (t--) {
        int u, v; cin >> u >> v;
        cout << "HB"[cut[u] || cut[v] || fa(u) == fa(v)];
    }
    cout << endl;
}
