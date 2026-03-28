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
    int n, m, q; cin >> n >> m >> q;
    vector<array<int, 2>> g(m);
    for (auto &[u, v] : g) cin >> u >> v;
    vector<array<int, 2>> qs(q);
    map<int, int> ls;
    for (auto &[l, r] : qs) {
        cin >> l >> r;
        ls[--l] = 0;
    }
    vector<array<int, 2>> dsu(n + 1, {-1, 0}); // {par, weight of edge}
    auto get = [&](this auto get, int u) -> int {
        auto &[par, w] = dsu[u];
        if (par < 0) return u;
        else {
            int rt = get(par);
            w ^= dsu[par][1];
            return par = rt;
        }
    };
    auto unite = [&](array<int, 2> e) {
        auto &[u, v] = e;
        int rt_u = get(u), rt_v = get(v);
        if (rt_u == rt_v) {
            return dsu[u][1] != dsu[v][1];
        }
        if (dsu[rt_u][0] < dsu[rt_v][0]) swap(rt_u, rt_v);
        dsu[rt_v][0] += dsu[rt_u][0];
        dsu[rt_u] = {rt_v, 1 ^ dsu[u][1] ^ dsu[v][1]};
        return true;
    };
    for (auto &[l, r] : ls) {
       dsu.assign(n + 1, {-1, 0});
        for (int i = 0; i < l; i++) {
            DBG(i);
            if (!unite(g[i])) {
                r = m;
                break;
            }
            DBG(dsu);
        }
        if (r == m) continue;
        for (r = m - 1; r > l; r--) {
            if (!unite(g[r])) break;
        }
    }
    DBG(ls);
    for (auto &[l, r] : qs) {
        cout << array{"NO\n", "YES\n"}[r <= ls[l]];
    }
}
