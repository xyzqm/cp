#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int M = 998244353;

int inv(int x) {
    assert(x != 0);
    int r = 1;
    for (int y = M - 2; y; x = x * x % M, y >>= 1) if (y & 1) r = r * x % M;
    return r;
}

inline void mul(int &a, const int b) { a = a * b % M; }

struct BIT : vector<int> {
    BIT(int n) : vector(n + 1, 1) {}
    void upd(int i, int x) { // multiply i by x
        for (++i; i < size(); i += i & -i) mul(at(i), x);
    }
    int query(int r) { // prod in range [0, r)
        int res = 1;
        for (; r; r -= r & -r) mul(res, at(r));
        return res;
    }
};

vector<int> sieve(int mx) { // sieves numbers in range [0, mx)
    vector<int> lp(mx, mx);
    vector<int> pr;
    for (int i = 2; i < mx; i++) {
        if (lp[i] == mx) pr.push_back(lp[i] = i);
        for (int x : pr) {
            if (x > lp[i] || i * x >= mx) break;
            lp[i * x] = x;
        }
    }
    return lp;
}

const int MX = 1e6 + 1;

int32_t main() {
    auto lp = sieve(MX);
    vector<int> phi(MX), i_phi(MX); // calculate totients for primes
    for (int i = 2; i < MX; i++) if (lp[i] == i) i_phi[i] = inv(phi[i] = M + 1 - inv(i));

    int n; cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;
    int q; cin >> q;
    vector<vector<array<int, 2>>> qs(n + 1);
    for (int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        qs[r].push_back({--l, i});
    }
    vector<int> res(q), lst(MX, -1);
    BIT bit(n);
    for (int r = 0; r <= n; r++) {
        for (auto &[l, i] : qs[r]) res[i] = bit.query(r) * inv(bit.query(l)) % M;
        if (r < n) {
            bit.upd(r, a[r]);
            for (int l = lp[a[r]]; a[r] > 1; l = lp[a[r] /= lp[a[r]]]) {
                if (int j = lst[l]; j >= 0) bit.upd(j, i_phi[l]);
                bit.upd(lst[l] = r, phi[l]);
            }
        }
    }
    for (int i = 0; i < q; i++) cout << res[i] << endl;
}
