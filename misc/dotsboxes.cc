// https://open.kattis.com/problems/dotsboxes
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>
#define int long long
using namespace std;
using P = pair<int, int>;
const int inf = 1e18;

const int N = 85;

int n, t = 0, lv[N * N], c[N * N], f[10 * N * N]; char a[2 * N][2 * N];
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

int id(int x, int y) {
  assert(x % 2 == 0 && y % 2 == 0);
  return (x / 2) * (n + 1) + y / 2 + 1;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  cin >> n;
  for (int i = 1; i < 2 * n; i++) {
    for (int j = 1; j < 2 * n; j++) {
      cin >> a[i][j];
      if (a[i][j] == '-') {
        if (i > 1) c[id(i - 1, j)]++;
        if (i < 2 * n - 1) c[id(i + 1, j)]++;
      }
      if (a[i][j] == '|') {
        if (j > 1) c[id(i, j - 1)]++;
        if (j < 2 * n - 1) c[id(i, j + 1)]++;
      }
    }
  }
  int t = (n + 1) * (n + 1) + 1;
  for (int i = 0; i <= 2 * n; i += 2) {
    for (int j = 0; j <= 2 * n; j += 2) {
      int ID = id(i, j);
      if (min(i, j) == 0 || max(i, j) == 2 * n) c[ID] = -inf;
      if ((i + j) % 4) add_edge(ID, t, 3 - c[ID]);
      else add_edge(0, id(i, j), 3 - c[ID]);
      if (j && j < 2 * n) {
        if (i && a[i - 1][j] != '-') add_edge(ID, ID - n - 1, 1);
        if (i < 2 * n && j < 2 * n && a[i + 1][j] != '-') add_edge(ID, ID + n + 1, 1);
      }
      if (i && i < 2 * n) {
        if (j && a[i][j - 1] != '|') add_edge(ID, ID - 1, 1);
        if (j < 2 * n && a[i][j + 1] != '|') add_edge(ID, ID + 1, 1);
      }
    }
  }
  cout << dinic(0, t) + 1 << endl;
}
