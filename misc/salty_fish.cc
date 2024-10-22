// https://www.acmicpc.net/problem/18586
#include "bits/stdc++.h"
using ll = long long;
using namespace std;

const int N = 3e5 + 1;

vector<int> g[N], e[N];
int n, q, f[N], x[N], k[N], d[N];
ll v[N], c[N];

struct _ { bool operator()(int u, int v) const { return u > v; }; };
map<int, ll, _> mp[N];

void dfs(int u) {
  mp[u][d[u] = d[f[u]] + 1] += v[u];
  for (int y : g[u]) {
    dfs(y);
    if (mp[u].size() < mp[y].size()) mp[u].swap(mp[y]);
    for (auto [k, v] : mp[y]) mp[u][k] += v; 
    mp[y].clear();
  }
  sort(e[u].begin(), e[u].end(), [](int u, int v) { return k[u] > k[v]; });
  for (int y : e[u]) {
    for (auto it = mp[u].lower_bound(d[u] + k[y]); c[y] && it != mp[u].end(); ) {
      ll del = min(it->second, c[y]);
      // if element becomes 0, erase it
      if (!(c[y] -= del, it->second -= del)) it = mp[u].erase(it);
    };
  }
}

void ac() {
  cin >> n >> q;
  for (int i = 1; i <= n; i++) g[i].clear(), e[i].clear();
  for (int i = 2; i <= n; i++) {
    cin >> f[i];
    g[f[i]].push_back(i);
  }
  for (int i = 1; i <= n; i++) cin >> v[i];
  for (int i = 1; i <= q; i++) {
    cin >> x[i] >> k[i] >> c[i];
    e[x[i]].push_back(i);
  }
  dfs(1);
  cout << accumulate(mp[1].begin(), mp[1].end(), 0LL, [](ll v, const auto& el) { return v + el.second; }) << endl;
  mp[1].clear();
}

int main() {
  int t; cin >> t;
  while (t--) ac();
}
