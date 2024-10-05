#define SOURCE
#ifndef COMPILED
const int N = 1e3 + 1;
#else
const int N = 4e5 + 1;
#endif
#include "hld.h"
#include "linear.h"
using L = Line<int>;
using P = pair<int, int>;

string s;
int i = 0, fi = 0;


const string ops = "[(!&^|";
struct Function {
  int k = 4, l = 0, r = 0;
  bool v = 0;
  L transform();
} a[N];

ostream& operator<<(ostream &os, Function f) { // prints function in prefix
  os << ops[f.k];
  if (!f.k) os << f.l << "]";
  if (f.k > 0 && f.l >= 0) os << a[f.l];
  if (f.k > 0 && f.r >= 0) os << a[f.r];
  return os;
}

L Function::transform() {
  if (k == 0) return L{0, v};
  else if (k == 1) assert(false); // we don't care about parentheses
  else if (k == 2) return L{-1, 1}; // !
  else if (k == 3) return a[l].v ? L{1, 0} : L{0, 0}; // &
  else if (k == 4) return a[l].v ? L{-1, 1} : L{1, 0}; // ^
  else return a[l].v ? L{0, 1} : L{1, 0}; // |
}

Tree t(N);

vector<int> leaves;
int nf(int k, int l, int r, bool v) {
  a[fi] = {k, l, r, v};
  if (k) {
    if (l >= 0) t.undirected(fi, l);
    if (r >= 0) t.undirected(fi, r);
  }
  else leaves.push_back(fi);
  return fi++;
}

// parses expression level k and puts pointer after expression
int parse(int k) {
  assert(i < s.size());
  if (s[i] == '\0') return -1;
  assert(k >= 0);
  if (k < 3) {
    if (s[i] != ops[k]) return parse(k - 1);
    else i++;
    if (k == 0) {
      int r = 0;
      while (s[i] != ']') r = r * 10 + (s[i++] - '0');
      return i++, nf(k, r, -1, 0);
    }
    if (k == 1) {
      int j = parse(5);
      assert(s[i] == ')');
      return i++, j;
    }
    else {
      int j = parse(2);
      return nf(k, j, -1, !a[j].v);
    }
  }
  else {
    int a = parse(k - 1);
    while (s[i] == ops[k]) {
      i++;
      int b = parse(k - 1);
      int l = ::a[a].v, r = ::a[b].v, x;
      if (k == 3) x = l & r;
      if (k == 4) x = l ^ r;
      else x = l | r;
      a = nf(k, a, b, x);
    }
    return a;
  }
}

int main() {
  int n, q; cin >> n >> q;
  cin >> s;
  s += '\0';
  int r = parse(ops.size() - 1);
  sort(leaves.begin(), leaves.end(), [&](int i, int j) { return a[i].l < a[j].l; });
  t.root(r);
  auto h = HLD(t, L{1, 0}).fn([](L x, L y) { return x(y); }).hld();
  for (int i = 0; i < fi; i++) {
    /* cout << t.p[i] << ":" << h.U[i] << " "; */
    if (min(a[i].l, a[i].r) >= 0) {
      if (h.U[a[i].l] == h.U[i]) swap(a[i].l, a[i].r); // l should be light child
    }
    h.upd(i, a[i].transform());
  }
  /* cout << endl; */
  vector<P> Q(q);
  vector<int> R(q);
  for (int i = 0; i < q; i++) {
    cin >> Q[i].first;
    Q[i].second = i;
  }
  sort(Q.begin(), Q.end());
  int li = 0;
  for (auto [x, i] : Q) {
    while (li < leaves.size() && x >= a[leaves[li]].l) {
      int c = leaves[li];
      /* cout << a[c].l << endl; */
      a[c].v = 1;
      h.upd(c, L{0, 1});
      while (c != r) {
        c = t.p[c];
        h.upd(c, a[c].transform());
        c = h.U[c];
        L l = h.query(c, h.D[c]);
        assert(!l.w);
        a[c].v = l.b;
        /* cout << c << " " << a[c].v << endl; */
      }
      li++;
    }
    R[i] = a[r].v;
  }
  for (int x: R) cout << (x ? "True\n" : "False\n");
} 
