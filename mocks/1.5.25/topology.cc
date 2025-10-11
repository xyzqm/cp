#include <bits/stdc++.h>
using namespace std;
#define int int64_t
#define ev(x, op, y) ((x) op (y)) % M
#define seq(x, op, y) x = (x op (y)) % M

const int N = 5e3 + 1;
const int M = 998244353;

int n, f[N], r[N], sz[N], dp[N], idp[N], F[N], I[N];
vector<int> g[N];

int inv(int x) {
    int r = 1;
    for (int p = (M - 2) << 1; p >>= 1; seq(x, *, x)) if (p & 1) seq(r, *, x);
    return r;
}

int split(int n, int k) { return F[n + k] * I[k] % M * I[n] % M; }
int choose(int n, int k) { return F[n] * I[k] % M * I[n - k] % M; }
int ichoose(int n, int k) { return I[n] * F[k] % M * F[n - k] % M; }

int dfs(int x) {
    dp[x] = 1;
    for (int y : g[x]) {
        seq(dp[x], *, dfs(y) * split(sz[x], sz[y]) % M);
        sz[x] += sz[y];
    }
    idp[x] = inv(dp[x]);
    return ++sz[x], dp[x];
}

// v[i] -> # of ways for parent to be at position i
void ac(int x, vector<int> v) {
    v.resize(n);
    partial_sum(v.begin(), v.end(), v.begin(), [](int v, int x) { return (v + x) % M; });
    r[x] = dp[x] * v[x - 1] % M * choose(n - x, sz[x] - 1) % M;
    for (int y : g[x]) {
        vector<int> nx(n - sz[x] + 2);
        for (int i = 1; i < nx.size(); i++) {
            nx[i] = v[i - 1] * dp[x] % M * choose(n - i - sz[y], sz[x] - 1 - sz[y]) % M * idp[y] % M * ichoose(sz[x] - 1, sz[y]) % M;
        }
        ac(y, nx);
    }
}

int32_t main() {
    // precompute factorials and inverse factorials
    F[0] = 1;
    for (int i = 1; i < N; i++) F[i] = F[i - 1] * i % M;
    I[N - 1] = inv(F[N - 1]);
    for (int i = N; i --> 1; ) I[i - 1] = I[i] * i % M;
    // solve
    cin >> n;
    for (int i = 2; i <= n; i++) {
        cin >> f[i];
        g[f[i]].push_back(i);
    }
    dfs(1);
    sz[0] = sz[1];
    ac(1, {1});
    for (int i = 1; i <= n; i++) cout << r[i] << " \n"[i == n];
}
