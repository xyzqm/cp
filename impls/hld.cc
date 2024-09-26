#include "graph.cc"
template <typename T, typename E>
struct HLD {
  Tree<E>& t;
  SGT<T> sgt;
  int I[N], U[N], i = 0;
  function<T(T, T)> f; T t0;
  HLD(Tree<E> &t, T x) : t(t) { t0 = x; }
  HLD& fn(function<T(T, T)> f) { return sgt.fn(this->f = f, t0), *this; }
  HLD& hld() {
    t.dfs();
    dfs_hld(t.r);
    return *this;
  }
  void dfs_hld(int x) {
    I[x] = i++;
    auto e = t.ex(x);
    for (int &y : e) if (t.s[y] > t.s[e[0]]) swap(e[0], y);
    for (int y : e) if (y != t.p[x]) {
      U[y] = (y == e[0]? U[x] : y);
      dfs_hld(y);
    }
  }
  HLD &upd(int u, T x) { assert(u <= t.n); return sgt.upd(I[u], x), *this; }
  T query(int u, int v) {
    assert(u <= t.n && v <= t.n);
    T x = t0;
    for (; U[u] != U[v]; u = t.p[U[u]]) {
      if (t.d[U[u]] < t.d[U[v]]) swap(u, v);
      x = f(x, sgt.query(I[U[u]], I[u] + 1));
    }
    if (t.d[u] > t.d[v]) swap(u, v);
    return f(x, sgt.query(I[u], I[v] + 1));
  }
};

/* int main() { */
/*   cin.tie(0)->sync_with_stdio(0); */
/*   int n, q; cin >> n >> q; */
/*   for (int i = 0; i < n; i++) cin >> a[i]; */
/*   Tree<int> t(n); */
/*   t.input(); */
/*   auto h = HLD(t.root(0), 0LL); */
/*   h.fn([](ll x, ll y) { return x + y; }).hld(); */
/*   for (int i = 0; i < n; i++) h.upd(i, a[i]); */
/*   while (q--) { */
/*     int t, x, y; cin >> t >> x >> y; */
/*     if (!t) h.upd(x, y); */
/*     else cout << h.query(x, y) << endl; */
/*   } */
/* } */

