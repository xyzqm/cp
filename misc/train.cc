// https://qoj.ac/contest/1684/problem/8725
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int inf = 1e9 + 1;

const int N = 1e5 + 1;

struct PST { int v; array<int, 2> c; } pst[35 * N];
int cn = 0;

int node(int v, array<int, 2> c = {0, 0}) { return pst[++cn] = {v, c}, cn; }

int query(int p, int ql, int qr, int l = 0, int r = inf) {
    auto [v, c] = pst[p];
    if (!p || ql >= r || qr <= l) return 0;
    else if (ql <= l && r <= qr) return v;
    else {
        int m = (l + r) >> 1;
        return query(c[0], ql, qr, l, m) + query(c[1], ql, qr, m, r);
    }
}

int upd(int p, int i, int l = 0, int r = inf) {
    auto [v, c] = pst[p];
    if (r - l == 1) return node(++v, c);
    else {
        int m = (l + r) >> 1;
        if (i < m) c[0] = upd(c[0], i, l, m);
        else c[1] = upd(c[1], i, m, r);
        return node(pst[c[0]].v + pst[c[1]].v, c);
    }
}

ll solve(
    int N, int M, int W, vector<int> T,
    vector<int> X, vector<int> Y,
    vector<int> A, vector<int> B, vector<int> C,
    vector<int> L, vector<int> R
) {
    vector<int> meals(W);
    iota(meals.begin(), meals.end(), 0);
    sort(meals.begin(), meals.end(), [&](int i, int j) { return L[i] < L[j]; });
    vector<pair<int, int>> psts = {{0, 0}};
    for (int i : meals) {
        psts.push_back({L[i], upd(psts.back().second, R[i])});
    }
    auto subranges = [&](int l, int r) { // subranges of (l, r)
        auto it = prev(upper_bound(psts.begin(), psts.end(), make_pair(l, inf)));
        return query(psts.back().second, l, r) - query(it->second, l, r);
    };
    struct V { int i, l, r; };
    vector<deque<V>> st(N); // monotonic
    st[0].push_back({-1, 0, inf});
    vector<ll> dp(M, 1e18);
    vector<pair<int, vector<int>*>> ord;
    for (int i = 0; i < M; i++) ord.push_back({i, &A}), ord.push_back({i, &B});
    sort(ord.begin(), ord.end(), [&](auto x, auto y) {
        int a = x.second->at(x.first), b = y.second->at(y.first);
        return a == b ? x.second == &B : a < b;
    });
    auto cost = [&](int i, int t, int X) { // cost to wait until time t after getting off train i on planet X
        return ll(i < 0 ? 0 : dp[i]) + 1LL * subranges(i < 0 ? 0 : B[i], t) * T[X];
    };
    ll r = 1e18;
    for (auto [i, v] : ord) {
        if (v == &A) {
            auto &dq = st[X[i]];
            if (!dq.size()) continue; // no valid transitions
            while (A[i] >= dq.front().r) dq.pop_front();
            dp[i] = C[i] + cost(dq.front().i, A[i], X[i]);
            if (Y[i] == N - 1) r = min(r, cost(i, inf, N - 1));
        }
        else {
            if (dp[i] == 1e18) continue; // impossible state
            auto &dq = st[Y[i]];
            while (
                dq.size() &&
                B[i] <= dq.back().l &&
                cost(i, dq.back().l, Y[i]) <= cost(dq.back().i, dq.back().l, Y[i])
            ) dq.pop_back();
            int x = inf;
            if (!dq.size()) x = B[i];
            else {
                for (int d = inf; d > 0; d /= 2) {
                    while (x - d >= max(B[i], dq.back().l) && cost(i, x - d, Y[i]) <= cost(dq.back().i, x - d, Y[i])) x -= d;
                }
                dq.back().r = x;
            }
            dq.push_back({i, x, inf});
        }
    }
    return r == 1e18 ? -1 : r;
}

int main() {
    int n, m, w; cin >> n >> m >> w;
    vector<int> t(n);
    for (int i = 0; i < n; i++) cin >> t[i];
    vector<int> x(m), y(m), a(m), b(m), c(m);
    for (int i = 0; i < m; i++) cin >> x[i] >> y[i] >> a[i] >> b[i] >> c[i];
    vector<int> l(w), r(w);
    for (int i = 0; i < w; i++) cin >> l[i] >> r[i];
    cout << solve(n, m, w, t, x, y, a, b, c, l, r) << endl;
}
