#include <bits/stdc++.h>
using namespace std;
#define int int64_t

const int N = 2e5 + 1;
int sz[N], lc[N], rc[N], h[N], mx[N], v[N], cc = 0;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

void pull(int x) {
    if (!x) return;
    sz[x] = sz[lc[x]] + sz[rc[x]] + 1;
    mx[x] = max({mx[lc[x]], mx[rc[x]], v[x]});
}
void merge(int &t, int l, int r) {
    if (!l || !r) t = l ? l : r;
    else if (h[l] > h[r]) merge(rc[l], rc[l], r), t = l;
    else merge(lc[r], l, lc[r]), t = r;
    pull(t);
}
void split(int t, int& l, int& r, int x) {
    if (!t) return void(l = r = 0);
    if (x > sz[lc[t]]) split(rc[t], rc[t], r, x - sz[lc[t]] - 1), l = t;
    else split(lc[t], l, lc[t], x), r = t;
    pull(t);
}

int node(int x) {
    int y = ++cc;
    h[y] = rng();
    mx[y] = v[y] = x;
    sz[y] = 1;
    return y;
}

void push_front(int &t, int x) {
  merge(t, node(x), t);
}

void del(int t, int i) {
    int l, r; split(t, l, r, i);
    split(r, t, r, 1);
    merge(t, l, r);
}

void print(int t) {
    if (!t) return;
    print(lc[t]);
    cout << v[t] << " ";
    print(rc[t]);
}

// index of first value >= x
int find(int t, int x) {
    if (!t) return 0;
    if (v[t] == x) return sz[lc[t]];
    else if (v[t] < x) return find(rc[t], x) + sz[lc[t]] + 1;
    else return find(lc[t], x);
}

void inc(int t, int i, int x) {
    if (sz[lc[t]] == i) v[t] += x;
    else if (i < sz[lc[t]]) inc(lc[t], i, x);
    else inc(rc[t], i - sz[lc[t]] - 1, x);
    pull(t);
}

int get(int t, int i) {
    if (sz[lc[t]] == i) return v[t];
    else if (i < sz[lc[t]]) return get(lc[t], i);
    else return get(rc[t], i - sz[lc[t]] - 1);
}

int t = 0;

/* struct V { int a, b; */
/*     bool operator<(const V &o) const { return a + b == o.a + o.b ? a > o.a : a + b < o.a + o.b; } */
/* } e[N]; */

int32_t main() {
    // for (int i = 1; i <= 5; i++) push_front(t, -i);
    // print(t);
    // cout << find(t, -3) << endl;
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int j, x; cin >> j >> x;
        int l, r; split(t, l, r, j);
        merge(t, l, node(x));
        merge(t, t, r);
    }
    print(t);
    cout << endl;
}

