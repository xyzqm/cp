#include <iostream>
#include <tuple>
#include <vector>
using namespace std;
const int M = 1e6 + 1;
int n, m, seg[4 * M], lazy[4 * M];
void push(int p, int l, int r) {
    if (lazy[p]) {
        seg[p] += lazy[p];
        if (l != r) {
            lazy[2 * p] += lazy[p];
            lazy[2 * p + 1] += lazy[p];
        }
        lazy[p] = 0;
    }
}
void upd(int i, int j, int x, int p = 1, int l = 1, int r = m - 1) {
    push(p, l, r);
    if (r < i || l > j) return;
    else if (i <= l && r <= j) {
        lazy[p] += x;
        push(p, l, r);
    } else {
        int m = (l + r) >> 1;
        upd(i, j, x, 2 * p, l, m);
        upd(i, j, x, 2 * p + 1, m + 1, r);
        seg[p] = min(seg[2 * p], seg[2 * p + 1]);
    }
}
int main() {
    cin >> n >> m;
    vector<tuple<int, int, int>> R;
    for (int i = 0; i < n; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        --y;
        R.emplace_back(w, x, y);
    }
    sort(R.begin(), R.end());
    int l = 0, r = 1, ans = 1e9;
    auto [w1, x1, y1] = R[0];
    upd(x1, y1, 1);
    while (l < r) {
        auto [wl, xl, yl] = R[l];
        if (seg[1]) {
            // cout << l << " " << r << endl;
            ans = min(ans, get<0>(R[r - 1]) - wl);
            upd(xl, yl, -1);
            ++l;
        } else if (r < n) {
            auto [wr, xr, yr] = R[r];
            upd(xr, yr, 1);
            ++r;
        } else break;
    }
    cout << ans << endl;
}