// https://qoj.ac/contest/1398/problem/7607
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9 + 7;

// util for log
constexpr int lg(int x) {
  return x ? 31 - __builtin_clz(x) : -1;
}

// mod utils
ll& ad(ll &a, ll b) { return a = (a + b) % M; }
ll& mul(ll &a, ll b) { return a = (a * b) % M; }

const int N = 3e5 + 1;
const int K = 20;

vector<int> g[N];
ll dp[N][K][2], dead[N]; // second dimension -> whether edge to parent is incoming/outgoing
int mx[N], sz[N]; // max power made

ll dfs(int x, int p) {
    int K = 1;
    for (int y : g[x]) if (y != p) {
        dfs(y, x);
        sz[x] += sz[y];
        K = max(K, mx[y] + 1);
    }
    sort(g[x].begin(), g[x].end(), [](int y, int z) { return mx[y] < mx[z]; });
    K = min(K, lg(++sz[x]) + 1);
    vector<array<ll, 2>> tmp(1 << K);
    tmp[0][0] = 1; // second dimension -> # of outgoing edges to children
    for (int y : g[x]) if (y != p) {
        for (int msk = (1 << mx[y]); msk --> 0; ) {
            ll non = dead[y]; // ways to do nothing
            for (int p = 0; p < mx[y]; p++) {
                // don't use incoming edge from child
                ad(non, dp[y][p][1]);
                if (msk >> p & 1) continue;
                // add incoming edge from child
                for (int o : {0, 1}) if (!o || p < lg(msk)) ad(tmp[msk | (1 << p)][o], tmp[msk][o] * dp[y][p][1]);
                // make outgoing edge to child
                if (p > lg(msk)) ad(tmp[msk | (1 << p)][1], tmp[msk][0] * dp[y][p][0]);
            }
            for (int o : {0, 1}) mul(tmp[msk][o], non);
        }
    }
    mx[x] = 0;
    ll r = 0;
    for (int msk = 0; msk < (1 << K); msk++) {
        if (__builtin_popcount(msk + 1) == 1) {
            ad(r, dp[x][__builtin_ctz(msk + 1)][1] = tmp[msk][0]); // can't have outgoing edges to children
            ad(dead[x], tmp[msk][1]); // # of ways for this node to have nothing left
            if (tmp[msk][0]) mx[x] = max(mx[x], __builtin_ctz(msk + 1) + 1); // calculate max value on this node
        }
    }
    ad(r, dead[x]);
    // try adding one incoming edge
    for (int k = 0; k < K; k++) for (int msk = 0; msk < (1 << K); msk++) {
        if (int msk_ = msk + (1 << k) + 1; __builtin_popcount(msk_) == 1) {
            ad(dp[x][k][0], tmp[msk][0] + (k < lg(msk)) * tmp[msk][1]); // doesn't matter whether there are outgoing edges to children
        }
    }
    return r;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    cout << dfs(1, 0) << endl;
}
