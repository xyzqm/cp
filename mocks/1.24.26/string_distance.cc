#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

void smax(int &a, const int b) { a = max(a, b); }

template <int N, int M>
struct mat : array<array<int, M>, N> {};

template <int A, int B, int C>
mat<A, C> operator*(const mat<A, B> &a, const mat<B, C> &b) {
    mat<A, C> c{};
    for (int i = 0; i < A; i++) for (int k = i; k < B; k++) for (int j = k; j < C; j++) {
        smax(c[i][j], a[i][k] + b[k][j]);
    }
    return c;
}


const int N = 1e5;
const int K = 21;
using st = mat<K, K>;

int n;
st sgt[2 * N];
void build() {
    for (int i = n; i --> 0; ) sgt[i] = sgt[i << 1] * sgt[i << 1 | 1];
}

int query(int l, int r) { // [l, r)
    st res_l{}, res_r{};
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res_l = res_l * sgt[l++];
        if (r & 1) res_r = sgt[--r] * res_r;
    }
    st res = res_l * res_r;
    int ans = 0;
    for (auto &r : res) for (auto &x : r) smax(ans, x);
    return ans;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    string a, b; cin >> a >> b;
    n = a.size();
    int sz = b.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < sz; j++) if (a[i] == b[j]) {
            for (int k = j + 1; k <= sz; k++) sgt[n + i][j][k] = 1;
        }
    }
    build();
    int q; cin >> q;
    while (q--) {
        int l, r; cin >> l >> r;
        int lcs = query(--l, r);
        cout << r - l + b.size() - 2 * lcs << endl;
    }
}
