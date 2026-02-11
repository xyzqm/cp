#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

struct bit : vector<int> {
    bit(int n) : vector(n + 1, 0) {}
    void upd(int i, int x) {
        for (++i; i < size(); i += i & -i) at(i) = at(i) + x;
    }
    int query(int r) {
        int res = 0;
        for (; r; r -= r & -r) res = res + at(r);
        return res;
    }
};

void ac() {
    int n, q; cin >> n >> q;
    // input tree
    auto g = vector(n + 1, vector<int>());
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    // dfs + HLD
    vector<int> d(n + 1, 0), chain(n + 1), par(n + 1), sz(n + 1, 1), rt;
    auto dfs = [&](this auto dfs, int x, int p) -> void {
        d[x] = d[par[x] = p] + 1;
        pair<int, int> mx = {-1, 0};
        for (int y : g[x]) if (y != p) {
            dfs(y, x);
            sz[x] += sz[y];
            mx = max(mx, {sz[y], y});
        }
        if (mx.second) chain[x] = chain[mx.second];
        else chain[x] = rt.size(), rt.emplace_back();
        rt[chain[x]] = x;
        DBG(x);
    };
    dfs(1, 0);
    DBG(chain);
    DBG(rt);
    // answer queries
    auto qs = vector(n + 1, vector<array<int, 2>>());
    for (int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        qs[r].push_back({l, i});
    }
    bit frq(n + 1); // how many of each color are there?
    auto colors = vector(n + 1, set<array<int, 3>>()); // {left, right, color}
    vector<int> res(q);

    auto paint = [&](set<array<int, 3>> &s, array<int, 3> nw) {
        DBG(nw);
        while (true) {
            auto it = s.lower_bound({nw[1] + 1, nw[1], 0});
            if (it == s.begin()) break;
            it = prev(it);
            assert((*it)[0] <= nw[1]);
            if ((*it)[1] < nw[0]) break; // no overlap
            auto overlap = array{max((*it)[0], nw[0]), min((*it)[1], nw[1]), (*it)[2]};
            frq.upd(overlap[2], -(overlap[1] - overlap[0] + 1));
            auto prv = *it;
            s.erase(it);
            if (overlap != prv) { // some parts need to be added back
                if (prv[0] < overlap[0]) s.insert({prv[0], overlap[0] - 1, prv[2]});
                if (overlap[1] < prv[1]) s.insert({overlap[1] + 1, prv[1], prv[2]});
            }
        }
        s.insert(nw);
        frq.upd(nw[2], nw[1] - nw[0] + 1);
    };

    for (int r = 1; r <= n; r++) {
        for (auto &[l, i] : qs[r]) {
            res[i] = frq.query(r) - frq.query(l);
            if (l == r) ++res[i];
            assert(res[i]);
        }
        if (r == n) break;
        // color path from r to r + 1 with color r
        int u = r, v = r + 1;
        while (chain[u] != chain[v]) {
            if (d[rt[chain[u]]] < d[rt[chain[v]]]) swap(u, v); // make u the deeper root
            paint(colors[chain[u]], {d[rt[chain[u]]], d[u], r});
            u = par[rt[chain[u]]];
        }
        if (d[u] < d[v]) swap(u, v);
        paint(colors[chain[u]], {d[v], d[u], r});
    }

    for (int i = 0; i < q; i++) cout << res[i] - 1 << "\n";
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
