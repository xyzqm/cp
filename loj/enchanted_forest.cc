#include <cassert>
#include <functional>
#include <algorithm>
#include <iostream>
#define int long long
using namespace std;

const int N = 2e5 + 1;
const int inf = 1e18;
struct Node;
typedef struct Node * T;
struct Node {
  int v, id, sz, U, V;
  T m = this;
  inline static int n = 0;
  static Node t[N];
  array<T, 2> c{};
  T p{};
  bool rev = false;
  Node() {}
  Node(int id, int v, int U, int V) : v(v), id(id), sz(1), U(U), V(V) {}
  static T init(int id, int v, int U = 0, int V = 0, T l = nullptr, T r = nullptr) {
    t[n] = Node(id, v, U, V);
    t[n].attach(0, l);
    t[n].attach(1, r);
    return &t[n++];
  }
  static int size(T x) { return x ? x->sz : 0; }
  static T mx(T x) { return x ? x->m : nullptr; }
  static T max(T a, T b) {
    if (!a) return b;
    if (!b) return a;
    return a->v > b->v ? a : b;
  }
  T push() {
    if (rev) {
      swap(c[0], c[1]);
      for (T x : c) if (x) x->rev ^= rev;
      rev = false;
    }
    return this;
  }
  void pull() {
    for (T x : c) if (x) x->push();
    sz = size(c[0]) + size(c[1]) + 1;
    m = max(mx(c[0]), max(this, mx(c[1])));
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
  int n = 0;
  T access(int u, bool lca = false) {
    for (T y = x[u], z = nullptr; y; z = y, y = y->p) {
      y->splay();
      if (lca && !y->p) return y;
      y->attach(1, z); // switch preferred path
    }
    x[u]->splay();
    return x[u];
  }
  int root(int u) { // get root of forest containing u
    T x = access(u);
    while ((x->push())->c[0]) x = x->c[0];
    return x->id;
  }
  T reroot(int u) {
    access(u)->rev ^= true;
    return x[u];
  }
  int node(int id, int v, int U = 0, int V = 0) {
    assert(!x[id]);
    x[id] = Node::init(id, v, U, V);
    n = max(n, id + 1);
    return id;
  }
  void link(int u, int v) { // add v as child of u
    access(u)->attach(1, reroot(v));
  }
  int cut(int u) { // cut edge from u to parent
    return access(u)->detach(0), u;
  }
  template <typename U>
  U query(int u, int v, function<U(T)> f) {
    int R = root(u);
    reroot(u);
    assert(root(v) == u);
    U x = f(access(v));
    reroot(R);
    return x;
  }
  void upd(int u, int v, function<void(T)> f) {
    int R = root(u);
    reroot(u);
    assert(root(v) == u);
    f(access(v));
    reroot(R);
  }
  int lca(int u, int v) {
    access(u);
    return access(v, true)->id;
  }
} lct;

void add_edge(int u, int v, int w) {
  int x = lct.node(lct.n, w, u, v);
  if (lct.root(u) == lct.root(v)) {
    // cut maximum edge
    T t = lct.query<T>(u, v, [&](T x) { return x->m; });
    if (t->v <= w) return;
    lct.reroot(t->id);
    lct.cut(t->U);
    lct.cut(t->V);
  }
  lct.link(x, u);
  lct.link(x, v);
}

struct E {
  int u, v, a, b;
  bool operator<(const E o) const { return a < o.a; }
} e[N];

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m; cin >> n >> m;
  for (int i = 1; i <= n; i++) lct.node(i, 0);
  for (int i = 0; i < m; i++) cin >> e[i].u >> e[i].v >> e[i].a >> e[i].b;
  sort(e, e + m);
  int r = inf;
  for (int i = 0; i < m; i++) {
    auto [u, v, a, b] =  e[i];
    add_edge(u, v, b);
    if (lct.root(1) == lct.root(n)) r = min(r, a + lct.query<int>(1, n, [&](T x) { return x->m->v; }));
  }
  cout << (r == inf ? -1 : r) << endl;
}
