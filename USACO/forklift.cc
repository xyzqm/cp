#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 1;
const int K = 20;

struct PST { int v; array<int, 2> c; } pst[K * N];
int cn = 0, n = 0;
bitset<K * N> vi;
vector<int> g[K * N];

int node(int v, array<int, 2> c = {0, 0}) {
    pst[++cn] = {v, c};
    for (int x : c) if (x) g[x].push_back(cn);
    return cn;
}

bool is_leaf(int x) { return !pst[x].c[0] && !pst[x].c[1]; }

int query(int p, int ql, int qr, int i, int l = 0, int r = 2 * n) {
    auto [v, c] = pst[p];
    if (!p || ql >= r || qr <= l) return 0;
    else if (ql <= l && r <= qr) {
        g[p].push_back(i);
        return v;
    }
    else {
        int m = (l + r) >> 1;
        return max(query(c[0], ql, qr, i, l, m), query(c[1], ql, qr, i, m, r));
    }
}

int upd(int p, int i, int x, int l = 0, int r = 2 * n) {
    auto [v, c] = pst[p];
    if (r - l == 1) return node(x, c);
    else {
        int m = (l + r) >> 1;
        if (i < m) c[0] = upd(c[0], i, x, l, m);
        else c[1] = upd(c[1], i, x, m, r);
        return node(max(pst[c[0]].v, pst[c[1]].v), c);
    }
}

int m, rt, id[N], prv[N], can[N];

vector<int> ord;
void dfs(int x) {
    vi[x] = 1;
    for (int y : g[x]) if (!vi[y]) dfs(y);
    if (is_leaf(x)) ord.push_back(pst[x].v);
}


void ac() {
    // clear PST
    for (int i = 1; i <= cn; i++) {
        pst[i] = {0, {0, 0}};
        g[i].clear();
    }
    rt = cn = 0;
    fill(id, id + n, 0);

    cin >> n;
    vector<tuple<int, int, int>> v;
    for (int i = 0; i < n; i++) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        v.push_back({--a, --b, i});
        v.push_back({--c, --d, i});
    }
    sort(v.begin(), v.end());
    for (auto [x, y, i] : v) {
        if (!id[i]) { // this is the southwest corner
            id[i] = cn + 1;
            rt = upd(rt, y, i);
            prv[i] = y;
        }
        else { // this is the northeast corner
            can[i] = (max(query(rt, 0, prv[i], id[i]), query(rt, prv[i] + 1, y, id[i])) <= i);
        }
    }
    ord.clear(), vi = 0;
    for (int i = 0; i < n; i++) if (!vi[id[i]]) dfs(id[i]);
    if (m == 1) for (auto it = ord.rbegin(); it != ord.rend(); it++) cout << *it + 1 << " ";
    else for (int i = 0; i < n; i++) cout << can[i];
    cout << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t >> m;
    while (t--) ac();
}
