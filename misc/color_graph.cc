// https://www.luogu.com.cn/problem/P4128
#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>
#define int long long
using namespace std;
using P = pair<int, int>;
const int inf = 1e18;

int M;
int E(int x, int y) { int r = 1; for (y <<= 1; y >>= 1; x = x * x % M) if (y & 1) r = r * x % M; return r; }
int inv(int x) { return E(x, M - 2); }
int sb(int x, int y) { return ((x - y) % M + M) % M; }
int ad(int& x, int y) { return x = (x + y) % M; }

const int N = 54;
int F[N], F_i[N];
void pre(int n) { F[0] = F_i[0] = 1; for (int i = 1; i < n; i++) F_i[i] = inv(F[i] = F[i - 1] * i % M); }
int C(int n, int k) { return F[n] * F_i[n - k] % M * F_i[k] % M; }

int g[N][N];

int n, m, r = 0, t = 0;

vector<int> v;
void dfs(int s = n, int p = 0, int l = 1, int w = 1, int c = 1) {
  for (int i = l; i <= s; i++) {
    v.push_back(i);
    dfs(s - i, p + i / 2, i, w * inv(i) % M * (i == l ? inv(c) : 1) % M, i == l ? c + 1 : 2);
    v.pop_back();
  }
  if (s > 0) return;
  for (int i = 0; i < v.size(); i++) for (int j = i + 1; j < v.size(); j++) {
    p += g[v[i]][v[j]];
  }
  ad(t, F[n] * w % M);
  ad(r, w * E(m, p) % M);
}

signed main() {
  cin >> n >> m >> M;
  pre(N);
  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) g[i][j] = gcd(i, j);
  dfs();
  assert(t == F[n]);
  cout << r << endl;
}
