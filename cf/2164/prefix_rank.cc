// https://codeforces.com/contest/2164/submission/360807941
#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

const int M = 998244353;

int inv(int x) {
    int r = 1;
    for (int pw = M - 2; pw; pw >>= 1, x = x * x % M) if (pw & 1) r = r * x % M;
    return r;
}

void ac() {
    int n; cin >> n;
    vector<int> fac(n + 1, 1), i_fac(n + 1, 1);
    for (int i = 1; i <= n; i++) fac[i] = i * fac[i - 1] % M;
    i_fac[n] = inv(fac[n]);
    for (int i = n; i --> 0; ) i_fac[i] = (i + 1) * i_fac[i + 1] % M;
    DBG(fac);
    DBG(i_fac);
    auto split = [&](int x, int y) { return fac[x + y] * i_fac[x] % M * i_fac[y] % M; };

    vector<int> fa(n + 1);
    auto g = vector(n + 1, vector<int>());
    for (int i = 2; i <= n; i++) {
        cin >> fa[i];
        g[fa[i]].push_back(i);
    }
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<int> sz(n + 2);
    int w = 1;
    vector<int> ord = {n + 1};

    auto dfs = [&](this auto dfs, int x) -> void {
        int prv = 0;
        swap(prv, sz[ord[a[x]]]);
        ord.insert(ord.begin() + a[x], x);
        for (int y : g[x]) dfs(y);
        int tot = sz[ord[a[x]]] + sz[ord[a[x] + 1]] + 1;
        ord.erase(ord.begin() + a[x]);
        // DBG(sz[ord[a[x]]]);
        // DBG(tot);
        w = w * split(prv, tot) % M;
        sz[ord[a[x]]] = prv + tot;
    };

    dfs(1);
    cout << w << endl;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
