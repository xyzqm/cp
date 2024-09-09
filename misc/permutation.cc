#include <iostream>
#include <map>
#include <functional>
using namespace std;

map<pair<int, int>, int> c;

double phi = 0.618;

int query(int l, int r) {
  if (l == r) return 0;
  if (c[{l, r}]) return c[{l, r}];
  cout << "? " << l << " " << r << endl;
  cin >> c[{l, r}];
  return c[{l, r}];
}

int bs(int l, int r, function<bool(int)> f) {
  while (l < r) {
    int m = (l + r + 1) / 2;
    if (f(m)) l = m;
    else r = m - 1;
  }
  return l;
}

int solve(int l, int r) {
  if (l == r) return l;
  int m = query(l, r);
  int sz = phi * (r - l);
  int L = l, R = r;
  if (l + sz >= m) { R = l = l + sz; ++l; }
  else { L = r = r - sz; --r; }
  if (query(L, R) == m) return solve(L, R);
  else return solve(l, r);
}

void ac() {
  c.clear();
  int n; cin >> n;
  int r = solve(1, n);
  cout << "! " << r << endl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int t; cin >> t;
  while (t--) ac();
}
