#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    auto g = vector(n + 1, vector<int>());
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> par(n + 1), ch(n + 1);
    auto dfs = [&](auto &&f, int x, int p) -> void {
        ++ch[par[x] = p];
        for (int y : g[x]) if (y != p) f(f, y, x);
    };
    dfs(dfs, 1, 0);

    auto days = vector(m, vector<int>());
    for (int i = 0; i < m; i++) {
        int sz; cin >> sz;
        days[i].resize(sz);
        for (int &u : days[i]) cin >> u;
    }
    reverse(days.begin(), days.end());
    auto red_c = vector(n + 1, vector<int>());
    vector<int> white_p = {}; // set of white parents with at least one red child
    vector<int> has_white_c = {}; // red nodes with white children
    vector<bool> red(n + 1);
    vector<int> c_red(n + 1); // number of red children
    for (auto &day : days) {
        auto mark = [&] (int u) { // only called at most O(sum k) timse
            assert(!red[u]);
            red[u] = true;
            has_white_c.push_back(u);
            if (par[u]) {
                ++c_red[par[u]];
                white_p.push_back(par[u]);
                red_c[par[u]].push_back(u);
            }
        };
        vector<int> nx_wp, nx_hwc;
        auto unmark = [&] (int u) { // only called at most O(sum k) times
            assert(red[u]);
            red[u] = false;
            nx_wp.push_back(u);
            if (par[u]) {
                nx_hwc.push_back(par[u]);
                // --c_red[par[u]];
            }
        };
        for (int u : day) if (!red[u]) mark(u);
        auto filter = [&](vector<int> &v, function<bool(int)> &&pred) {
            vector<int> vv;
            for (int u : v) if (pred(u)) vv.push_back(u);
            v = vv;
        };
        filter(white_p, [&](int u) { return !red[u]; });
        filter(has_white_c, [&](int u) { return red[u]; });
        for (int u : white_p) { // body bypassed at most k times
            for (int v : red_c[u]) if (red[v]) {
                unmark(v);
            }
            // assert(tot == c_red[u]);
            red_c[u].clear();
        }
        for (int u : has_white_c) {
            if (red[u] && c_red[u] < ch[u]) {
                unmark(u);
            }
        }

        white_p = nx_wp;
        has_white_c = nx_hwc;
        for (int u : nx_hwc) --c_red[u];
    }
    // DBG(cur);
    int res = 0;
    for (int i = 1; i <= n; i++) if (!red[i]) res += a[i];
    cout << res << "\n";
}
