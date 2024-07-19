// https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum
#include <cassert>
#include <iostream>
#include <random>
#include <chrono>
#include <functional>
#define int long long
using namespace std;

struct mint;
using P = pair<mint, mint>;
struct mint {
  const static int M = 998244353;
  int v = 0;
  mint() {}
  mint(int v) { this->v = (v % M + M) % M; }
  mint operator+(const mint &o) const { return v + o.v; }
  mint& operator+=(const mint& o) { v = (v + o.v) % M; return *this; }
  mint operator*(const mint &o) const { return v * o.v; }
  mint operator-(const mint &o) const { return v - o.v; }
  mint& operator-=(const mint& o) { mint t = v - o.v; v = t.v; return *this; }
  mint operator^(int y) const { mint r = 1, x = v; for (y <<= 1; y >>= 1; x = x * x) if (y & 1) r = r * x; return r; }
  mint inv() const { assert(v); return *this ^ M - 2; }
  friend istream& operator>>(istream& s, mint& v) { s >> v.v; return s; }
  friend ostream& operator<<(ostream& s, const mint& v) { s << v.v; return s; }
  mint operator/(mint o) { return *this * o.inv(); }
};

struct F {
  mint w = 1, b = 0;
  mint operator()(mint x) { return w * x + b; }
  F operator()(F f) { return F{w * f.w, w * f.b + b}; }
  operator bool() const { return w.v != 1 || b.v != 0; }
};

typedef struct X * T;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
struct X {
  X(mint v) : v(v), s(v), p(rng()), sz(1) {}
  mint v, s;
  int p, sz;
  bool rev = false;
  T l = NULL, r = NULL;
  F f;
};

int sz(T x) { return x ? x->sz : 0; }
mint s(T x) { return x ? x->s : 0; }
void push(T x) {
  if (!x) return;
  if (x->rev) {
    x->rev = false;
    swap(x->l, x->r);
    if (x->l) x->l->rev ^= true;
    if (x->r) x->r->rev ^= true;
  }
  if (x->f) {
    x->v = x->f(x->v);
    x->s = x->f.w * x->s + x->f.b * x->sz;
    if (x->l) x->l->f = x->f(x->l->f);
    if (x->r) x->r->f = x->f(x->r->f);
    x->f = F{1, 0};
  }
}
bool needs_push(T x) { return x && x->f; }
void u(T x) {
  if (!x) return;
  push(x->l), push(x->r);
  assert(!x->f);
  x->sz = sz(x->l) + sz(x->r) + 1;
  x->s = s(x->l) + s(x->r) + x->v;
}
void merge(T& t, T l, T r) {
  push(l), push(r);
  if (!l || !r) t = l ? l : r;
  else if (l->p > r->p) merge(l->r, l->r, r), t = l;
  else merge(r->l, l, r->l), t = r;
  u(t);
}
void split(T t, T& l, T& r, int x, int sz = 0) {
  if (!t) return void(l = r = 0);
  push(t);
  int sz_ = sz + ::sz(t->l) + 1;
  if (x < sz_) split(t->l, l, t->l, x, sz), r = t;
  else split(t->r, t->r, r, x, sz_), l = t;
  u(t);
}
T t = NULL;
void insert(int i, int x) {
  T l, r; split(t, l, r, i);
  T v = new X(x);
  merge(l, l, v);
  merge(t, l, r);
}
void del(int i) {
  T l, r; split(t, l, r, i);
  split(r, t, r, 1);
  merge(t, l, r);
}

void upd(int l, int r, function<void(T)> f) { // updates range [l, r)
  T a, b, c;
  split(t, a, b, l);
  split(b, b, c, r - l);
  if (b) f(b);
  merge(t, a, b);
  merge(t, t, c);
}

template <typename R>
R query(int l, int r, function<R(T)> f) { // queries range [l, r)
  T a, b, c;
  split(t, a, b, l);
  split(b, b, c, r - l);
  assert(b); R x = f(b);
  merge(t, a, b);
  merge(t, t, c);
  return x;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q; cin >> n >> q;
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    insert(i, x);
  }
  /* upd(0, n, [](T x) { x->rev ^= true; }); */
  /* for (int i = 0; i < n - 1; i++) cout << query<mint>(i, i + 1, [](T x) { return x->s; }) << " "; */
  /* cout << endl; */
  /* return 0; */
  while (q--) {
    int t; cin >> t;
    int i, x, l, r, w, b;
    switch (t) {
      case 0:
        cin >> i >> x; insert(i, x);
        break;
      case 1:
        cin >> i; del(i);
        break;
      case 2:
        cin >> l >> r;
        upd(l, r, [](T x) { x->rev ^= true; });
        break;
      case 3:
        cin >> l >> r >> w >> b;
        upd(l, r, [=](T x) { x->f = F{w, b}(x->f); });
        break;
      case 4:
        cin >> l >> r;
        cout << query<mint>(l, r, [](T x) { return x->s; }) << endl;
        break;
    }

  }
}
