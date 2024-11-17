// https://codeforces.com/problemset/problem/1866/H
#include <iostream>
#define int long long
using namespace std;
using P = pair<int, int>;
const int inf = 1e18;

const int N = 2e5 + 1;
const int M = 998244353;
int E(int x, int y) { int r = 1; for (y <<= 1; y >>= 1; x = x * x % M) if (y & 1) r = r * x % M; return r; }
int inv(int x) { return E(x, M - 2); }
int sb(int x, int y) { return ((x - y) % M + M) % M; }
int ad(int& x, int y) { return x = (x + y) % M; }

signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  int n, k; cin >> n >> k;
  int r = 0, f = 1, c = 1;
  for (int i = n; i >= max(0LL, n - k); i--) {
    int x = n - i + 1;
    ad(r, c * f % M * sb(E(x, k - x + 2), E(x - 1, k - x + 2)) % M);
    f = f * x % M;
    c = c * i % M;
  }
  cout << r << endl;
}
