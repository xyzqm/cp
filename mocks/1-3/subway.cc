#include <bits/stdc++.h>
using namespace std;
#define int int64_t
const int inf = 1e18;
const int N = 1e6 + 1;

// cost to switch from line x to line y is b_x * a_y
int n, d[N], a[N], b[N], id[N], l[N], arc[N], nx;
struct E { int w, v;
    bool operator<(const E &o) const { return w < o.w; }
    bool operator<(const int &d) const { return w < d; }
};
vector<E> g[N];

int node(int x, int line) {
    id[nx] = x, l[nx] = line;
    // connect to transfer node
    g[x].push_back({a[line], nx});
    g[nx].push_back({0, x});
    return nx++;
}

// pq element
struct Info {
    int w, u, i, k = 0; // weight, node, index of next unused edge, slope (if applicable)
    int nx() const {
        if (i >= g[u].size()) return inf;
        if (u > n) return w + g[u][i].w;
        else return w + k * g[u][i].w;
    }
    bool operator<(const Info &o) const { return nx() > o.nx(); }
};

struct Line {
    inline static int MX = 2e6;
    int m, b, l, r; // optimal on range [l, r)
    int operator()(int x) { return m * x + b; }
};
vector<Line> lc[N];
int add(int i, int m, int b) { // adds mx + b to lines from i, returns first point it becomes optimal at
    Line l = {m, b, Line::MX, Line::MX};
    while (lc[i].size() && l(lc[i].back().l) < lc[i].back()(lc[i].back().l)) lc[i].pop_back();
    int x = 0;
    if (lc[i].size()) {
        x = lc[i].back().r;
        for (int d = x; d > 0; d /= 2) {
            while (x - d > lc[i].back().l && l(x - d) < lc[i].back()(x - d)) x -= d;
        }
    }
    if (x < Line::MX) lc[i].push_back({m, b, x, Line::MX});
    return x;
}


int32_t main() {
    int k; cin >> n >> k;
    for (int i = 0; i < k; i++) cin >> a[i];
    for (int i = 0; i < k; i++) cin >> b[i];
    nx = n + 1;
    for (int i = 0; i < k; i++) {
        int p, u; cin >> p >> u;
        u = node(u, i);
        --p; while (p--) {
            int w, v; cin >> w >> v;
            v = node(v, i);
            g[u].push_back({w, v});
            u = v;
        }
    }
    for (int i = 1; i < nx; i++) sort(g[i].begin(), g[i].end());
    fill(d, d + nx, inf);
    priority_queue<Info> pq;
    pq.push({d[1] = 0, 1, 0, 0});
    add(1, 0, 0);
    while (pq.size()) {
        Info info = pq.top(); pq.pop();
        auto [w, u, i, k] = info;
        if (i < arc[u] || i >= g[u].size()) continue;
        auto [e, v] = g[u][i];
        if ((i = ++arc[u]) < g[u].size()) pq.push({w, u, i, k});
        d[v] = min(d[v], info.nx());
        int nx = arc[v];
        if (v <= n) nx = lower_bound(g[v].begin(), g[v].end(), add(v, b[l[u]], info.nx())) - g[v].begin();
        pq.push({info.nx(), v, nx, (v <= n) * b[l[u]]});
    }
    for (int i = 2; i <= n; i++) cout << d[i] << " ";
    cout << endl;
}
