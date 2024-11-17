// https://codeforces.com/contest/1932/problem/G
#include <iostream>
#include <numeric>
#include <queue>
#include <vector>
#define int long long
using namespace std;

const int N = 2e5 + 1;
const int inf = 1e18;

int n, m, H, D[N], l[N], s[N];

int sb(int x, int y) { return ((x - y) % H + H) % H; }

int gcd(int a, int b, int& x, int& y) {
  x = 1, y = 0;
  int x1 = 0, y1 = 1, a1 = a, b1 = b;
  while (b1) {
    int q = a1 / b1;
    tie(x, x1) = make_tuple(x1, sb(x, q * x1 % H));
    tie(y, y1) = make_tuple(y1, sb(y, q * y1 % H));
    tie(a1, b1) = make_tuple(b1, sb(a1, q * b1 % H));
  }
  return a1;
}
int gcd(int a, int b) { int x, y; return gcd(a, b, x, y); }

int inv(int a, int m) {
  int x, y;
  gcd(a, m, x, y);
  return (x % m + m) % m;
}

int cl(int x, int y) { return (x + y - 1) / y; }

vector<int> g[N];

void ac() {
  cin >> n >> m >> H;
  for (int i = 1; i <= n; i++) g[i].clear(), D[i] = inf;
  for (int i = 1; i <= n; i++) cin >> l[i];
  for (int i = 1; i <= n; i++) cin >> s[i];
  for (int i = 0; i < m; i++) {
    int u, v; cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  using T = pair<int, int>;
  priority_queue<T, vector<T>, greater<T>> pq;
  pq.push({D[1] = 0, 1});
  while (pq.size()) {
    auto [d, x] = pq.top(); pq.pop();
    if (d != D[x]) continue;
    for (int y : g[x]) {
      // 1. find k s.t. l_x + k(s_x) = l_y + k(s_y) mod h
      int ds = (((s[x] - s[y]) % H) + H) % H;
      int dl = (((l[y] - l[x]) % H) + H) % H;
      int g = gcd(ds, H);
      if (dl % g != 0) continue;
      int k = dl / g * inv(ds / g, H / g) % (H / g);
      // 2. find next time this overlap will occur --> t = k mod h and t >= d
      int l = (ds ? lcm(ds, H) / ds : 1);
      int t = d <= k ? k : l * cl(d - k, l) + k;
      // 3. profit
      if (++t < D[y]) pq.push({D[y] = t, y});
    }
  }
  cout << (D[n] == inf ? - 1 : D[n]) << endl;
}

signed main() {
  int t; cin >> t;
  while (t--) ac();
}
