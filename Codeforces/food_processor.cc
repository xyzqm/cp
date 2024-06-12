// https://open.kattis.com/contests/n2jtkf/problems/foodprocessor
#include <cmath>
#include <functional>
#include <iomanip>
#include <ios>
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;
using P = pair<int, int>;
const int inf = 1e18;

const int N = 1e5 + 1;

P a[N];

signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  int s, t, n; cin >> s >> t >> n;
  for (int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
  sort(a, a + n, greater<P>());
  if (a[0].first < s) { cout << -1 << endl; return 0; }
  long double r = 0;
  int c = inf;
  int i = 0;
  while (i + 1 < n && a[i + 1].first >= s) c = min(c, a[i++].second);
  for ( ; i < n; i++) {
    c = min(c, a[i].second); 
    int x = max(i < n - 1 ? a[i + 1].first : 0, t);
    int y = min(s, a[i].first);
    r += (log2(y) - log2(x)) * c;
    if (x == t) break;
  }
  cout << fixed << setprecision(30) << r << endl;
}
