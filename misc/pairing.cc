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
    int n; cin >> n;
    auto g = vector(n + 1, vector<array<int, 2>>());
    for (int i = 1; i < n; i++) {
        int x, y, z; cin >> x >> y >> z;
        g[x].push_back({y, z});
        g[y].push_back({x, z});
    }

    int res = 0;
    auto dfs = [&](int x, int p, int w, auto &&f) -> int {
        int sz = 1;
        for (auto [y, e] : g[x]) if (y != p) {
            sz += f(y, x, e, f);
        }
        res += min(sz, n - sz) * w;
        return sz;
    };
    dfs(1, 0, 0, dfs);
    cout << res << endl;
}
