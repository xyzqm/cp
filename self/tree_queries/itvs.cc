#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

int mx = 0;

void ac() {
    int n, q; cin >> n >> q;
    auto g = vector(n + 1, vector<int>());
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    auto side = vector(n + 1, set<int>());
    map<pair<int, int>, int> itvs;
    auto dfs = [&](this auto dfs, int x, int p) -> void {
        side[x].insert(x);
        for (auto y : g[x]) if (y != p) {
            dfs(y, x);
            for (int z : side[y]) side[x].insert(z);
        }
        DBG(x);
        DBG(side[x]);
        if (x == 1) return;
        int lef = 0, cur = 0;
        for (int y : side[x]) {
            if (y == cur) cur++;
            else {
                ++itvs[{lef, cur - 1}];
                ++itvs[{cur, y - 1}];
                lef = y, cur = y + 1;
            }
        }
        ++itvs[{lef, cur - 1}];
        ++itvs[{cur, n}];
        DBG(itvs);
    };
    dfs(1, 0);
    DBG(itvs.size());
    // assert(itvs.size() <= n * 6);
    mx = max(mx, (int)itvs.size());
    while (q--) {
        int l, r, res = 0; cin >> l >> r;
        for (auto &[itv, c] : itvs) {
            auto &[a, b] = itv;
            if (a <= l && r <= b) res += c;
        }
        cout << n - 1 - res << endl;
    }
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
