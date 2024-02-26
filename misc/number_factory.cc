#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
#define int long long
const int inf = 1e18;
using P = pair<int, int>;
using T = tuple<int, int, int>;
const int N = 1e5 + 1;
const int M = 1e9 + 7;
P S[4 * N], a[N];
int n, m;
P operator*(P a, P b) { return {b.first * a.first % M, (b.first * a.second % M + b.second) % M}; }
P qry(int x, int y, int i = 1, int l = 1, int r = n) {
  if (r < x || l > y) return {1, 0};
  else if (x <= l && r <= y) return S[i];
  else {
    int m = (l + r) >> 1;
    return qry(x, y, 2 * i, l, m) * qry(x, y, 2 * i + 1, m + 1, r);
  }
}
void upd(int x, P v, int i = 1, int l = 1, int r = n) {
  if (l == r) S[i] = v;
  else {
    int m = (l + r) >> 1;
    if (x <= m) upd(x, v, 2 * i, l, m);
    else upd(x, v, 2 * i + 1, m + 1, r);
    S[i] = S[2 * i] * S[2 * i + 1];
  }
}
void build(int i = 1, int l = 1, int r = n) {
  if (l == r) S[i] = a[l];
  else {
    int m = (l + r) >> 1;
    build(2 * i, l, m);
    build(2 * i + 1, m + 1, r);
    S[i] = S[2 * i] * S[2 * i + 1];
  }
}
P OP(char op, int x) {
  if (op == '+') return {1, x};
    else if (op == '-') return {1, (M - x) % M};
    else return {x, 0}; 
}
signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    char op;
    int x;
    cin >> op >> x;
    a[i] = OP(op, x);
  }
  build();
  while (m--) {
    char c; cin >> c;
    if (c == 'q') {
      int x, i;
      cin >> x >> i;
      P op = qry(1, i);
      cout << (op.first * x % M + op.second) % M << endl;
    } else {
      int i, x;
      cin >> i >> x;
      char op; cin >> op;
      upd(i, OP(op, x));
    }
  }
  return 0;
}