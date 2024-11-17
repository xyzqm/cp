// https://codeforces.com/problemset/problem/1912/B
#include <iostream>
#define int long long
using namespace std;
using P = pair<int, int>;
const int inf = 1e18;

const int N = 1e5 + 1;

const int M = 998244353;
int E(int x, int y) { int r = 1; for (y <<= 1; y >>= 1; x = x * x % M) if (y & 1) r = r * x % M; return r; }
int inv(int x) { return E(x, M - 2); }
int sb(int x, int y) { return ((x - y) % M + M) % M; }
int ad(int& x, int y) { return x = (x + y) % M; }

int F[N], F_i[N];
void pre(int n) { F[0] = F_i[0] = 1; for (int i = 1; i < n; i++) F_i[i] = inv(F[i] = F[i - 1] * i % M); }
int C(int n, int k) { return F[n] * F_i[n - k] % M * F_i[k] % M; }

int t(int n) { --n; return n * (n + 1) / 2; }
int tt(int n) { return t(n / 2) + t((n + 1) / 2); }

void ac() {
  int n, k; cin >> n >> k;
  // split n into r groups of odd size, and k - r groups of even size
  // smaller size is g
  int g = n / k, r = n % k;
  int y = (k - r) * tt(g) + r * tt(g + 1);
  if (g % 2) r = k - r;
  int x = 0; // total number of ways
  for (int i = 0; 2 * i <= r; i++) { // number of odd pairs we split
    if (i && g == 1) break;
    int o = r - 2 * i, e1 = k - r + i, e2 = i; 
    // case 1: first value is even
    if (e1) ad(x, C(k - 1, e1 - 1) % M * C(k - e1, e2) % M);
    if (e2) ad(x, C(k - 1, e2 - 1) % M * C(k - e2, e1) % M); 
    // case 2: first value is odd
    if (o && g > 1) ad(x, 2 * C(k - 1, o - 1) % M * C(k - o, e1) % M);
  }
  cout << y << " " << x << endl;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  pre(N);
  int t; cin >> t;
  while (t--) ac();
}
