#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <queue>
using namespace std;
#define int long long
const int inf = 1e18;
using P = pair<int, int>;
using T = tuple<int, int, int>;
const int N = 3e5 + 1;
vector<P> g[N];
vector<T> E;
int n, m, df[N], ds[N];
void dj(int s, int d[]) {
  priority_queue<P, vector<P>, greater<P>> pq;
  fill(d, d + N, inf);
  pq.push({d[s] = 0, s});
  while (pq.size()) {
    auto [D, x] = pq.top();
    pq.pop();
    if (D != d[x]) continue;
    for (auto [y, w] : g[x]) if (max(D, w) < d[y]) {
      pq.push({d[y] = max(D, w), y});
    }
  }
}
signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    g[u].push_back({v, w});
    g[v].push_back({u, w});
    E.push_back({u, v, w});
  }
  dj(1, df);
  dj(n, ds);
  int r = inf;
  for (auto [u, v, w] : E) {
    if (max(df[u], ds[v]) <= w) r = min(r, w + max(df[u], ds[v]));
    if (max(df[v], ds[u]) <= w) r = min(r, w + max(df[v], ds[u]));
  }
  cout << r << endl;
  return 0;
}