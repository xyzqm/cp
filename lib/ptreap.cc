// https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum
#include <cassert>
#include <iostream>
#include <random>
#include <functional>
#define int long long
using namespace std;

typedef struct X * T;
mt19937 rng(42);
const int N = 2e5 + 1;
struct X {
  X() {}
  X(int v) : v(v), s(v), p(rng()), sz(1) {}
  int v, s;
  int p, sz;
  bool rev = false;
  T l = nullptr, r = nullptr;
  inline static int n = 0;
} t[N * 60]{};

template <typename T>
X* node(T x) { return &(t[X::n++] = X(x)); }

int sz(T x) { return x ? x->sz : 0; }
int s(T x) { return x ? x->s : 0; }
void push(T x) {
  if (!x || !x->rev) return;
  if (x->l) x->l = node(*x->l);
  if (x->r) x->r = node(*x->r);
  if (x->rev) {
    x->rev = false;
    swap(x->l, x->r);
    if (x->l) x->l->rev ^= true;
    if (x->r) x->r->rev ^= true;
  }
}
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
T merge(T l, T r) {
  push(l), push(r);
  T t;
  if (!l || !r) t = l ? l : r;
  else if (l->p > r->p) t = l, t->r = merge(l->r, r);
  else t = r, t->l = merge(l, r->l);
  u(t);
  return t;
}
pair<T, T> split(T t, int x) {
  if (!t) return {nullptr, nullptr};
  push(t);
  T l = nullptr, r = nullptr;
  if (x > sz(t->l)) l = node(*t), tie(l->r, r) = split(t->r, x - sz(t->l) - 1), u(l);
  else r = node(*t), tie(l, r->l) = split(t->l, x), u(r);
  return {l, r};
}
T insert(T t, int i, int x) {
  auto [l, r] = split(t, i);
  T v = node(x);
  return merge(merge(l, v), r);
}
T del(T t, int i) {
  auto [l, r] = split(t, i);
  tie(t, r) = split(r, 1);
  return merge(l, r);
}

T upd(T t, int l, int r, function<void(T)> f) { // updates range [l, r)
  T a, b, c;
  tie(a, b) = split(t, l);
  tie(b, c) = split(b, r - l);
  if (b) f(b);
  return merge(merge(a, b), c);
}

template <typename R>
R query(T t, int l, int r, function<R(T)> f) { // queries range [l, r)
  T a, b, c;
  tie(a, b) = split(t, l);
  tie(b, c) = split(b, r - l);
  return f(b);
}

T h[N]{};

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  int q; cin >> q;
  int prev = 0;
  for (int v = 1; v <= q; v++) {
    int opt, p, i, x, l, r;
    cin >> p >> opt;
    switch (opt) {
      case 1:
        cin >> i >> x; i ^= prev, x ^= prev; h[v] = insert(h[p], i, x);
        break;
      case 2:
        cin >> i; i ^= prev; i--; h[v] = del(h[p], i);
        break;
      case 3:
        cin >> l >> r; l ^= prev, r ^= prev;
        assert(l <= r);
        h[v] = upd(h[p], l - 1, r, [](T x) { x->rev ^= true; });
        break;
      case 4:
        cin >> l >> r; l ^= prev, r ^= prev;
        assert(l <= r);
        cout << (prev = query<int>(h[p], l - 1, r, [](T x) { return x->s; })) << endl;
        h[v] = h[p];
        break;
    }
  }
}

