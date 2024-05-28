// https://codeforces.com/problemset/problem/1082/G
#include <iostream>
#include <queue>
#include <vector>
#define int long long
using namespace std;
using P = pair<int, int>;
const int inf = 1e18;

const int N = 1e3 + 1;

int n, m, t = 0, lv[2 * N], f[10 * N];

struct E {
  int y, id, cap;
};

vector<E> g[N * N];
vector<E>::iterator e[N * N];

void add_edge(int x, int y, int cap) {
  g[x].push_back({y, t++, cap});
  g[y].push_back({x, t++, 0});
}

bool bfs(int s, int t) {
  for (int i = 0; i <= t; i++) lv[i] = inf;
  queue<int> q;
  q.push(lv[s] = 0);
  while (q.size()) {
    int x = q.front(); q.pop();
    if (x == t) return true;
    for (auto [y, id, cap] : g[x]) if (cap > f[id] && lv[y] > lv[x] + 1) {
      lv[y] = lv[x] + 1; q.push(y);
    }
  }
  return false;
}

int dfs(int x, int fl, int t) {
  if (x == t) return fl;
  for (; e[x] != g[x].end(); e[x]++) {
    auto [y, id, cap] = *e[x];
    if (lv[y] != lv[x] + 1 || f[id] >= cap) continue; 
    int nf = dfs(y, min(fl, cap - f[id]), t);
    if (nf > 0) {
      f[id] += nf, f[id^1] -= nf;
      return nf;
    }
  }
  return 0;
}

int dinic(int s, int t) {
  int r = 0;
  while (bfs(s, t)) {
    for (int i = 0; i <= t; i++) e[i] = g[i].begin();
    while (int x = dfs(s, inf, t)) {
      r += x;
    }
  }
  return r;
}
signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  cin >> n >> m;
  int t = n + m + 1;
  int r = 0;
  for (int i = 1; i <= n; i++) {
    int x; cin >> x;
    add_edge(m + i, t, x);
  }
  for (int i = 1; i <= m; i++) {
    int u, v, w; cin >> u >> v >> w; r += w;
    add_edge(i, m + u, inf);
    add_edge(i, m + v, inf);
    add_edge(0, i, w);
  }
  cout << r - dinic(0, t) << endl;
}
