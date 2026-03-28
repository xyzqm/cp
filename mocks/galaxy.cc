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
    vector<int> out_deg(n + 1);
    vector<vector<array<int, 2>>> in(n + 1);
    while (m--) {
        int u, v; cin >> u >> v;
        ++out_deg[u];
        in[v].push_back({u, 1});
    }
    int q; cin >> q;
    auto toggle = [&](int v, int st, int u) {
        for (auto &[uu, ss] : in[v]) if (!u || uu == u) {
            out_deg[uu] += st - ss;
            ss = st;
        }
    };
    while (q--) {
        int t; cin >> t;
        --t;
        if (t & 1) {
            int v; cin >> v;
            toggle(v, t >> 1, 0);
        }
        else {
            int u, v; cin >> u >> v;
            toggle(v, t >> 1, u);
        }
        // DBG(out_deg);
        if (count(out_deg.begin() + 1, out_deg.end(), 1) == n) {
            cout << "YES\n";
        }
        else cout << "NO\n";
        // DBG(in);
    }
}
