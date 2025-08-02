// https://atcoder.jp/contests/arc196/tasks/arc196_d
#include <bits/stdc++.h>
#include <atcoder/segtree>

using namespace std;
using namespace atcoder;

const int N = 4e5 + 5;
int n, m, q, s[N], t[N], c[N], min_l[N];

template <int K> constexpr int e() { return K; }
int mn(int a, int b) { return min(a, b); }
int mx(int a, int b) { return max(a, b); }
struct T {
    segtree<int, mn, e<N>> l;
    segtree<int, mx, e<0>> r;
    T() : l(N), r(N) {}
} st[2];

int main() {
    cin >> n >> m >> q;
    int l = 1;
    auto rem = [&]() {
        st[c[l]].l.set(t[l], N);
        st[c[l]].r.set(s[l], 0);
        ++l;
    };
    for (int i = 1; i <= m; i++) {
        cin >> s[i] >> t[i];
        c[i] = s[i] > t[i]; // 0 = ->, 1 = <-
        if (c[i]) swap(s[i], t[i]);
        while (
            st[c[i]].l.prod(s[i] + 1, t[i] + 1) <= s[i] ||
            st[c[i]].r.prod(s[i], t[i]) >= t[i] ||
            st[c[i] ^ 1].l.get(t[i]) != N ||
            st[c[i] ^ 1].r.get(s[i]) != 0
        ) rem();
        min_l[i] = l;
        assert(st[c[i]].l.get(t[i]) == N);
        assert(st[c[i]].r.get(s[i]) == 0);
        st[c[i]].l.set(t[i], s[i]);
        st[c[i]].r.set(s[i], t[i]);
    }
    while (q--) {
        int l, r; cin >> l >> r;
        cout << vector{"No", "Yes"}[l >= min_l[r]] << endl;
    }
}
