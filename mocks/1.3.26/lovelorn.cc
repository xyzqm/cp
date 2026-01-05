#include <bits/stdc++.h>
using namespace std;

#define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

const int M = 998244353;

struct bit : vector<int> {
    bit(int n) : vector(n + 1, 1) {}
    void upd(int i, int x) {
        for (++i; i < size(); i += i & -i) at(i) = at(i) * x % M;
    }
    int query(int r) {
        int res = 1;
        for (; r; r -= r & -r) res = res * at(r) % M;
        return res;
    }
};

int iv(int x) {
    int res = 1;
    for (int pw = M - 2; pw; pw >>= 1, x = x * x % M) if (pw & 1) res = res * x % M;
    return res;
}

const int MX = 1e7 + 1;
int lp[MX], lst[MX], inv[MX];
vector<int> pr;

int32_t main() {
    pr.reserve(700000);
    for (int i = 2; i < MX; i++) {
        if (!lp[i]) lp[i] = i, pr.push_back(i);
        for (int x : pr) {
            if (i * x >= MX || x > lp[i]) break;
            lp[i * x] = x;
        }
    }

    inv[1] = 1;
    for (int i = 2; i < MX; i++) inv[i] = M - M / i * inv[M % i] % M;

    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;
    int q; cin >> q;
    vector<int> res(q + 1);
    vector<array<int, 3>> qs(q);
    for (int qi = 0; auto &[r, l, i] : qs) {
        cin >> l >> r; --l;
        i = qi++;
    }
    for (int i = 1; i <= n; i++) qs.push_back({i, 0, q});
    sort(qs.begin(), qs.end());

    bit ft(n);
    DBG(ft);
    for (auto [r, l, i] : qs) {
        for (int x = a[r - 1]; x > 1; x /= lp[x]) {
            int pr = lp[x];
            if (lst[pr]) ft.upd(lst[pr] - 1, inv[pr]);
            ft.upd((lst[pr] = r) - 1, pr);
            DBG(x);
            DBG(ft);
        }
        res[i] = ft.query(r) * iv(ft.query(l)) % M;
    }
    for (int i = 0; i < q; i++) cout << res[i] << endl;
}
