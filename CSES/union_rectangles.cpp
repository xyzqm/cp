// https://cses.fi/problemset/task/1741
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int OFFSET = 1e6;
const int R = 2 * OFFSET; // range of coordinates
const int inf = INT_MAX;
struct Edge {
    int y1, y2;
    bool enter; // enter/exit
};
vector<Edge> edges[R + 1];
pii st[4 * R]; // min + number of occurences of min
int lazy[4 * R];
void push(int p, int l, int r) {
    if (lazy[p]) {
        if (l != r) {
            lazy[2 * p] += lazy[p];
            lazy[2 * p + 1] += lazy[p];
        }
        st[p].first += lazy[p];
        lazy[p] = 0;
    }
}
int query() {
    if (st[1].first != 0) return R;
    else return R - st[1].second;
}
void _update(int p, int l, int r, int ql, int qr, int x) {
    push(p, l, r);
    if (r < ql || l > qr) return;
    if (ql <= l && r <= qr) {
        lazy[p] += x;
        push(p, l, r);
    }
    else {
        int m = (l + r) / 2;
        _update(2 * p, l, m, ql, qr, x);
        _update(2 * p + 1, m + 1, r, ql, qr, x);
        if (st[2 * p].first == st[2 * p + 1].first) 
            st[p] = {st[2 * p].first, st[2 * p].second + st[2 * p + 1].second};
        else if (st[2 * p].first < st[2 * p + 1].first) st[p] = st[2 * p];
        else st[p] = st[2 * p + 1];
    }
}
void update(int l, int r, int x) {
    _update(1, 0, R - 1, l + OFFSET, r + OFFSET - 1, x);
}
void _build(int p, int l, int r) {
    st[p] = {0, r - l + 1};
    if (l != r) {
        int m = (l + r) / 2;
        _build(2 * p, l, m);
        _build(2 * p + 1, m + 1, r);
    }
}
void build() {
    _build(1, 0, R - 1);
}

int main() {
    build();
    int n, x1, y1, x2, y2; cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x1 >> y1 >> x2 >> y2;
        edges[x1 + OFFSET].push_back(Edge{y1, y2, true});
        edges[x2 + OFFSET].push_back(Edge{y1, y2, false});
    }
    ll ans = 0;
    for (int i = 0; i <= R; i++) {
        for (Edge e : edges[i]) {
            if (e.enter) update(e.y1, e.y2, 1);
            else update(e.y1, e.y2, -1);
        }
        ans += query();
    }
    cout << ans;
}