// https://codeforces.com/problemset/problem/1863/E
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#define int long long
using namespace std;
using P = pair<int, int>;
const int inf = 1e18;

const int N = 2e5 + 1;

int n, m, k, h[N], v[N], t[N];
vector<int> g[N];

void ac() {
  for (int i = 1; i <= n; i++) g[i].clear(), t[i] = v[i] = 0;
  cin >> n >> m >> k;
  for (int i = 1; i <= n; i++) cin >> h[i];
  while (m--) {
    int u, v; cin >> u >> v;
    g[u].push_back(v);
  }
  vector<int> l;
  for (int i = 1; i <= n; i++) {
    if (t[i] % k <= h[i]) t[i] = k * (t[i] / k) + h[i];
    else t[i] = k * (t[i] / k + 1) + h[i];
    if (t[i] < k) l.push_back(i);
    for (int j : g[i]) t[j] = max(t[j], t[i]);
  }
  sort(l.begin(), l.end(), [](int x, int y) { return t[x] > t[y]; });
  int f = *max_element(t, t + n + 1), r = inf;
  while (l.size()) {
    int x = l.back(); l.pop_back(); if (t[x] >= k) continue;
    r = min(r, f - t[x]);
    queue<int> q; q.push(x);
    while (q.size()) {
      int x = q.front(); q.pop(); 
      if (v[x]) continue; v[x] = true;
      f = max(f, t[x] += k);
      for (int y : g[x]) if (t[x] > t[y]) q.push(y);
    }
  }
  cout << r << endl;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  int t; cin >> t;
  while (t--) ac();
}
