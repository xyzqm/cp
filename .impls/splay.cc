#include <cassert>
#include <functional>
#include <iostream>
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
  mint v, sum;
  int sz;
  T l, r, p;
  F f;
  bool rev;
  static T ghost;
  Node(int v, T l = ghost, T r = ghost) : v(v), sum(v), sz(0), l(l), r(r), p(ghost), rev(false) {
    if (l) l->p = this;
    if (r) r->p = this;
    /* cout << "constructor" << endl; */
    if (l && r) pull();
  }
  bool left() { assert(p); return this == p->l; }
  void push() {
    if (this == ghost) return;
    if (rev) {
      rev = false;
      swap(l, r);
      l->rev ^= true;
      r->rev ^= true;
    }
    if (f) {
      v = f(v);
      sum = f.w * sum + f.b * sz;
      l->f = f(l->f);
      r->f = f(r->f);
      f = F{1, 0};
    }
  }
  void pull() {
    if (this == ghost) return;
    assert(!f);
    assert(!l || l == ghost || l->p == this);
    assert(!r || r == ghost || r->p == this);
    l->push(), r->push();
    sz = l->sz + r->sz + 1;
    sum = l->sum + r->sum + v;
  }
  void rotate() {
    assert(this != ghost && p != ghost);
    /* cout << this << " " << sz << endl; */
    /* cout << p << endl; */
    if (p != ghost) {
      if (left()) assert(p->l == this);
      else assert(p->r == this);
    }
    int o = p->sz;
    p->push(), push();
    if (left()) {
      /* cout << "left" << endl; */
      p->l = r, p->l->p = p, p->pull(), r = p;
      p = p->p;
      if (p != ghost) {
        if (r->left()) p->l = this;
        else p->r = this;
      }
      r->p = this;

    } else {
      /* cout << "right" << endl; */
      p->r = l, p->r->p = p, p->pull(), l = p;
      p = p->p;
      if (p != ghost) {
        if (l->left()) p->l = this;
        else p->r = this;
      }
      l->p = this;
    }
    pull();
    assert(sz == o);
  }
  bool step() {
    p->p->push();
    p->push();
    if (p == ghost) return false;
    if (p->p == ghost) rotate();
    else if (left() == p->left()) p->rotate(), rotate();
    else rotate(), rotate();
    return true;
  }
  T splay(int x) { // splays and returns new root
    /* cout << this << endl; */
    if (this == ghost) return this;
    /* cout << x << " " << sz << endl; */
    push();
    assert(x < sz);
    if (x < l->sz) return l->splay(x);
    else if (x > l->sz) return r->splay(x - l->sz - 1);
    else { // we found the element
      while (step());
      /* cout << l->sz << " " << x << endl; */
      /* assert(l->sz == x && p == ghost); */
      return this;
    }
  }
  friend ostream& operator<<(ostream& os, T s) {
    if (s == ghost) return os;
    os << s->l;
    os << s->v << " ";
    return os << s->r;
  }
};

T Node::ghost = new Node(0);

struct Splay {
  T root = Node::ghost;
  void splay(int x) { root = root->splay(x); }
  auto split(int i) { // {[0, i), [i, )}
    if (i == root->sz) return make_pair(Splay{root}, Splay{Node::ghost});
    /* cout << root->sz << "y" << endl; */
    /* cout << "splitting" << endl; */
    splay(i);
    assert(root != nullptr);
    assert(root->l != nullptr);
    T l = root->l;
    /* cout << root->sz << "x" << endl; */
    l->p = Node::ghost, root->l = Node::ghost;
    /* cout << "post-split" << endl; */
    root->pull();
    return make_pair(Splay{l}, Splay{root});
  }
  Splay join(Splay o) {
    if (root == Node::ghost) return root = o.root, *this;
    splay(root->sz - 1);
    root->r = o.root, o.root->p = root;
    /* cout << "post-join" << endl; */
    root->pull();
    return *this;
  }
  void insert(int i, int x) {
    auto [l, r] = split(i);
    root = new Node(x, l.root, r.root);
  }
  void del(int i) {
    /* cout << "Deleting" << endl; */
    splay(i);
    root->l->p = root->r->p = Node::ghost;
    /* cout << root->l->sz << " " << root->r->sz << endl; */
    root = Splay{root->l}.join(Splay{root->r}).root;
  }
  mint query(int l, int r) { // query range [l, r)
    Splay a, b, c;
    /* cout << root->sz << endl; */
    tie(a, b) = split(l);
    /* cout << a.root->sz << "q" << b.root->sz << endl; */
    tie(b, c) = b.split(r - l);
    mint R = b.root->sum;
    root = a.join(b).join(c).root;
    return R;
  }
  void upd(int l, int r, function<void(T)> f) {
    Splay a, b, c;
    /* cout << root->sz << endl; */
    tie(a, b) = split(l);
    /* cout << a.root->sz << "q" << b.root->sz << endl; */
    tie(b, c) = b.split(r - l);
    f(b.root);
    root = a.join(b).join(c).root;
  }
  friend ostream& operator<<(ostream& os, Splay s) { return os << s.root; }
} splay;

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  Node::ghost->l = Node::ghost->r = Node::ghost->p = Node::ghost;
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
