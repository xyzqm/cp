#include <bits/stdc++.h>
using namespace std;
#define int int64_t
#define all(v) v.begin(), v.end()
#define seq(a, op, b) a = a op (b)

const int M = 998244353;
const int N = 2e5 + 1;
struct mint { int x;
    mint(int x = 0) : x((x % M + M) % M) {}
    operator int() { return x; }
};
mint inv(mint x) {
    mint r = 1;
    for (int y = (M - 2) << 1; y >>= 1; x = x * x % M) if (y & 1) r = r * x;
    return r;
}
mint iv[N];

// linear function
struct F { mint w, b;
    F operator()(F &o) { return {w * o.w, w * o.b + b}; }
    bool zero() { return !w && !b; }
};
using T = array<F, 2>;
T operator+(T a, T b) {
    return {
        b[0].zero() ? a[0] : a[1](b[0]),
        b[1].zero() ? a[0] : a[1](b[1])
    };
}
T sgt[2 * N];

int n;

T id = {{{0, 0}, {1, 0}}};
// composes f[l, r)
T compose(int l, int r) {
    T L = id, R = id;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) L = L + sgt[l++];
        if (r & 1) R = R + sgt[--r];
    }
    return L + R;
}

void upd(int i, T f) { for (sgt[i += n] = f; i >>= 1; ) sgt[i] = sgt[i << 1] + sgt[i << 1 | 1]; }

vector<int> g[N];
int sz[N], fa[N], opt[N];
int dfs_sz(int x, int p) {
    if (p) g[x].erase(find(all(g[x]), fa[x] = p));
    for (int y : g[x]) sz[x] += dfs_sz(y, x);
    return ++sz[x];
}

int hld_t = 0, idx[N], t[N], b[N];
void hld(int x, int p) {
    b[t[x] = p] = x;
    idx[x] = hld_t++;
    for (int &y : g[x]) if (sz[y] > g[x][0]) swap(g[x][0], y);
    for (int y : g[x]) {
        if (y == g[x][0]) hld(y, p);
        else hld(y, y);
    }
}

bool esc[N];
mint dp[N], sdp[N];

void fix(int x) {
    if (!x) return;
    if (esc[x]) upd(idx[x], {{{0, 1}, {0, 1}}});
    else upd(idx[x], {{{iv[max(opt[x] - 1, 0LL)], sdp[x] * iv[max(opt[x] - 1, 0LL)]}, {iv[opt[x]], sdp[x] * iv[opt[x]]}}});
}

void toggle(int x) {
    esc[x] ^= 1;
    while (x >= 1) {
        fix(x);
        mint fin = compose(idx[t[x]], idx[b[t[x]]] + 1)[0].b;
        seq(sdp[fa[t[x]]], +, fin - dp[t[x]]);
        if (fin && !dp[t[x]]) ++opt[fa[t[x]]];
        if (!fin && dp[t[x]]) --opt[fa[t[x]]];
        dp[t[x]] = fin;
        x = fa[t[x]];
    }
}

int32_t main() {
    // precompute inverses
    // iv[0] = 1e18; // this value should never be used
    for (int i = 1; i < N; i++) iv[i] = inv(i);
    // input tree
    int q; cin >> n >> q;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs_sz(1, 0), hld(1, 1);
    while (q--) {
        int x; cin >> x;
        toggle(x);
        int y = compose(idx[1], idx[b[1]] + 1)[0].b;
        cout << y << endl;
    }
}
