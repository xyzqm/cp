#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

const int M = 1e9 + 7;

void ad(int &a, int b) { a = (a + b) % M; }

using st = array<vector<int>, 2>;
st operator+(const st &a, const st &b) {
    st c{};
    auto inc = [&](int i, int j, int x) {
        if (!x) return;
        while (j >= c[i].size()) c[i].emplace_back();
        ad(c[i][j], x);
    };
    for (int ta : {0, 1}) for (int tb : {0, 1}) for (int i = 0; i < a[ta].size(); i++) for (int j = 0; j < b[tb].size(); j++) {
        int w = a[ta][i] * b[tb][j] % M;
        if (ta && tb) inc(1, i + j, w);
        else if (!ta && !tb) inc(0, i + j, w);
        else if (ta) inc(1, i, w);
        else inc(1, j, w);
    }
    return c;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, L, R, k; cin >> n >> L >> R >> k;
    vector<int> a(n + 1), fa(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 2; i <= n; i++) cin >> fa[i];
    DBG("here");
    auto colors = vector(n + 1, vector(n + 1, vector<int>()));
    auto dp = vector(n + 1, st{{{1}, {0}}});
    auto g = vector(n + 1, vector<int>());
    for (int i = n; i > 0; i--) {
        // g[i] = {i};
        // g[i].swap(colors[i][a[i]]);
        for (int j : colors[i][a[i]]) dp[i] = dp[i] + dp[j];
        auto inc = [&](int t, int j, int x) {
            if (!x) return;
            while (j >= dp[i][t].size()) dp[i][t].push_back(0);
            ad(dp[i][t][j], x);
        };
        // try marking this node
        dp[i][0].push_back(0);
        dp[i][1].push_back(0);
        for (int j = dp[i][1].size(); j --> 2; ) inc(1, j, dp[i][1][j - 1]);
        for (int j = k - 1; j < dp[i][0].size(); j++) inc(1, 1, dp[i][0][j]);
        for (int j = k; j --> 1; ) inc(0, j, dp[i][0][j - 1]);

        colors[i][a[i]] = {i};
        for (int c = 1; c <= n; c++) colors[fa[i]][c].insert(colors[fa[i]][c].end(), colors[i][c].begin(), colors[i][c].end());
    }
    DBG(g);
    DBG(dp);
    // DBG(colors[0]);
    st base = {{{1}, {0}}};
    for (int c = 1; c <= n; c++) for (int i : colors[0][c]) {
        DBG(i);
        DBG(dp[i]);
        base = base + dp[i];
    }
    DBG(base);
    int ans = 0;
    for (int i = L; i < min(R + 1, (int)base[1].size()); i++) ad(ans, base[1][i]);
    cout << ans << endl;
}
