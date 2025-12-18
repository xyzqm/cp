#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

using dat = int;
dat ad(dat a, dat b) { return max(a, b); }
dat ID = 0;

// 0-indexed iterative segment tree
struct sgt : vector<dat> {
    int n;
    sgt(size_t n) : vector(2 * bit_ceil(n), ID), n(bit_ceil(n)) {}
    void upd(int i, int x) { // increments a[i] by x
        for (at(i += n) += x; i >>= 1; ) at(i) = ad(at(i << 1), at(i << 1 | 1));
    }
    int walk(int l, int tgt) { // find first r s.t. [l, r] >= tgt, or -1 if no such r exists
        int cur = ID;
        for (l += n; l < size() && l; ) {
            if (ad(cur, at(l)) < tgt) {
                cur = ad(cur, at(l));
                while (l & 1) l >>= 1;
                if (l) ++l;
            }
            else l <<= 1;
        }
        assert(!l || l >= 2 * n);
        return l ? (l >> 1) - n : -1;
    }
};

int32_t main() {
    int n, q; cin >> n >> q;
    sgt st(n);
    for (int i = 0, x; i < n; i++) {
        cin >> x;
        st.upd(i, x);
    }
    while (q--) {
        int a; cin >> a;
        int i = st.walk(0, a);
        cout << i + 1 << " ";
        if (i >= 0) st.upd(i, -a);
    }
    cout << endl;
}
