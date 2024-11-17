// https://codeforces.com/problemset/problem/1929/F
#include <iostream>
#define int long long
using namespace std;
using P = pair<int, int>;
const int inf = 1e18;

const int M = 998244353;
int E(int x, int y) { int r = 1; for (y <<= 1; y >>= 1; x = x * x % M) if (y & 1) r = r * x % M; return r; }
int inv(int x) { return E(x, M - 2); }

const int N = 5e5 + 1;

int n, c, t, x, r, L[N], R[N], v[N];

void add(int y) {
  if (y == -1) { ++t; return; }
  for (int i = y - x + t; i > y - x; i--) r = r * i % M;
  for (int i = 1; i <= t; i++) r = r * inv(i) % M;
  x = y, t = 0;
}

void dfs(int y) {
  if (L[y] >= 0) dfs(L[y]);
  add(v[y]);
  if (R[y] >= 0) dfs(R[y]);
}

void ac() {
  cin >> n >> c; t = 0, r = 1, x = 1;
  for (int i = 1; i <= n; i++) cin >> L[i] >> R[i] >> v[i];
  dfs(1); add(c);
  cout << r << endl;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  int t; cin >> t;
  while (t--) ac();
}
