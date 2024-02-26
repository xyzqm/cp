#include <iostream>
#include <vector>
#include <tuple>
#include <assert.h>
#include <cmath>
#define int long long
using namespace std;
const int N = 5e5;
const int K = 20;
int n, q, h[N], nxt[N], prv[N], stl[N][K], str[N][K], ans[N], seg[4 * N];
int query(int i, int j, int p = 1, int l = 0, int r = n - 1) {
    if (r < i || l > j) return 0;
    if (i <= l && r <= j) return seg[p];
    int m = (l + r) / 2;
    return query(i, j, 2 * p, l, m) + query(i, j, 2 * p + 1, m + 1, r);
}
void upd(int i, int x, int p = 1, int l = 0, int r = n - 1) {
    if (l == r) seg[p] += x;
    else {
        int m = (l + r) / 2;
        if (i <= m) upd(i, x, 2 * p, l, m);
        else upd(i, x, 2 * p + 1, m + 1, r);
        seg[p] = seg[2 * p] + seg[2 * p + 1];
    }
}
void build() {
    for (int i = 0; i < n; i++) stl[i][0] = str[i][0] = h[i];
    for (int j = 1; j < K; j++) {
        for (int i = 0; i < n; i++) {
            stl[i][j] = stl[i][j - 1];
            if (int k = i + (1 << (j - 1)); k < n) stl[i][j] = max(stl[i][j], stl[k][j - 1]);
            str[i][j] = str[i][j - 1];
            if (int k = i - (1 << (j - 1)); k >= 0) str[i][j] = max(str[i][j], str[k][j - 1]);
        }
    }
}
int mx(int l, int r) {
    int k = log2(r - l);
    return max(stl[l][k], str[r - 1][k]);
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    fill(nxt, nxt + N, -1);
    fill(prv, prv + N, -1);
    cin >> n >> q;
    vector<int> st;
    for (int i = 0; i < n; i++) {
        cin >> h[i];
        while (st.size() && h[st.back()] <= h[i]) {
            nxt[st.back()] = i;
            st.pop_back();
        }
        if (st.size()) prv[i] = st.back();
        st.push_back(i);
    }
    build();
    vector<tuple<int, bool, int, int>> R;
    for (int i = 0; i < n; i++) {
        if (nxt[i] != -1 && i + 1 < nxt[i]) R.emplace_back(i, true, nxt[i], h[i] - mx(i + 1, nxt[i]));
        if (prv[i] != -1 && prv[i] + 1 < i) R.emplace_back(prv[i], true, i, h[i] - mx(prv[i] + 1, i));
    }
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        --l, --r;
        R.emplace_back(l, false, r, i);
    }
    sort(R.begin(), R.end(), greater<tuple<int, bool, int, int>>());
    for (auto [l, q, r, i] : R) {
        if (!q) ans[i] = query(0, r);
        else upd(r, i * (r - l - 1));
    }
    for (int i = 0; i < q; i++) cout << ans[i] << endl;
}