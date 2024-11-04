#include <bits/stdc++.h>
using ll = long long;
using namespace std;
#define int ll

const int N = 1e5 + 1;
int g[N], L[N], x[N];

struct J { int d, p, l;
    bool operator<(const J &o) const { return d != o.d ? d > o.d : p > o.p; }
} j[N];

struct P { int c, s; } bit[N];
// increment count of price i by x
void upd(int i, int x) {
    for (int p = i * x; i < N; i += i & -i) bit[i].c += x, bit[i].s += p;
}
// get count and sum of prices [0, r]
P query(int r) {
    int a = 0, b = 0;
    for (; r; r -= r & -r) a += bit[r].c, b += bit[r].s;
    return {a, b};
}

signed main() {
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> j[i].d >> j[i].p >> j[i].l;
    for (int i = 0; i < m; i++) cin >> g[i] >> L[i];
    for (int dif = (1 << 16); dif > 0; dif >>= 1) {
        fill(bit, bit + N, P{0, 0});
        vector<J> e(j, j + n);
        for (int i = 0; i < m; i++) e.push_back({x[i] + dif, -1, i});
        sort(e.begin(), e.end());
        for (auto [d, p, l] : e) {
            if (p == -1) { // processing a customer
                int a = 0, c = 0;
                for (int d = (1 << 16); d; d >>= 1) {
                    if ((c | d) < N - 1 && a + bit[c | d].c < L[l]) a += bit[c |= d].c;
                }
                a = query(++c).c;
                if (a >= L[l] && query(c).s - (a - L[l]) * c <= g[l]) x[l] += dif;
            } else {
                upd(p, l);
            }
        }
    }
    for (int i = 0; i < m; i++) cout << (x[i] ? x[i] : -1) << endl;
}
