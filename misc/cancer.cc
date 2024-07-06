// https://loj.ac/p/2496
#include <cassert>
#include <iostream>
#include <vector>
#define int long long
#define exit(X) { cout << (X); return; }
using namespace std;
const int inf = 1e18;

const int N = 1e5 + 1;

vector<int> g[N];
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
  mint& operator*=(const mint& o) { mint t = v * o.v; v = t.v; return *this; }
  mint operator-(const mint &o) const { return v - o.v; }
  mint& operator-=(const mint& o) { mint t = v - o.v; v = t.v; return *this; }
  friend istream& operator>>(istream& s, mint& v) { s >> v.v; return s; }
  friend ostream& operator<<(ostream& s, const mint& v) { s << v.v; return s; }
  operator int() const { return v; }
};
int n, m, p[N], id[N], t = 0;

struct V { mint u, v; mint& operator[](int i) { return i ? v : u; };
  V operator*(V o) { return {u * o.u, v * o.v}; }
  V operator*=(V o) { u *= o.u, v *= o.v; return *this; }
} dp[N], x[N];
struct M { mint a[2][2]{}; mint* operator[](int i) { return a[i]; }
  M operator*(M o) {
    M v; for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++) for (int k = 0; k < 2; k++) v[i][j] += a[i][k] * o[k][j];
    return v;
  }
  V operator*(V x) { return V{x.u * a[0][0] + x.v * a[0][1], x.u * a[1][0] + x.v * a[1][1]}; }
  M dot(V x) { auto [u, v] = x; M m = *this; m[0][0] *= u; m[0][1] *= u; m[1][0] *= v; m[1][1] *= v; return m; }
} T{{{1, 1}, {1, 0}}};

struct E { int v = 0; M t; };
vector<E> g_v[N]; vector<V> e;
void mark(int x) { if (!id[x]) id[x] = ++t; assert(t < 32); }
void mark(int x, int y) { mark(x), mark(y); if (x < y) e.push_back({x, y}); }
vector<int> v;

E dfs(int x = p[1] = 1) {
  dp[x] = {1, 1};
  vector<E> r;
  for (int y : g[x]) { if ((y != p[x] && !p[y]) || p[y] == x) {
    p[y] = x;
    E e = dfs(y);
    if (e.v) r.push_back(e);
    else dp[x] *= T * dp[y];
  } else if (y != p[x]) mark(x, y); }
  if (r.size() > 1 || id[x]) for (E e : r) g_v[x].push_back(e);
  if (id[x] || r.size() > 1) return E{x, T};
  else if (r.size() == 1) return E{r[0].v, T * (r[0].t.dot(dp[x]))};
  else return E{};
}

mint ac(int m, int u = 1) {
  x[u] = dp[u];
  for (auto [v, t] : g_v[u]) {
    ac(m, v);
    x[u] *= t * x[v];
  }
  if (m >> id[u] & 1) x[u][0] = 0;
  return x[u][0] + x[u][1];
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int x, y; cin >> x >> y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  mark(1); dfs();
  assert(e.size() == m - n + 1);
  mint r = 0;
  for (int i = 0; i < (1 << e.size()); i++) {
    int m = 0;
    for (int j = 0; j < e.size(); j++) if (i >> j & 1) m |= 1 << id[e[j].u] | 1 << id[e[j].v];
    assert(!(m & 1));
    r += ac(m, 1) * mint(__builtin_popcount(i) & 1 ? -1 : 1);
  }
  cout << r << endl;
}
