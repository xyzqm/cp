// https://loj.ac/p/3144
#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#define int long long
using namespace std;
using P = pair<int, int>;
const int inf = 1e18;

const int N = 1e6 + 1;

vector<P> r;

signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  int n, a, b; cin >> n >> a >> b;
  int m = a / gcd(a, b + 1) * b;
  for (int i = 0; i < n; i++) {
    int l, r; cin >> l >> r;
    if (r - l > m - 1) { cout << m << endl; return 0; }
    l %= m, r %= m;
    if (l <= r) ::r.push_back({l, r}); 
    else { ::r.push_back({l, m - 1}); ::r.push_back({0, r}); }
  }
  int r = 0, cr = -inf;
  sort(::r.begin(), ::r.end());
  for (int i = 0; i < ::r.size(); i++) {
    if (cr >= ::r[i].second) continue;
    r += ::r[i].second - max(::r[i].first - 1, cr);
    cr = max(cr, ::r[i].second);
  }
  cout << r << endl;
}
