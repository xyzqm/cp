#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <set>
using namespace std;
#define int long long
using ll = long long;

const int N = 2e5;

int n, a[N], b[N], r[N];
ll k;

ll solve(int a[N], int b[N]) {
  multiset<int> s;
  for (int i = 0; i < (k - 1) * 2; i += 2) s.insert(b[i]);
  for (int i = 0; i < n; i += 2) {
    s.insert(b[(i + (k - 1) * 2) % n]);
    r[i] = max(abs(a[i] - *s.begin()), abs(a[i] - *s.rbegin()));
    s.erase(b[i]);
  }
  s.clear();
  for (int i = 1; i < (k - 1) * 2 + 1; i += 2) s.insert(b[i]);
  for (int i = 1; i < n; i += 2) {
    s.insert(b[(i + (k - 1) * 2) % n]);
    r[i] = max(abs(a[i] - *s.begin()), abs(a[i] - *s.rbegin()));
    s.erase(b[i]);
  }
  // for (int i = 0; i < n; i++) cout << r[i] << " ";
  // cout << endl;
  return accumulate(r, r + n, 0LL);
}

signed main() {
  int t; cin >> t;
  while (t--) {
    cin >> n >> k;
    k = min((int)k, n / 2);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    ll r = solve(a, b);
    reverse(a, a + n), reverse(b, b + n);
    cout << r + solve(b, a) << "\n";
  }
}
