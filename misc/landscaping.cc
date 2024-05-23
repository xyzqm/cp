// https://open.kattis.com/problems/landscaping
#include <iostream>
#include <queue>
#include <vector>
#define int long long
using namespace std;
using P = pair<int, int>;
const int inf = 1e18;

const int N = 1e5 + 1;

int n, m, a, b, t = 0, lv[N], f[N];
char c[51][51];

struct E {
  int y, id, cap;
};
vector<E> g[N];
vector<E>::iterator e[N];

void add_edge(int x, int y, int cap) {
  g[x].push_back({y, t++, cap});
  g[y].push_back({x, t++, 0});
}

bool bfs() {
  for (int i = 0; i <= n * m + 1; i++) lv[i] = inf;
  queue<int> q;
  q.push(lv[0] = 0);
  while (q.size()) {
    int x = q.front(); q.pop();
    if (x == n * m + 1) return true;
    for (auto [y, id, cap] : g[x]) if (cap > f[id] && lv[y] > lv[x] + 1) {
      lv[y] = lv[x] + 1; q.push(y);
    }
  }
  return false;
}

int dfs(int x, int fl) {
  if (x == n * m + 1) return fl;
  for (; e[x] != g[x].end(); e[x]++) {
    auto [y, id, cap] = *e[x];
    if (lv[y] != lv[x] + 1 || f[id] >= cap) continue; 
    int nf = dfs(y, min(fl, cap - f[id]));
    if (nf > 0) {
      f[id] += nf, f[id^1] -= nf;
      return nf;
    }
  }
  return 0;
}

int dinic() {
  int r = 0;
  while (bfs()) {
    for (int i = 0; i <= n * m + 1; i++) e[i] = g[i].begin();
    while (int t = dfs(0, inf)) {
      r += t;
    }
  }
  return r;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  cin >> n >> m >> a >> b;
  for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
    int id = (i - 1) * m + j;
    cin >> c[i][j];
    if (c[i][j] == '.') add_edge(0, id, b);
    else add_edge(id, n * m + 1, b);
    if (i > 1) {
      add_edge(id, id - m, a);
      add_edge(id - m, id, a);
    }
    if (j > 1) {
      add_edge(id, id - 1, a);
      add_edge(id - 1, id, a);
    }
  }
  cout << dinic() << endl;
}
