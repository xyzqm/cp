// https://codeforces.com/contest/2027/problem/D2
#include "mint.h"
#include <map>
#define int ll
using namespace std;

const int M = 1e9 + 7;

void ac() {
  int n, m; cin >> n >> m;
  vector<int> a(n), b(m), v(n + 1, inf);
  vector<mint> w(n + 1);
  v[0] = 0, w[0] = 1;
  for (int &x : a) cin >> x;
  for (int &x : b) cin >> x;
  for (int i = 0; i < m; i++) {
    map<int, mint> mp;
    map<int, int> fr;
    int l = 0, s = 0;
    for (int r = 0; r <= n; r++) { // delete max range [l, r)
      while (s > b[i]) {
        mp[v[l]] -= w[l];
        if (!--fr[v[l]]) mp.erase(mp.find(v[l]));
        s -= a[l++];
      }
      if (mp.size() && mp.begin()->first != inf) {
        auto [_, W] = *mp.begin();
        int V = _ + m - 1 - i;
        if (V < v[r]) v[r] = V, w[r] = W;
        else if (V == v[r]) w[r] += W;
      }
      mp[v[r]] += w[r], ++fr[v[r]];
      if (r < n) s += a[r];
    }
  }
  if (v[n] == inf) cout << "-1" << endl;
  else cout << v[n] << " " << w[n] << endl;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  int t; cin >> t;
  while (t--) ac();
}
