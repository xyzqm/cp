// https://www.luogu.com.cn/problem/P5633
#include <iostream>
#include <numeric>
#include <algorithm>
#include <utility>
using namespace std;
using ll = long long;
const int N = 5e5 + 1;

struct DSU {
  int p[N], s[N];
  void init(int n) {
    iota(p, p + n + 1, 0);
    fill(s, s + n + 1, 1);
  }
  int fa(int x) {
  	return p[x] == x ? p[x] : (p[x] = fa(p[x]));
  }
  bool unite(int x, int y) {
  	x = fa(x), y = fa(y);
  	if (x == y) return false;
  	if (s[x] < s[y]) swap(x, y);
  	p[y] = x;
  	s[x] += s[y];
  	return true;
  }
} dsu;

struct E { int u, v; ll w; } e[N];

int n, m, s, k;

auto ac(ll l) {
  dsu.init(n);
  sort(e, e + m, [=](E e, E f) {
    return e.w + (e.u == s || e.v == s) * l < f.w + (f.u == s || f.v == s) * l;
  });
  ll r = 0;
  int c = 0;
  for (int i = 0; i < m; i++) {
    auto [u, v, w] = e[i];
    if (dsu.unite(u, v)) {
      bool x = (u == s || v == s);
      r += w + x * l;
      c += x;
    }
  }
  return make_pair(r, c);
}

int d[N];

int main() {
  cin >> n >> m >> s >> k;
  for (int i = 0; i < m; i++) {
    cin >> e[i].u >> e[i].v >> e[i].w;
    ++d[e[i].u], ++d[e[i].v];
  }
  ll l = -1e5, r = 1e5;
  for (ll d = r - l; d > 0; d /= 2) {
    while (l + d < r && ac(l + d).second >= k) l += d;
  }
  auto [v, c] = ac(l);
  if (d[s] < k || dsu.s[dsu.fa(s)] != n || c > k) cout << "Impossible" << endl;
  else cout << v - l * k << endl;
}
