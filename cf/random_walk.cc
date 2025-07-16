// https://codeforces.com/problemset/problem/1823/F
#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int M = 998244353;
struct mint {
    int v = 0;
    mint() {}
    mint(int v) : v((v % M + M) % M) {}
    operator int() { return v; }
    mint operator+(const mint o) const { return v + o.v; }
    mint operator*(const mint o) const { return v * o.v; }
    mint operator-(const mint o) const { return v - o.v; }
    mint inv() {
        mint x = v, r = 1;
        for (int p = (M - 2) * 2; p >>= 1; x = x * x) if (p & 1) r = r * x;
        return r;
    }
};

const int N = 2e5 + 1;
vector<int> g[N];
int fa[N], deg[N], n, s, t;
mint dp[N], dp_fa[N]; // E[c(x)] = dp[x] + E[c(fa(x))] * dp_fa[x]

void dfs(int x) {
    mint m = 1; // m * E[c(x)] = b + E[c(fa(x))];
    if (x == t) return (void)(dp[x] = 1, dp_fa[x] = 0);
    if (x == s) dp[x] = 1;
    for (int y : g[x]) if (y != fa[x]) {
        fa[y] = x; dfs(y);
        m = m - mint{deg[y]}.inv() * dp_fa[y];
        dp[x] = dp[x] + mint{deg[y]}.inv() * dp[y];
    }
    dp[x] = dp[x] * m.inv();
    dp_fa[x] = m.inv() * mint{deg[fa[x]]}.inv();
}

void push(int x) {
    if (x != s) dp[x] = dp[x] + dp[fa[x]] * dp_fa[x];
    if (x != t) for (int y : g[x]) if (y != fa[x]) push(y);
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> s >> t;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        ++deg[u], ++deg[v];
    }
    deg[t] = 0;
    dfs(s); push(s);
    for (int i = 1; i <= n; i++) cout << dp[i] << " \n"[i == n];
}
