// https://www.acmicpc.net/problem/15292
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

const int N = 3e3 + 1;
const ll inf = 1e18;

struct E { int v; ll w; };
vector<E> g[N];
ll d[N];

int main() {
  int n, m, k; cin >> n >> m >> k;
  set<ll> s;
  while (m--) {
    int u, v; ll w;
    cin >> u >> v >> w;
    g[u].push_back({v, w});
    g[v].push_back({u, w});
    s.insert(w);
  }
  s.insert(0);
  ll r = inf;
  for (ll W : s) {
    using T = pair<ll, int>;
    priority_queue<T, vector<T>, greater<>> pq;
    fill(d, d + N, inf);
    pq.push({d[1] = 0, 1});
    while (pq.size()) {
      auto [d, u] = pq.top();
      pq.pop();
      if (::d[u] != d) continue;
      for (auto [v, w] : g[u]) {
        w = max(0LL, w - W);
        if (d + w < ::d[v]) pq.push({::d[v] = d + w, v});
      }
    }
    r = min(r, d[n] + W * k);
  }
  cout << r << endl;
}
