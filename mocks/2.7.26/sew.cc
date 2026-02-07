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

// let dp[i] = PIE for this subtree w/ maximum depth i
// let's try combining with another subtree
// case 1: don't draw edge from root to this subtree => multiply all vals of dp[i]
// case 2: that subtree provides the maximum value => brute force add
// case 3: this subtree provides the maximum value => sz[rt] range multiplies of left
using T = array<int, 2>; // value, lazy multiply
struct lz : vector<T> {
    T& at(int idx) { return vector::at(size() - 1 - idx); } // reversed
    void mul(int l, int r, int x) {
        assert(l <= r);
        ::mul(at(l)[1], x);
        if (r < size()) ::mul(at(r)[1], inv(x));
    }
    void prop(int r) { // propagate all lazy tags in range [0, r)
        for (int i = 0; i < r; i++) {
            ::mul(at(i)[0], at(i)[1]);
            if (i + 1 < size()) ::mul(at(i + 1)[1], at(i)[1]);
            at(i)[1] = 1;
        }
    }
    vector<int> psum(int r) {
        prop(r);
        vector<int> res(r);
        for (int i = 0; i < r; i++) {
            if (i) res[i] = res[i - 1];
            ad(res[i], at(i)[0]);
        }
        return res;
    }
};

const int N = 1e6 + 1;
lz dp[N];
vector<int> g[N];

int l;

void dfs(int x, int p) {
    dp[x].push_back({1, 1});
    for (int y : g[x]) if (y != p) {
        dfs(y, x);
        dp[y].push_back({0, 1});
        if (dp[y].size() > dp[x].size()) dp[x].swap(dp[y]);
        auto x_sm = dp[x].psum(dp[y].size());
        auto y_sm = dp[y].psum(dp[y].size());
        // case 1: don't connect the two subtrees
        dp[x].mul(0, dp[x].size(), y_sm.back());
        // case 3: connect with x as maximum
        for (int i = 0; i < dp[y].size(); i++) {
            if (i <= l - i) dp[x].mul(i, l - i + 1, dp[y][i][0]);
        }
        dp[x].prop(dp[y].size());
        // case 2: connect subtree with y as strict maximum
        assert(x_sm[0] == 0);
        for (int i = 1; i < dp[y].size(); i++) {
            mul(dp[y][i][0], x_sm[max(min(l - i, i - 1), 0LL)]);
            ad(dp[x][i][0], dp[y][i][0]);
        }
    }

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
