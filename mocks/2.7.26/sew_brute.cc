#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

const int M = 1e9 + 7;
void mul(int &a, const int b) { a = a * b % M; }
void ad(int &a, const int b) { a = (a + b) % M; }
int inv(int x) {
    int res = 1;
    for (int pw = M - 2; pw; x = x * x % M, pw >>= 1) if (pw & 1) res = res * x % M;
    return res;
}

int l;

const int N = 1e5 + 1;
const int L = 101;
int dp[N][L][2];

void dfs(int x, int p) {
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n >> l;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    DBG(dp[1]);
}
