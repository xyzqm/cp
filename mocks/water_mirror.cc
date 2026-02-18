// https://qoj.ac/contest/1512/problem/8218
#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

// > < < | >
// place "dividers" between all "< >", "< =", "= =", "= >"
// when divider added, no need to add new ranges (already subranges of previous range)
// when divider removed, should add subrange formed by left and right
// for each possible right point, store leftmost left point, then take suffix min afterward
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<int> v(n);
    for (int &x : v) cin >> x;
    // create events for toggle
    vector<int> st(n); // 0 = <, 1 = >, 2 = =
    map<int, vector<int>> evts;
    for (int i = 1; i < n; i++) {
        if (v[i - 1] == v[i]) st[i] = 2;
        else {
            st[i] = v[i - 1] > v[i];
            evts[v[i - 1] + v[i]].push_back(i);
        }
    }

    set<int> divs = {0, n - 1};
    // array<array<int, 2>, 4> bad = {{
    //     {0, 1}, // < >
    //     {2, 1}, // = >
    //     {0, 2}, // < =
    //     {2, 2}, // = =
    // }};
    auto sync = [&](int i) { // check whether divider i needs to be placed
        if (i <= 0 || i >= n - 1) return;
        if (st[i] != 1 && st[i + 1]) divs.insert(i);
        // if (ranges::contains(bad, array{st[i], st[i + 1]})) divs.insert(i);
        else divs.erase(i);
    };
    vector<int> lef(n, n);
    auto upd = [&](int i) { // update interval(s) containing divider i
        if (auto it = divs.lower_bound(i); it != divs.begin()) {
            lef[*it] = min(lef[*it], *prev(it));
        }
        if (auto it = divs.upper_bound(i); it != divs.end()) {
            lef[*it] = min(lef[*it], *prev(it));
        }
    };
    for (int i = 0; i < n; i++) sync(i);
    for (int i = 0; i < n; i++) upd(i);
    for (auto &[_, vals] : evts) {
        for (int x : vals) {
            assert(st[x] == 0 || st[x] == 1);
            st[x] ^= 1;
            sync(x - 1);
            sync(x);
        }
        for (int x : vals) upd(x - 1), upd(x);
    }
    DBG(lef);
    int ans = 0;
    for (int i = n; i --> 0; ) {
        if (i + 1 < n) lef[i] = min(lef[i], lef[i + 1]);
        ans += max(i - lef[i], (int)0);
    }
    cout << ans << endl;
}
