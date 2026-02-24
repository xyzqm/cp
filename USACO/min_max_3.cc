#include <bits/stdc++.h>
using namespace std;

#define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

void ac() {
    int n, q; cin >> n >> q;
    auto qs = vector(n, vector<array<int, 3>>());
    vector<int> ks;
    while (q--) {
        int t, l, r, k; cin >> t >> l >> r >> k;
        qs[--l].push_back({r, --t, k});
        ks.push_back(k);
    }
    // coordinate compress
    sort(ks.begin(), ks.end());
    for (auto &ql : qs) for (auto &[_, __, k] : ql) {
        k = lower_bound(ks.begin(), ks.end(), k) - ks.begin();
    }
    DBG(qs);

    auto g = vector(ks.size(), vector<array<int, 2>>());
    vector<int> deg(ks.size());
    auto add_edge = [&](int mn, int mx, int i) {
        if (mn >= 0) g[mn].push_back({mx, i}), ++deg[mn];
        if (mx >= 0) g[mx].push_back({mn, i}), ++deg[mx];
    };

    set<array<int, 3>> active;
    array<set<int>, 2> bounds;
    vector<int> low(n);
    for (int i = 0; i < n; i++) {
        for (auto &[r, t, k] : qs[i]) {
            active.insert({r, t, k});
            bounds[t].insert(k);
        }
        while (active.size() && (*active.begin())[0] == i) {
            auto &[r, t, k] = *active.begin();
            bounds[t].erase(k);
            active.erase(active.begin());
        }
        int lb = -1, ub = -1;
        if (bounds[0].size()) lb = *bounds[0].rbegin();
        if (bounds[1].size()) ub = *bounds[1].begin();
        if (lb >= 0) low[i] = ks[lb];

        if (lb >= 0 && ub >= 0 && lb > ub) {
            cout << "-1\n";
            return;
        }
        else add_edge(lb, ub, i);
    }
    DBG(g);
    DBG(deg);
    set<array<int, 2>> by_deg;
    for (int i = 0; i < ks.size(); i++) by_deg.insert({deg[i], i});
    vector<int> res(n, -1);
    vector<bool> sat(ks.size());
    auto match = [&](int u) {
        for (auto &[v, idx] : g[u]) if (res[idx] == -1) {
            sat[u] = true;
            res[idx] = ks[u];
            if (v >= 0 && !sat[v]) {
                by_deg.erase({deg[v]--, v});
                by_deg.insert({deg[v], v});
            }
            return;
        }
        assert(false);
    };
    while (by_deg.size()) {
        auto [dg, u] = *by_deg.begin();
        by_deg.erase(by_deg.begin());
        if (!dg) { cout << "-1\n"; return; }
        else match(u);
    }
    DBG(res);
    for (int i = 0; i < ks.size(); i++) if (!sat[i]) { cout << "-1\n"; return; }
    for (int i = 0; i < n; i++) cout << (res[i] >= 0 ? res[i] : low[i]) << " \n"[i == n - 1];
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
