// https://www.luogu.com.cn/problem/P3199
#include <cassert>
#include <iomanip>
#include <ios>
#include <iostream>
#include <vector>
#define int long long
using namespace std;
using P = pair<int, int>;
const int inf = 1e18;

const int N = 3e3 + 1;
int n, m;
double d[N];
struct E { int u, v; double w; };
vector<E> e;

bool ck(double x) {
  fill(d, d + N, 0);
  for (int i = 0; i < n; i++) {
    for (auto [u, v, w] : e) {
      w -= x;
      if (d[v] > d[u] + w) {
        if (i == n - 1) return true;
        else d[v] = d[u] + w;
      }
    }
  } 
  return false;
}
signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int u, v; double w; cin >> u >> v >> w;
    e.push_back({u, v, w});
  }
  /* cout << ck(5) << endl; */
  double x = 1e7;
  for (double d = 2e7; d > 1e-9; d /= 2) {
    while (ck(x - d)) x -= d;
  }
  cout << fixed << setprecision(8) << x << endl;
}
