#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using ll = long long;
// flow-edge
struct FE { int u, v; ll c; };
template <int N>
// push-relabel
struct Flow {
    const int inf = 1e9;
    int s, t, n, l[N], h[N], g[N]; // source, sink, current-arc, height, gap
    ll c[N][N], f[N][N], e[N]; // capacity, flows, excess
    queue<int> ex; // vertices with excess
    ll* operator[](int i) { return &f[i][0]; }

    void push(int u) { // push to next node
        if (l[u] >= n) raise(u), l[u] = 0; // exhausted all edges
        int v = l[u]++;
        if (h[u] <= h[v]) return;
        ll d = min(e[u], c[u][v] - f[u][v]);
        f[u][v] += d, f[v][u] -= d;
        e[u] -= d, e[v] += d;
        if (d && e[v] == d) ex.push(v);
    }

    void raise(int u) {
        int d = inf;
        for (int i = 0; i < n; i++) if (c[u][i] > f[u][i]) d = min(d, h[i]);
        --g[h[u]];
        ++g[h[u] = d + 1];
    }

    ll flow() {
        for (int i = 0; i < n; i++) push(s);
        while (ex.size()) {
            int u = ex.front(); ex.pop();
            if (u != s && u != t) while (e[u]) push(u);
        }
        return (ll)1e18 - e[s];
    }

    Flow& init(int n, int S, int T, vector<FE> G, bool U = false) { // U -> whether undirected
        memset(c, 0, sizeof c), memset(f, 0, sizeof f);
        memset(h, 0, sizeof h), memset(e, 0, sizeof e);
        memset(l, 0, sizeof l), memset(g, 0, sizeof g);
        this->n = n;
        s = S, t = T;
        e[s] = 1e18, h[s] = n, g[n] = 1, g[0] = n - 1;
        for (auto [u, v, C] : G) c[u][v] += C, c[v][u] += U * C;
        return *this;
    }
};
