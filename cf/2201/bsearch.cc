#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

void ac() {
    int n, q; cin >> n >> q;
    vector<int> a(n);
    auto pos = vector(n + 1, set<int>());
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pos[a[i]].insert(i);
    }
    auto rngs = vector(n + 1, set<array<int, 2>>()); // ranges by difference
    vector<int> ws(n); // sum by difference
    auto ws_range = [&](array<int, 2> rng) {
        int vals = rng[1] - rng[0];
        return vals * (vals + 1) / 2;
    };
    auto mod_range = [&](int dif, array<int, 2> rng, bool ad) {
        if (ad) rngs[dif].insert(rng);
        else rngs[dif].erase(rng);
        ws[dif] += (ad ? 1 : -1) * ws_range(rng);
    };
    auto ad = [&](int dif, int v) { // add v to the range set
        auto &s = rngs[dif];
        array<int, 2> cur = {v, v + 1};
        auto it = s.lower_bound({v, 0});
        vector<array<int, 2>> to_rem;
        if (it != s.end() && (*it)[0] == cur[1]) {
            to_rem.push_back(*it);
            cur[1] = (*it)[1];
        }
        if (it != s.begin() && (*prev(it))[1] == cur[0]) {
            to_rem.push_back(*prev(it));
            cur[0] = (*prev(it))[0];
        }
        for (auto rng : to_rem) mod_range(dif, rng, false);
        mod_range(dif, cur, true);
    };
    auto rm = [&](int dif, int v) { // remove v from the range set
        auto &s = rngs[dif];
        auto cur = *prev(s.lower_bound({v + 1, 0}));
        mod_range(dif, cur, false);
        if (cur[0] < v) mod_range(dif, {cur[0], v}, true);
        if (v + 1 < cur[1]) mod_range(dif, {v + 1, cur[1]}, true);
    };
    multiset<int> vs;
    auto sync = [&](int val, bool add) {
        if (pos[val].size() < 2) return;
        int dif = *pos[val].rbegin() - *pos[val].begin();
        if (add) ad(dif, *pos[val].begin()), vs.insert(dif);
        else {
            DBG(pos[val]);
            // DBG(rngs[dif]);
            rm(dif, *pos[val].begin());
            vs.erase(vs.find(dif));
        }
    };
    for (int i = 1; i <= n; i++) sync(i, true);
    // DBG(rngs);
    while (q--) {
        int i, x; cin >> i >> x;
        if (x != a[--i]) {
            sync(a[i], false);
            sync(x, false);
            pos[a[i]].erase(i);
            pos[x].insert(i);
            sync(a[i], true);
            sync(a[i] = x, true);
        }
        DBG(vs);
        if (vs.size()) {
            // DBG(vs);
            int k = *vs.rbegin();
            DBG(rngs[k]);
            cout << k << " " << ws[k] << "\n";
        }
        else cout << "0 0\n";
    }
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
