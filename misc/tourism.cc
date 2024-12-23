// https://qoj.ac/contest/1210/problem/6340
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 1;
const int B = 400;

// util for log
constexpr int lg(int x) {
  return 31 - __builtin_clz(x);
}

// sparse table
const int K = 20;
int n, t = 0, tin[N], et[2 * N], c[N], d[N], st[2 * N][K]{};
int mind(int i, int j) { // min by depth
    return d[i] < d[j] ? i : j;
}
void build() {
	for (int i = 0; i < 2 * N; i++) st[i][0] = et[i];
	for (int k = 1; k < K; k++) for (int i = 0; i < 2 * N; i++) {
		st[i][k] = st[i][k - 1];
		if (int j = i + (1 << (k - 1)); j < 2 * N) st[i][k] = mind(st[i][k], st[j][k - 1]);
	}
}
int lca(int u, int v) { // lca of u and v
    u = tin[u], v = tin[v];
    if (u > v) swap(u, v);
    int k = lg(++v - u);
    return mind(st[u][k], st[v - (1 << k)][k]);
}

int dist(int u, int v) {
    return d[u] + d[v] - 2 * d[lca(u, v)];
}

// DFS
vector<int> g[N];
void dfs(int x, int p) {
    d[x] = d[p] + 1;
    et[tin[x] = t++] = x;
    for (int y : g[x]) if (y != p) {
        dfs(y, x);
        et[t++] = x;
    }
}

vector<int> o;
struct V { int x, c; }; // node + count
list<V> ll;
list<V>::iterator a[N]; // a[i] -> iterator pointing to node corresponding to city i
auto prv(list<V>::iterator it) {
    return --(it == ll.begin() ? ll.end() : it);
}
auto nxt(list<V>::iterator it) {
    it = next(it);
    return it == ll.end() ? ll.begin() : it;
}

struct T { int i, x; }; // insert city x before city i
vector<T> stk;

int tot = 0;

void build(int l, int r) {
    ll.clear();
    for (int x : o) {
        ll.push_back({x, 0});
        a[x] = --ll.end();
    }
    for (int i = l; i < r; i++) {
        ++a[c[i]]->c;
    }
    for (int i = 1; i <= n; i++) if (!a[i]->c) ll.erase(a[i]);
    tot = 0;
    for (auto it = ll.begin(); it != ll.end(); it++) {
        tot += dist(it->x, nxt(it)->x);
    }

}
int rem(int x) {
    auto l = prv(a[x]);
    auto r = nxt(a[x]);
    return dist(l->x, r->x) - dist(l->x, x) - dist(x, r->x);
}
void del(int x) {
    if (--(a[x]->c)) stk.push_back({0, x});
    else {
        stk.push_back({nxt(a[x])->x, x});
        tot += rem(x);
        ll.erase(a[x]);
    }
}
void undo() {
    // assert(stk.size());
    auto [i, x] = stk.back();
    stk.pop_back();
    if (!i) ++(a[x]->c);
    else {
        a[x] = ll.insert(a[i], {x, 1});
        tot -= rem(x);
    }
}

struct Q { int l, r, i;
    bool operator<(const Q &o) const { return l / B == o.l / B ? r > o.r : l / B > o.l / B; }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int m, q; cin >> n >> m >> q;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    build();
    o.resize(n);
    iota(o.begin(), o.end(), 1);
    sort(o.begin(), o.end(), [](int i, int j) { return tin[i] < tin[j]; });
    for (int i = 0; i < m; i++) cin >> c[i];
    build(0, m);
    vector<Q> qs(q);
    for (int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        qs[i] = {--l, r, i};
    }
    sort(qs.begin(), qs.end());
    int cl = 0, cr = m;
    vector<int> res(q);
    for (auto [l, r, i] : qs) {
        if (l / B != cl / B) build(cl = l / B * B, cr = r);
        while (cr > r) del(c[--cr]);
        while (cl < l) del(c[cl++]);
        res[i] = tot / 2 + 1;
        while (cl > l / B * B) undo(), cl--;
    }
    for (int i = 0; i < q; i++) cout << res[i] << endl;
}
