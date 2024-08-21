#include <cassert>
#include <functional>
#include <iostream>
#define int long long
using namespace std;

struct F {
  int w = 1, b = 0;
  int operator()(int x) const { return w * x + b; }
  F operator()(F f) const { return F{w * f.w, w * f.b + b}; }
  operator bool() const { return w != 1 || b != 0; }
};

const int N = 2e5 + 1;
const int inf = 1e18;
struct Node;
typedef struct Node * T;
struct Node {
  int v, s, m, M;
  int id, sz;
  inline static int n = 0;
  static Node t[N];
  array<T, 2> c{};
  T p{};
  F f{};
  bool rev = false;
  Node() {}
  Node(int id, int v) : v(v), s(v), m(v), M(v), id(id), sz(1), rev(false) {}
  static T init(int id, int v, T l = nullptr, T r = nullptr) {
    t[n] = Node(id, v);
    t[n].attach(0, l);
    t[n].attach(1, r);
    return &t[n++];
  }
  static int size(T x) { return x ? x->sz : 0; }
  static int sum(T x) { return x ? x->s : 0; }
  static int ID(T x) { return x ? x->id : -1; }
  static int mn(T x) { return x ? x->m : inf; }
  static int mx(T x) { return x ? x->M : -inf; }
  T push() {
    if (rev) {
      swap(c[0], c[1]);
      for (T x : c) if (x) x->rev ^= rev;
      rev = false;
    }
    if (f) {
      v = f(v);
      s = f.w * s + f.b * sz;
      for (T x : c) if (x) x->f = f(x->f);
      f = F{1, 0};
    }
    return this;
  }
  void pull() {
    for (T x : c) if (x) x->push();
    sz = size(c[0]) + size(c[1]) + 1;
    s = sum(c[0]) + sum(c[1]) + v;
    m = min({mn(c[0]), mn(c[1]), v});
    M = max({mx(c[0]), mx(c[1]), v});
  }
  bool side() { return p->c[1] == this; }
  bool is_root() { return !p || p->c[side()] != this; }
  void attach(int i, T x) {
    push();
    if (x) x->p = this;
    c[i] = x;
    pull();
  }
  T detach(int i) {
    push();
    T t = c[i];
    if (c[i]) c[i]->p = nullptr;
    c[i] = nullptr;
    return pull(), t;
  }
  void rotate() {
    T p = this->p, g = p->p;
    if (g) g->push();
    p->push(), push();
    int i = side();
    if (!p->is_root()) g->attach(p->side(), this);
    else this->p = g;
    p->attach(i, c[!i]);
    attach(!i, p);
  }
  T splay() {
    for (; !is_root(); rotate()) {
      if (!p->is_root()) {
        (side() == p->side()) ? p->rotate() : rotate();
      }
    }
    return this;
  }
  friend ostream& operator<<(ostream& os, T s) {
    if (!s) return os;
    os << s->c[0];
    os << s->id << " ";
    return os << s->c[1];
  }
};

Node Node::t[N]{};

struct LCT {
  T x[N]{}; // nodes
  /* int r = 0; */
  T access(int u, bool lca = false) {
    for (T y = x[u], z = nullptr; y; z = y, y = y->p) {
      y->splay();
      if (lca && !y->p) return y;
      y->attach(1, z); // switch preferred path
    }
    x[u]->splay();
    return x[u];
  }
  void print_chains() {
    /* cout << "chains: " << endl; */
    /* for (int i = 1; i <= 10; i++) if (x[i] && x[i]->is_root()) cout << x[i] << endl; */
    /* cout << "----" << endl; */
  }
  int root(int u) { // get root of forest containing u
    T x = access(u);
    while ((x->push())->c[0]) x = x->c[0];
    return x->id;
  }
  T reroot(int u) {
    access(u)->rev ^= true;
    return x[u]->push();
  }
  int node(int id, int v) {
    if (!x[id]) x[id] = Node::init(id, v);
    return id;
  }
  void link(int u, int v) { // add v as child of u
    access(u)->attach(1, reroot(v));
  }
  int cut(int u) { // cut edge from u to parent
    return access(u)->detach(0), u;
  }
  int query(int u, int v, function<int(T)> f) {
    /* int R = root(u); */
    reroot(u);
    assert(root(v) == u);
    int x = f(access(v));
    /* reroot(R); */
    return x;
  }
  void upd(int u, int v, function<void(T)> f) {
    /* int R = root(u); */
    reroot(u);
    assert(root(v) == u);
    f(access(v));
    /* reroot(R); */
  }
  int lca(int u, int v) {
    access(u);
    return access(v, true)->id;
  }
} lct;

int a[N];

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q; cin >> n >> q;
  for (int i = 1; i <= n; i++) { 
    cin >> a[i];
    lct.node(i, a[i]);
  }
  for (int i = 1; i <= n; i++) assert(lct.x[i]);
  for (int i = 1; i < n; i++) {
    int u, v; cin >> u >> v;
    lct.link(u, v);
  }
  int r; cin >> r;
  lct.reroot(r);
  while (q--) {
    int k; cin >> k;
    if (k == 0) { int x; cin >> x; lct.reroot(x); }
    else if (k < 3) {
      int x, y, z; cin >> x >> y >> z;
      cout << k << " " << x << " " << y << " " << z << endl;
      cout << "stuff: " << (k == 2) << endl;
      lct.upd(x, y, [=](T t) { t->f = F{k == 2, z}(t->f); });
    }
    else if (k < 6) {
      int x, y; cin >> x >> y;
      cout << k << " " << x << " "  << y << endl;
      cout << lct.query(x, y, [=](T t) { return k == 3 ? t->m : (k == 4 ? t->M : t->s); }) << endl;
    }
    else if (k == 6) {
      int x, y; cin >> x >> y;
      if (lct.lca(x, y) == x) continue;
      lct.link(y, lct.cut(x));
    }
    else {
      int x, y; cin >> x >> y;
      cout << lct.lca(x, y) << endl;
    }
  }
}

