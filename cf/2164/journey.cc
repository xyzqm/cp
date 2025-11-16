#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

struct dsu : vector<int> {
    dsu(int n) : vector(n, -1) {}
    int rep(int x) { return at(x) < 0 ? x : at(x) = rep(at(x)); }
    bool same(int x, int y) { return rep(x) == rep(y); }
    bool join(int x, int y) {
        x = rep(x), y = rep(y);
        if (x == y) return 0;
        if (at(x) > at(y)) ::swap(x, y);
        at(x) += at(y);
        return at(y) = x, 1;
    }
};

void ac() {
    int n, m; cin >> n >> m;
    vector<int> cnt(n + 1), id(n + 1), fa(n + m + 2), best(n + 1);
    iota(id.begin(), id.end(), 0);
    dsu uf(n + 1);
    int ans = 0;
    while (m--) {
        int u, v, w; cin >> u >> v >> w;
        for (int x : {u, v}) cnt[x] ^= 1;
        u = uf.rep(u), v = uf.rep(v);
        uf.join(u, v);
        id[uf.rep(u)] = fa[id[u]] = fa[id[v]] = cnt.size();
        cnt.push_back(0);
        best.push_back(w);
        ans += w;
    }
    for (int i = best.size(); i > n; i--) if (fa[i]) best[i] = min(best[i], best[fa[i]]);
    for (int i = 1; i < cnt.size(); i++) {
        assert(cnt[i] <= 2);
        if (cnt[i] == 2) {
            assert(i > n);
            ans += best[i], cnt[i] = 0;
        }
        if (fa[i]) cnt[fa[i]] += cnt[i];
    }
    cout << ans << endl;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
