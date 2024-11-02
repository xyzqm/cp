#include <bits/stdc++.h>
using namespace std;
using ld = double;
using ll = long long;

const int N = 3e5 + 1;
const ll inf = 4e18;

// function of form a + b sqrt(c + kx)
struct fn { ld a = inf; ll b, c, k = 1;
    ld operator()(ll x) { return k * x + c < 0 ? (a == inf ? a : -inf * b) : a + b * sqrt(k * x + c); }
};

// sparse segment tree
template <typename T>
struct SGT { vector<T> sgt; vector<int> lc, rc;

    SGT() : sgt(2), lc(2), rc(2) {}
    // helper to get left/right child
    int get(vector<int> &a, int p) {
        // cout << p << endl;
        if (a[p]) return a[p];
        sgt.push_back({});
        lc.push_back(0), rc.push_back(0);
        return a[p] = sgt.size() - 1;
    }

    // updates range [l, r) with f
    void upd(ll l, ll r, fn f, int p = 1, ll i = 0, ll j = +inf) {
        if (l >= j || i >= r) return;
        ll m = (i + j) / 2;
        if (l <= i && j <= r) {
            if constexpr (is_same_v<T, fn>) {
                if (sgt[p](m) >= f(m)) swap(sgt[p], f);
                if (sgt[p](l) < f(l) && m != i) upd(m, j, f, get(lc, p), m, j);
                else if (m != j) upd(i, m, f, get(rc, p), i, m);
            }
            else {
                sgt[p].upd(0, +inf, f);
            }
        }
        else {
            upd(l, r, f, get(lc, p), i, m);
            upd(l, r, f, get(rc, p), m, j);
        }
    }

    // gets the min value of f(x)
    ld query(ll x, ll y = 0, int p = 1, ll i = 0, ll j = +inf) {
        if (j - i == 1) return sgt[p](y ? y : x);
        ll m = (i + j) / 2;
        ld r = inf;
        if (x < m) { if (lc[p]) r = query(x, y, lc[p], i, m); }
        else if (rc[p]) r = query(x, y, rc[p], m, j);
        return min(r, sgt[p](y ? y : x));
    }
    ld operator()(ll x) {
        if constexpr (is_same_v<T, fn>) return query(x);
        else assert(false);
    }
};
SGT<fn> lct; // li-chao tree
SGT<SGT<fn>> sgt; // other tree

ld h[N], v[N], u[N], dp[N];

// two cases:
// 2h_f + u_f^2 >= 2h_i + v_i^2 (initial speed of v_i)
//  time = sqrt(2h_i + v_i^2 - 2h_f) - v_i (use sgt)
// otherwise (2h_f + u_f^2 < 2h_i + v_i^2), final speed of u_f
//  time = u_f - sqrt(u_f^2 + 2h_f - 2h_i) (use lct)

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) cin >> h[i] >> v[i] >> u[i];
    for (int i = n; i --> 0; ) {
        if (i < n - 1) {
            // cout << i << "----" << endl;
            dp[i] = min(sgt.query(2 * h[i] + u[i] * u[i], 2 * h[i]), lct.query(u[i] * u[i] + 2 * h[i]) + u[i]);
            // cout << dp[i] << " ";
        }
        sgt.upd(2 * h[i] + v[i] * v[i], inf, {dp[i] - v[i], 1, 2 * h[i] + v[i] * v[i], -1});
        lct.upd(2 * h[i], 2 * h[i] + v[i] * v[i], {dp[i], -1, -2 * h[i]});
    }
    if (dp[0] >= inf) cout << -1 << endl;
    else cout << fixed << setprecision(8) << dp[0] << endl;
}
