// https://acm.timus.ru/problem.aspx?space=1&num=1132
#include <cassert>
#include <iostream>
#include <random>
#include <chrono>
#define int long long
using namespace std;
using P = pair<int, int>;
const int inf = 1e18;

const int N = 1e5 + 1;
int M = 0;
int E(int x, int y) { int r = 1; for (y <<= 1; y >>= 1; x = x * x % M) if (y & 1) r = r * x % M; return r; }
int inv(int x) { return E(x, M - 2); }
int sb(int x, int y) { return ((x - y) % M + M) % M; }
int ad(int x, int y) { return (x % M + y % M) % M; }
int sym(int n) { return E(n, (M - 1) / 2); }

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

void ac() {
  int n; cin >> n >> M;
  if (sym(n) != 1) { cout << "No root\n"; return; }
  if (M == 2) {
    if (n & 1) cout << "1\n";
    else cout << "No root\n";
    return;
  }
  int a = 0;
  while (sym(sb(a * a % M, n)) != M - 1) a = rng() % M;
  /* a = 2; */
  int w = sb(a * a % M, n);
  auto mul = [&](P x, P y) { return P{
    ad(x.first * y.first, x.second * y.second % M * w),
    ad(x.first * y.second, x.second * y.first) 
  }; }; 
  P c = {a, 1}, r = {1, 0};
  for (int i = 1; i < 2 * M; i <<= 1) {
    if (((M + 1) / 2) & i) r = mul(r, c);
    c = mul(c, c);
  }
  assert(r.second == 0);
  int x = r.first, y = M - r.first;
  if (x > y) swap(x, y);
  cout << x << " " << y << endl;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  int t; cin >> t;
  while (t--) ac();
}
