#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int long long

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    auto g = vector(n + 1, vector<int>());
    vector<int> deg(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        ++deg[u], ++deg[v];
    }
    vector<int> cur, nx;
    vector<bool> del(n + 1);
    for (int i = 1; i <= n; i++) if (deg[i] == 1) cur.push_back(i);
    while (cur.size() > 2) {
        for (int u : cur) {
            del[u] = true;
            for (int v : g[u]) {
                if (--deg[v] == 1) nx.push_back(v);
            }
        }
        cur = nx;
        nx.clear();
    }
    DBG(cur);
    vector<bool> vis(n + 1);
    auto get_tails = [&](int u) {
        vector<int> cnts, cur = {u}, nx, seen;
        while (cur.size()) {
            cnts.push_back(cur.size());
            for (int u : cur) {
                vis[u] = true;
                seen.push_back(u);
                for (int v : g[u]) if (del[v] && !vis[v]) nx.push_back(v);
            }
            cur = nx;
            nx.clear();
        }
        for (int u : seen) vis[u] = false;
        return cnts;
    };
    DBG(get_tails(cur[0]));
    DBG(get_tails(cur.back()));
    auto conv = convolution_ll(get_tails(cur[0]), get_tails(cur.back()));
    DBG(conv);
    if (cur[0] == cur.back()) {
        for (int v : g[cur[0]]) {
            auto tails = get_tails(v);
            tails.insert(tails.begin(), 0);
            DBG(tails);
            tails = convolution_ll(tails, tails);
            DBG(tails);
            for (int i = 0; i < tails.size(); i++) conv[i] -= tails[i];
        }
        for (int &v : conv) if (v > 1) v /= 2;
    }
    DBG(conv);
    int dist = [&](this auto dfs, int x, int p) -> int {
        if (x == cur.back()) return 0;
        for (int y : g[x]) if (y != p) {
            if (int dist = dfs(y, x); dist != -1) return dist + 1;
        }
        return -1;
    }(cur[0], 0);
    DBG(dist);
    conv.resize(n);
    for (int i = 0; i < n; i++) {
        if (i < dist) cout << "0\n";
        else cout << conv[i - dist] << "\n";
    }
}
