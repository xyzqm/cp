#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define all(x) x.begin(), x.end()

struct dat {
    int cnt = 0; // parity of # of values
    array<int, 2> sm = {0, 0}; // sm[i] = sum of vals whose parity = i + parity[last elt]
};
dat operator+(dat l, dat r) {
    dat rt;
    rt.cnt = r.cnt ^ l.cnt;
    for (int t : {0, 1}) rt.sm[t] = r.sm[t] + l.sm[t ^ r.cnt];
    return rt;
}

struct node { dat d{}; array<int, 2> c = {0, 0}; };
struct sgt : vector<node> {
    int n; // max value
    sgt(int n) : vector(1), n(n) { }
    int node(dat d, array<int, 2> c) { return push_back({d, c}), size() - 1; }
    int create(int i) {
        dat d = {1, {i, 0}};
        auto cr = [&](auto &&cr, int l, int r) {
            array<int, 2> c = {0, 0};
            if (r - l == 1) return node(d, c);
            int m = (l + r) >> 1;
            if (i < m) c[0] = cr(cr, l, m);
            else c[1] = cr(cr, m, r);
            return node(d, c);
        };
        return cr(cr, 0, n);
    }
    int merge(int x, int y) {
        if (!x || !y) return x + y;
        else if (at(x).c == array<int, 2>{0, 0} && at(y).c == array<int, 2>{0, 0}) at(x).d = at(x).d + at(y).d; // merge two leaves
        else {
            for (int t : {0, 1}) at(x).c[t] = mg(mg, at(x).c[t], at(y).c[t]);
            at(x).d = at(at(x).c[0]).d + at(at(x).c[1]).d;
        }
        return x;
    }
};

struct cp {
    vector<pair<int, int>> sol = {{-1, 0}};
    int v = -1, w = 0; // v < 0 means size, v >= 0 means parent, w is edge to parent
};

const int MX = 2e9;

sgt t(MX);
vector<int> rt; // sgt roots
struct dsu : vector<cp> {
    dsu(int n) : vector(n) {}
    int rep(int x, int w) { return (at(x).v < 0 || at(x).w >= w) ? x : rep(at(x).v, w); }
    bool join(int x, int y, int w) {
        x = rep(x, MX), y = rep(y, MX);
        if (x == y) return false;
        if (at(x).v > at(y).v) ::swap(x, y);
        at(x).v += at(y).v;
        at(y).v = x, at(y).w = w;
        assert(t.merge(rt[x], rt[y]) == rt[x]);
        at(x).sol.push_back({w, t[rt[x]].d.sm[0]});
        return true;
    }
};


int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, q, typ; cin >> n >> m >> q >> typ;
    vector<int> p(++n);
    for (int i = 1; i < n; i++) cin >> p[i];
    vector<int> sm(n);
    vector<array<int, 3>> es;
    int tot = 0;
    while (m--) {
        int u, v, w; cin >> u >> v >> w;
        es.push_back({max(p[u], p[v]), u, v});
        sm[u] += w, sm[v] += w, tot += w;
    }

    for (int x : sm) rt.push_back(t.create(x));
    sort(all(es));
    dsu uf(n);
    for (int i = 1; i < n; i++) uf[i].sol.push_back({p[i], sm[i]});
    for (auto [w, u, v] : es) uf.join(u, v, w);
    for (int prv = 0; q --> 0; prv = abs(prv)) {
        int x, k; cin >> x >> k;
        if (typ) x ^= prv, k ^= prv;
        int rep = uf.rep(x, k);
        cout << (prv = (--lower_bound(all(uf[rep].sol), pair<int, int>{k, -1}))->second - tot) << endl;
    }
}
