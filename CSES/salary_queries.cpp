#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#define COMB(a, b) (a) + (b)
using namespace std;
using ll = long long;
const int N = 6e5 + 1;
int n, q, a[N];
ll seg[4 * N];
vector<int> v;
ll query(int i, int j, int p = 1, int l = 1, int r = v.size()) {
    if (r < i || l > j) return 0;
    if (i <= l && r <= j) return seg[p];
    int m = (l + r) / 2;
    return COMB(query(i, j, 2 * p, l, m), query(i, j, 2 * p + 1, m + 1, r));
}
void upd(int i, int x, int p = 1, int l = 1, int r = v.size()) {
    if (l == r) seg[p] += x;
    else {
        int m = (l + r) / 2;
        if (i <= m) upd(i, x, 2 * p, l, m);
        else upd(i, x, 2 * p + 1, m + 1, r);
        seg[p] = COMB(seg[2 * p], seg[2 * p + 1]);
    }
}
int main() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        v.push_back(a[i]);
    }
    vector<tuple<char, int, int>> Q(q);
    for (int i = 0; i < q; i++) {
        char c;
        int x, y;
        cin >> c >> x >> y;
        Q[i] = {c, x, y};
        v.push_back(y);
        if (c == '?') v.push_back(x);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    auto I = [&](int x) {
        return upper_bound(v.begin(), v.end(), x) - v.begin();
    };
    for (int i = 1; i <= n; i++) upd(a[i] = I(a[i]), 1);
    for (int i = 0; i < q; i++) {
        auto [c, x, y] = Q[i];
        if (c == '!') {
            upd(a[x], -1);
            upd(a[x] = I(y), 1);
        } else cout << query(I(x), I(y)) << endl;
    }
}