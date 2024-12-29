// https://qoj.ac/contest/1660/problem/8673
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5 + 1;

vector<tuple<int, int, long long>> generate_edges(int n, int m, unsigned seed) {
    mt19937 gen(seed);
    vector<std::tuple<int, int, long long>> edges(m);
    unsigned max = -1u / n * n;
    auto sample = [&]() {
        unsigned x;
        do { x = gen(); } while(x >= max);
        return x % n + 1;
    };
    for(auto & [u, v, w] : edges) {
        u = sample();
        v = sample();
        w = gen();
    } // u 到 v 存在边权为 w 的边
    return edges;
}

const ll inf = 1e18;
struct E { int v; ll w;
    bool operator<(const E &o) const { return w < o.w; }
};

vector<E> g[2][N];
ll d[2][N];

ll edge(int x, int t, int i) { return i == g[t][x].size() ? inf : g[t][x][i].w; };

struct T {
    ll w; int x, i; bool t;
};

struct cmp {
    bool operator()(const T &x, const T &y) {
        auto [a, b, i, t] = x;
        auto [c, d, j, _] = y;
        assert(t == _);
        return a + edge(b, t, i) > c + edge(d, t, j);
    };
};

ll ac() {
    int s, t; cin >> s >> t;
    if (s == t) return 0;
    priority_queue<T, vector<T>, cmp> pq[2];
    ll r = inf;
    bool cur = 0;
    pq[0].push({d[0][s] = 0, s, 0, 0});
    pq[1].push({d[1][t] = 0, t, 0, 1});
    vector<int> vis[2];
    vis[0] = {s}, vis[1] = {t};
    while (pq[0].size() && pq[1].size()) {
        auto [d, x, i, _] = pq[cur].top(); pq[cur].pop();
        if (d > ::d[cur][x]) continue;
        if (i == g[cur][x].size()) continue;
        auto [y, w] = g[cur][x][i];
        if (++i < g[cur][x].size()) pq[cur].push({d, x, i, cur});
        if (d + w < ::d[cur][y]) {
            pq[cur].push({::d[cur][y] = d + w, y, 0, cur});
            vis[cur].push_back(y);
            if (::d[cur ^ 1][y] < inf) { // we've found a hit
                r = d + w + ::d[cur ^ 1][y];
                break;
            }
        }
        cur ^= 1;
    }
    if (r != inf) {
        for (int x : vis[0]) {
            for (auto [y, w] : g[0][x]) {
                if (w > r - 2 * d[0][x]) break;
                r = min(r, d[0][x] + w + d[1][y]);
            }
        }
        for (int x : vis[1]) {
            for (auto [y, w] : g[1][x]) {
                if (w > r - 2 * d[1][x]) break;
                r = min(r, d[1][x] + w + d[0][y]);
            }
        }
    }
    for (int t : {0, 1}) for (int x : vis[t]) {
        d[0][x] = d[1][x] = inf;
    }
    return r == inf ? -1 : r;
}

int main() {
    int n, m, q; unsigned seed; cin >> n >> m >> q >> seed;
    for (auto [u, v, w] : generate_edges(n, m, seed)) {
        // cout << u << " " << v << " " << w << endl;
        g[0][u].push_back({v, w});
        g[1][v].push_back({u, w});
    }
    for (int t : {0, 1}) {
        fill(d[t], d[t] + N, inf);
        for (int i = 1; i <= n; i++) {
            sort(g[t][i].begin(), g[t][i].end());
        }
    }
    while (q--) cout << ac() << endl;
}
