#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

void ac() {
    int n; cin >> n;
    auto g = vector(n + 1, vector<int>());
    vector<int> rts = {1};
    for (int i = 2; i <= n; i++) {
        int fa; cin >> fa;
        if (fa == -1) rts.push_back(i);
        else {
            g[fa].push_back(i);
            g[i].push_back(fa);
        }
    }

    auto dfs = [&](this auto dfs, int x, int p) -> pair<int, int> { // return {dist, node}
        pair<int, int> res = {-1, x};
        for (int y : g[x]) if (y != p) {
            res = max(res, dfs(y, x));
        }
        return ++res.first, res;
    };
    vector<int> ds;
    for (int rt : rts) {
        auto [_, u] = dfs(rt, 0);
        auto [diam, v] = dfs(u, 0);
        ds.push_back(diam);
    }
    DBG(ds);
    int mx = ranges::fold_left(ds, 0LL, std::plus<>()) + rts.size() - 1;
    cout << mx << " ";
    for (int &d : ds) d = (d + 1) / 2;
    ranges::sort(ds, greater());
    if (ds.size() == 1) cout << ds[0] << "\n";
    else cout << ds[0] + ds[1] + 1 + (ds.size() > 2 && ds[0] == ds[1] == ds[2]) << "\n";
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
