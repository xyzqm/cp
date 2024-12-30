#include <bits/stdc++.h>
#define int long long
using namespace std;

const int M = 998244353;

struct mint {
    int v;
    mint() : v(0) {}
    mint(int v) : v(((v % M) + M) % M) {}
    operator int() { return v; }
    mint operator+=(mint v) { return *this = *this + v; }
    mint exp(int k) {
        mint r = 1, x = v;
        for (k <<= 1; k >>= 1; x = x * x) if (k & 1) r = r * x;
        return r;
    }
    mint inv() { assert(mint(*this * exp(M - 2)).v == 1); return exp(M - 2); }
};

const int N = 1e4 + 1;
const int K = 61;
mint F[K], I[K], tot[K][K][K], dp[N];

mint C(int n, int k) { return F[n] * I[k] % M * I[n - k]; }

int x[N], y[N], z[N], v[N];
bool sub(int a, int b) { return (a & b) == a; }
mint w(int i, int j) {
    int a = __builtin_popcountll(x[j] - x[i]);
    int b = __builtin_popcountll(y[j] - y[i]);
    int c = __builtin_popcountll(z[j] - z[i]);
    return tot[a][b][c];
}
vector<int> g[N];

mint r = 0;
int o;
mint dfs(int x) {
    if (v[x]) return dp[x];
    v[x] = 1;
    for (int y : g[x]) {
        dp[x] += dfs(y) * w(y, x) % M * (M - 1);
    }
    return dp[x];
}

signed main() {
    // precomputation
    F[0] = 1;
    for (int i = 1; i < K; i++) F[i] = F[i - 1] * i;
    I[K - 1] = F[K - 1].inv();
    for (int i = K - 1; i > 0; i--) {
       I[i - 1] = I[i] * i;
    }
    tot[0][0][0] = 1;
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < K; j++) {
            for (int k = 0; k < K; k++) {
                for (int d = 1; d <= max({i, j, k}); d++) {
                    if (d <= i) tot[i][j][k] += tot[i - d][j][k] * C(i, d);
                    if (d <= j) tot[i][j][k] += tot[i][j - d][k] * C(j, d);
                    if (d <= k) tot[i][j][k] += tot[i][j][k - d] * C(k, d);
                }
            }
        }
    }
    // input
    int n, m, r; cin >> n >> m >> r;
    cin >> o;
    for (int i = 1; i <= o; i++) {
        cin >> x[i] >> y[i] >> z[i];
    }
    // construct graph, with edges to each obstacle from its subsets
    ++o, x[o] = n, y[o] = m, z[o] = r;
    for (int i = 0; i <= o; i++) for (int j = 0; j <= o; j++) if (i != j) {
        if (sub(x[i], x[j]) && sub(y[i], y[j]) && sub(z[i], z[j])) g[j].push_back(i);
    }
    // brute force DFS
    dp[0] = M - 1;
    cout << dfs(o) << endl;
}
