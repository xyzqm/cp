#include <queue>
#include <vector>
#include <iostream>
using namespace std;
using ll = long long;
// flow-edge
struct FE { int u, v; ll c; };
template <int N>
// push-relabel
struct Flow {
    const int inf = 1e9;
    int s, t, n, l[N], h[N]; // source, sink, current-arc, height
    ll c[N][N], f[N][N], e[N]; // capacity, flows, excess
    queue<int> ex; // vertices with excess

    void push(int u) { // push to next node
        assert(e[u]);
        if (l[u] >= n) raise(u), l[u] = 0; // exhausted all edges
        int v = l[u]++;
        if (h[u] <= h[v]) return;
        assert(c[u][v] >= f[u][v]);
        ll d = min(e[u], c[u][v] - f[u][v]);
        f[u][v] += d, f[v][u] -= d;
        e[u] -= d, e[v] += d;
        if (d && e[v] == d) ex.push(v);
    }

    void raise(int u) {
        int d = inf;
        for (int i = 0; i < n; i++) if (c[u][i] > f[u][i]) d = min(d, h[i]);
        h[u] = d + 1;
    }

    ll flow() {
        e[s] = 1e18, h[s] = n;
        for (int i = 0; i < n; i++) push(s);
        while (ex.size()) {
            int u = ex.front(); ex.pop();
            if (u != s && u != t) while (e[u]) push(u);
        }
        return (ll)1e18 - e[s];
    }

    Flow& init(int n, int S, int T, vector<FE> g) {
        this->n = ++n;
        s = S, t = T;
        for (auto [u, v, C] : g) c[u][v] += C;
        return *this;
    }
};
