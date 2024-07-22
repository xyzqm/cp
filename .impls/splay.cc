#include <cassert>
#include <functional>
#include <iostream>
#include <vector>
#define int long long
using namespace std;

struct mint;
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
  mint sym() { return *this ^ (M - 1) / 2; } // legendre symbol: 1 -> qresidue, -1 -> non-residue
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

typedef struct Node * T;
struct Node {
  mint v, s;
  int sz;
  T l, r;
  F f;
  bool rev;
  static inline vector<T> st = {};
  Node(int v, T l = nullptr, T r = nullptr) : v(v), s(v), sz(0), l(l), r(r), rev(false) { pull(); }
  static int size(T x) { return x ? x->sz : 0; }
  static mint sum(T x) { return x ? x->s : 0; } 
  void push() {
    if (rev) {
      rev = false;
      swap(l, r);
      if (l) l->rev ^= true;
      if (r) r->rev ^= true;
    }
    if (f) {
      v = f(v);
      s = f.w * s + f.b * sz;
      if (l) l->f = f(l->f);
      if (r) r->f = f(r->f);
      f = F{1, 0};
    }
  }
  void pull() {
    assert(!f);
    if (l) l->push();
    if (r) r->push();
    sz = size(l) + size(r) + 1;
    s = sum(l) + sum(r) + v;
  }
  void rotate(T p, T g) {
    int o = p->sz;
    p->push(), push();
    assert(this == p->l || this == p->r);
    if (this == p->l) p->l = r, r = p;
    else p->r = l, l = p;
    if (g) {
      if (p == g->l) g->l = this;
      else g->r = this;
    }
    /* assert(!g || g->l == this || g->r == this); */
    p->pull(), pull();
    assert(sz == o);
  }
  T top() {
    if (!st.size()) return nullptr;
    T x = st.back(); st.pop_back();
    return x;
  }
  bool step() {
    T x = top(), p = top(), g = top(), a = top();
    if (!p) return false;
    assert(x == this && p);
    /* cout << x << endl << p << endl; */
    /* assert(this == p->l || this == p->r); */
    if (!g) rotate(p, g);
    else if ((this == p->l) == (p == g->l)) p->rotate(g, a), rotate(p, a);
    else rotate(p, g), rotate(g, a);
    if (a) st.push_back(a);
    st.push_back(x);
    assert(!a || a->l == x || a->r == x);
    return true;
  }
  T splay(int x) { // splays and returns new root
    /* cout << this << endl; */
    st.push_back(this);
    push();
    assert(x < sz);
    if (x < size(l)) return l->splay(x);
    else if (x > size(l)) return r->splay(x - size(l) - 1);
    else { // we found the element
      while (step());
      /* cout << l->sz << " " << x << endl; */
      /* assert(l->sz == x && p == ghost); */
      return this;
    }
  }
  friend ostream& operator<<(ostream& os, T s) {
    if (!s) return os;
    os << s->l;
    os << s->v << " ";
    return os << s->r;
  }
};

struct Splay {
  T root = nullptr;
  void splay(int x) { assert(!Node::st.size()); root = root->splay(x); }
  auto split(int i) { // {[0, i), [i, )}
    if (i == (root ? root->sz : 0)) return make_pair(Splay{root}, Splay{nullptr});
    /* cout << root->sz << "y" << endl; */
    /* cout << "splitting" << endl; */
    splay(i);
    assert(root != nullptr);
    T l = root->l;
    root->l = nullptr;
    /* cout << root->sz << "x" << endl; */
    /* cout << "post-split" << endl; */
    root->pull();
    return make_pair(Splay{l}, Splay{root});
  }
  Splay join(Splay o) {
    if (!root) return root = o.root, *this;
    splay(root->sz - 1);
    root->r = o.root;
    /* cout << "post-join" << endl; */
    root->pull();
    return *this;
  }
  void insert(int i, int x) {
    auto [l, r] = split(i);
    root = new Node(x, l.root, r.root);
  }
  void del(int i) {
    splay(i);
    root = Splay{root->l}.join(Splay{root->r}).root;
  }
  mint query(int l, int r) { // query range [l, r)
    Splay a, b, c;
    tie(a, b) = split(l);
    tie(b, c) = b.split(r - l);
    mint R = b.root->s;
    root = a.join(b).join(c).root;
    return R;
  }
  void upd(int l, int r, function<void(T)> f) {
    Splay a, b, c;
    tie(a, b) = split(l);
    tie(b, c) = b.split(r - l);
    f(b.root);
    root = a.join(b).join(c).root;
  }
  friend ostream& operator<<(ostream& os, Splay s) { return os << s.root; }
} splay;

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q; cin >> n >> q;
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    splay.insert(i, x);
    /* cout << splay << endl; */
  }
  /* splay.insert(2, 1); */
  /* cout << splay << endl; */
  /* splay.insert(0, 10); */
  /* cout << splay << endl; */
  /* splay.del(2); */
  /* cout << splay << endl; */
  while (q--) {
    int t; cin >> t;
    int i, x, l, r, w, b;
    /* cout << splay << endl; */
    switch (t) {
      case 0:
        cin >> i >> x; splay.insert(i, x);
        break;
      case 1:
        cin >> i; splay.del(i);
        break;
      case 2:
        cin >> l >> r;
        splay.upd(l, r, [](T x) { x->rev ^= true; });
        break;
      case 3:
        cin >> l >> r >> w >> b;
        splay.upd(l, r, [=](T x) { x->f = F{w, b}(x->f); });
        break;
      case 4:
        cin >> l >> r;
        cout << splay.query(l, r) << endl;
        break;
    }

  }
}
