#include <cassert>
#include <iostream>
#include <memory>
#include <random>
#define int long long
using namespace std;

typedef struct X * T;
mt19937 rng(42);
const int N = 2e5 + 1;
const int K = 6e6 + 1;
struct X {
  X() {}
  X(int v) : v(v), s(v), sz(1) {}
  int v, s, sz;
  T l = nullptr, r = nullptr;
} a[K], t[K];

int xn = 0, sn = 0;
template <typename R>
T node(R x, bool te = false) { int& n = (te ? sn : xn); assert(n < K); return &((te ? t : a)[n++] = X(x)); }
/* T node(R x) { return new X(x); } */

int sz(T x) { return x ? x->sz : 0; }
int s(T x) { return x ? x->s : 0; }

void u(T x) {
  if (!x) return;
  x->sz = sz(x->l) + sz(x->r) + 1;
  x->s = s(x->l) + s(x->r) + x->v;
}
ostream& operator<<(ostream& os, T x) {
  if (!x) return os;
  os << x->l;
  os << x->v << " ";
  return os << x->r;
}
T merge(T l, T r, bool cpy = true) {
  T t;
  if (!l && !r) t = nullptr;
  else if (!!l + !!r == 1) t = cpy ? node(l ? *l : *r) : (l ? l : r);
  else if (rng() % (sz(l) + sz(r)) < sz(l)) t = cpy ? node(*l) : l, t->r = merge(l->r, r, cpy);
  else t = cpy ? node(*r) : r, t->l = merge(l, r->l, cpy);
  u(t);
  return t;
}
pair<T, T> split(T t, int x, bool cpy = true) {
  if (!t) return {nullptr, nullptr};
  T l = nullptr, r = nullptr;
  if (x > sz(t->l)) l = cpy ? node(*t) : t, tie(l->r, r) = split(t->r, x - sz(t->l) - 1, cpy), u(l);
  else r = cpy ? node(*t) : t, tie(l, r->l) = split(t->l, x, cpy), u(r);
  return {l, r};
}
void insert(T &t, int i, int x) {
  auto [l, r] = split(t, i, false);
  T v = node(x);
  t = merge(merge(l, v, false), r, false);
}
void del(T &t, int i) {
  auto [l, r] = split(t, i);
  tie(t, r) = split(r, 1);
  t = merge(l, r);
}

int n, m;
T O, R;
int query(int l, int r) { // queries range [l, r)
  T a, b, c;
  tie(a, b) = split(R, l);
  tie(b, c) = split(b, r - l);
  /* assert(sz(R) == n); */
  return b->s;
}
void shift(int l, int r, int k) {
  T t = split(split(R, l - k).second, k).first;
  T x = split(t, (r - l) % k).first;
  for ( ; sz(t) <= (r - l); t = merge(t, t)) if (sz(t) / k & (r - l) / k) x = merge(t, x);
  T a, b, c;
  tie(a, b) = split(R, l);
  tie(b, c) = split(b, r - l);
  R = merge(merge(a, x), c);
}
void revert(int l, int r) {
  T B, a, b, c;
  B = split(split(O, l).second, r - l).first;
  tie(a, b) = split(R, l);
  tie(b, c) = split(b, r - l);
  R = merge(merge(a, B), c);
}

T rebuild(X t) {
  T c = node(t, true);
  c->l = t.l ? rebuild(*t.l) : nullptr;
  c->r = t.r ? rebuild(*t.r) : nullptr;
  return c;
}

T copy(T t) {
  if (!t) return nullptr;
  T c = node(*t);
  c->l = copy(t->l);
  c->r = copy(t->r);
  return c;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    insert(O, i, x);
  }
  int sn = xn;
  // cout << sn << endl;
  R = node(*O);
  while (m--) {
    int t, l, r; cin >> t >> l >> r; --l;
    if (t == 1) cout << query(l, r) << endl;
    else if (t == 2) {
      int k; cin >> k;
      shift(l, r, k);
    }
    else revert(l, r);
    if (xn > 5e6) {
      xn = sn, ::sn = 0;
      R = copy(rebuild(*R));
    }
  }
}
