#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#define int long long
using namespace std;

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
  friend istream& operator>>(istream& s, mint& v) { s >> v.v; return s; }
  friend ostream& operator<<(ostream& s, const mint& v) { s << v.v; return s; }
};

struct F {
  mint w = 1, b = 0;
  mint operator()(mint x) { return w * x + b; }
  F operator()(F f) { return F{w * f.w, w * f.b + b}; }
  operator bool() const { return w.v != 1 || b.v != 0; }
};

const int N = 5e5 + 1;
struct Node;
typedef struct Node * T;
struct Node {
  mint v, s;
  int sz = 1;
  int d = 0;
  inline static int n = 0;
  static Node t[2 * N];
  array<T, 2> c{};
  inline static vector<T> path;
  T p{};
  F f{};
  bool rev = false;
  Node() {}
  Node(int v) : v(v), s(v) {}
  static T init(int v, T l = nullptr, T r = nullptr) {
    t[n] = Node(v);
    t[n].attach(0, l);
    t[n].attach(1, r);
    t[n].pull();
    return &t[n++];
  }
  static int size(T x) { return x ? x->sz : 0; }
  static mint sum(T x) { return x ? x->s : 0; }
  int ind() { return this - t; }
  void push() {
    for (T x : c) if (x) x->d = d + 1;
    if (rev) {
      swap(c[0], c[1]);
      for (int i = 0; i < 2; i++) if (c[i]) c[i]->rev ^= rev;
      rev = false;
    }
    if (f) {
      v = f(v);
      s = f.w * s + f.b * sz;
      for (int i = 0; i < 2; i++) if (c[i]) c[i]->f = f(c[i]->f);
      f = F{1, 0};
    }
  }
  void rebuild_depths() {
    push();
    for (T x : c) if (x) x->rebuild_depths();
  }
  void pull() {
    assert(!f);
    for (int i = 0; i < 2; i++) if (c[i]) c[i]->push();
    sz = size(c[0]) + size(c[1]) + 1;
    s = sum(c[0]) + sum(c[1]) + v;
  }
  bool side() { return p->c[1] == this; }
  void attach(int i, T x) {
    if (x) x->p = this;
    if (x) assert(x->p == this);
    c[i] = x;
    push();
    pull();
  }
  T detach(int i) {
    push();
    T t = c[i];
    if (c[i]) c[i]->p = nullptr;
    c[i] = nullptr;
    pull(); return t;
  }
  void rotate() {
    T p = this->p, g = p->p;
    p->push(), push();
    int i = side();
    if (g) g->attach(p->side(), this);
    else this->p = nullptr, d = 0;
    assert(this == p->c[i]);
    p->attach(i, c[!i]);
    attach(!i, p);
  }
  void splay() {
    for (;p;rotate()) {
      if (p->p) {
        (side() == p->side()) ? p->rotate() : rotate();
      }
    }
  }
  T find(int i) {
    path.push_back(this);
    if (c[0]) assert(c[0]->p == this);
    if (c[1]) assert(c[1]->p == this);
    assert(i <= sz);
    push();
    if (i < size(c[0])) return c[0]->find(i);
    else if (i > size(c[0])) return c[1]->find(i - size(c[0]) - 1);
    else return this;
  }
  friend ostream& operator<<(ostream& os, T s) {
    if (!s) return os;
    os << s->c[0];
    os << s->v << " ";
    return os << s->c[1];
  }
};

Node Node::t[2 * N];

struct Splay {
  T root = nullptr;
  T splay(int x) {
    Node::path.clear();
    root->d = 1;
    root->rebuild_depths();
    T t = root->find(x);
    vector<int> v;
    vector<T> all_nodes;
    function<void(T)> dfs = [&](T x) {
      if (!x) return;
      all_nodes.push_back(x);
      dfs(x->c[0]);
      dfs(x->c[1]);
    };
    // dfs(root);
    // for (T u : all_nodes) v.push_back(u->d);
    for (T u : Node::path) v.push_back(u->d);
    t->splay();
    // assert(t->d == 0);
    int i = 0;
    double tot = 0, tot_lg = 0;
    double cost = Node::path.size();
    t->d = 1;
    t->rebuild_depths();
    /* cout << "ratios: "; */ for (T u : Node::path) {
      if (v[i] == 0) { i++; continue; }
      double t = (double)(u->d)/(v[i++]);
      tot += t;
      if (t > 0) { cost += log2(t), tot_lg += log2(t); }
      // cout << t << " ";
    }
    // cout << endl;
    cout << "avg: " << tot / (Node::path.size() - 1) << endl;
    cout << "avg log: " << tot_lg / (Node::path.size() - 1) << endl;
    cout << "cost: " << cost << endl;
    assert(Node::size(t->c[0]) == x);
    return root = t;
  }
  pair<Splay, Splay> split(int i) { // splits into {[0, i), [i, )}
    if (i == (root ? root->sz : 0)) return make_pair(Splay{root}, Splay{nullptr});
    T t = splay(i)->detach(0);
    assert(root->c[0] == nullptr);
    return make_pair(Splay{t}, Splay{root});
  }
  Splay join(Splay o) {
    if (!root) return root = o.root, *this;
    splay(root->sz - 1);
    assert(root->c[1] == nullptr);
    root->attach(1, o.root);
    return *this;
  }
  void insert(int i, int x) {
    auto [l, r] = split(i);
    root = Node::init(x, l.root, r.root);
  }
  void del(int i) {
    assert(i < root->sz);
    splay(i);
    root = Splay{root->detach(0)}.join(Splay{root->detach(1)}).root;
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
  }
  while (q--) {
    int t; cin >> t;
    int i, x, l, r, w, b;
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
