/**
Solution sketch:
1. Find expected moves for each node to go to its parent
  -> e_to[i] = 1 + [P(i -> child) * (e_to[child] + e_to[i])] for all children
  ->  e_to[i] * P(i -> parent) = 1 + [P(i -> child) * e_to[child]] for all children

2. Find expected moves to get to each node from parent
  -> e_from[i] = 1 + [P(parent -> sibling) * (e_to[sibling] + e_from[i])] for all siblings
                   + P(parent -> grandparent) * (e_from[parent] + e_from[i])
  -> e_from[i] * P(parent -> i) = 1 + [P(parent -> sibling) * e_to[sibling]] for all siblings
                                    + P(parent -> grandparent) * e_from[parent]
3. Binary lift
  -> j_to[i][k] -> expected moves to go to i's 2^kth ancestor
  -> j_from[i][k] -> expected moves to come from i's 2^kth anscestor

4. Profit!
*/

#include <iostream>
#include <vector>
#define int long long
using namespace std;

const int N = 1e5 + 1;
const int M = 998244353;
const int K = 20;

int P(int x, int y) {
  int r = 1;
  for (y <<= 1; y >>= 1; x = x * x % M) if (y & 1) r = r * x % M;
  return r;
}

int n, C[N], p[N], j_p[N][K], d[N];

// fraction
struct F {
  int n, d;
  F reduce() {
    while (n < 0) n += M;
    while (d < 0) d += M;
    n %= M, d %= M;
    return *this;
  }
  int mod() { return n * P(d, M - 2) % M; }
  F operator*(const F& o) { return F{n * o.n, d * o.d}.reduce(); }
  F operator+(const F& o) { return F{n * o.d + o.n * d, d * o.d}.reduce(); }
  F operator+=(const F& o) { return *this = *this + o; }
  F operator-(const F& o) { return *this + F{-o.n, o.d}.reduce(); }
  F operator/(const F& o) { return *this * F{o.d, o.n}.reduce(); }
  F operator/=(const F& o) { return *this = *this / o; }
} p_to[N], e_to[N], p_from[N], e_from[N], j_to[N][K], j_from[N][K];

ostream& operator<<(ostream& os, const F& f) {
  os << f.n << "/" << f.d;
  return os;
}

struct E { int v, w; };

vector<E> g[N];

F expected_to(int x = 1) {
  p_to[x] = {0, 1};
  F r = {1, 1};
  for (auto [v, w] : g[x]) {
    if (v == p[x]) p_to[x] = F{w, C[x]}.reduce();
    else {
      p[v] = x, d[v] = d[x] + 1;
      p_from[v] = F{w, C[x]}.reduce();
      r += p_from[v] * expected_to(v);
    }
  }
  return e_to[x] = r / p_to[x];
}

void expected_from(int x = 1) {
  if (!p[x]) e_from[x] = {0, 1};
  F siblings = {0, 1};
  for (auto [v, _] : g[x]) if (v != p[x]) {
    siblings += p_from[v] * e_to[v];
  }
  for (auto [v, _] : g[x]) if (v != p[x]) {
    e_from[v] = F{1, 1}
                + (siblings - p_from[v] * e_to[v])
                + p_to[x] * e_from[x];
    e_from[v] /= p_from[v];
    expected_from(v);
  }
}

void ac() {
  int q; cin >> n >> q;
  for (int i = 1; i <= n; i++) g[i].clear(), C[i] = 0;
  for (int i = 1; i < n; i++) {
    int u, v, c1, c2; cin >> u >> v >> c1 >> c2;
    g[u].push_back({v, c1});
    g[v].push_back({u, c2});
    C[u] += c1, C[v] += c2;
  }

  expected_to();
  for (int i = 1; i <= n; i++) j_p[i][0] = p[i];
  for (int i = 1; i <= n; i++) j_to[i][0] = e_to[i];
  expected_from();
  for (int i = 1; i <= n; i++) j_from[i][0] = e_from[i];

  for (int k = 1; k < K; k++) {
    for (int i = 1; i <= n; i++) {
      int P = j_p[i][k - 1];
      j_p[i][k] = j_p[P][k - 1];
      j_to[i][k] = j_to[i][k - 1] + j_to[P][k - 1];
      j_from[i][k] = j_from[P][k - 1] + j_from[i][k - 1];
    }
  }

  while (q--) {
    int s, t; cin >> s >> t;
    F r = {0, 1};
    for (int k = K; k --> 0; ) if (max(d[s] - d[t], 0LL) >> k & 1) {
      r += j_to[s][k];
      s = j_p[s][k];
    }
    for (int k = K; k --> 0; ) if (max(d[t] - d[s], 0LL) >> k & 1) {
      r += j_from[t][k];
      t = j_p[t][k];
    }
    for (int k = K; k --> 0; ) if (j_p[s][k] != j_p[t][k]) {
      r += j_to[s][k] + j_from[t][k];
      s = j_p[s][k], t = j_p[t][k];
    }
    if (s != t) r += e_to[s] + e_from[t];
    cout << r.mod() << endl;
  }
}

signed main() {
  int t; cin >> t;
  while (t--) ac();
}
