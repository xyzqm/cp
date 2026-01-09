#include <bits/stdc++.h>
using namespace std;

#define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

void smax(int &a, const int b) { a = max(a, b); }

struct lz : deque<int> {
    int ad = 0;
    void operator+=(int x) { ad += x; }
    int operator[](int i) const { return deque::at(i) + ad; }
    void operator<<=(lz &o) {
        if (size() < o.size()) { swap(o); ::swap(ad, o.ad); }
        for (int i = 0; i < o.size(); i++) smax(at(i), o[i] - ad);
    }
    void push_front(int x) { deque::push_front(x - ad); }
};

void ac() {
    int n, m; cin >> n >> m;
    vector<int> p(n + 1);
    vector<vector<int>> g(n + 1);
    for (int u = 2; u <= n; u++) {
        cin >> p[u];
        g[p[u]].push_back(u);
    }

    // precompute subtree sizes
    auto sz = vector<int>(n + 1, 1);
    for (int u = n; u > 1; u--) sz[p[u]] += sz[u];

    // ad: adding to existing chain of length x, which is also maximum
    // ad[x] depends on ad[x + 1] and nw[x] of children
    auto ad = array{vector<int>(n + 1), vector<int>(n + 1)};

    // nw: starting a new chain, where x is the current maximum chain length
    // depends on ad[x] and nw[x] of descendants
    auto nw = vector<int>(n + 1);
    auto tot = vector<int>(n + 1); // sum of nw of children
    vector<lz> opts(n + 1);

    DBG(sz);
    for (int x = m + 1; x > 0; x--) {
        ranges::fill(ad[0], 0);
        ranges::fill(nw, 0);
        ranges::fill(tot, 0);
        DBG(x);
        for (int u = n; u > 0; u--) {
            opts[u].clear();
            smax(nw[u], x * sz[u]);
            for (int v : g[u]) {
                smax(ad[0][u], ad[1][v] + tot[u] - nw[v]);
                opts[v] += tot[u] - nw[v];
                opts[u] <<= opts[v];
            }
            opts[u].push_front(ad[0][u] += x);
            // DBG(x);
            DBG(opts[u]);
            DBG(opts[u].ad);
            if (x <= opts[u].size()) smax(nw[u], (x - 1) * x + opts[u][x - 1]);

            tot[p[u]] += nw[u];
        }
        ad[0].swap(ad[1]);
    }
    cout << nw[1] << "\n";
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
