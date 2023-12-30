#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
#define int long long
const int inf = 1e18;
using P = pair<int, int>;
const int N = 1e5 + 1;
int n, q, k, t[N], l[N], r[N], a[N], A[N], S[4 * N], L[4 * N];
void pull(int x) { S[x] = S[2 * x] + S[2 * x + 1]; }
void apply(int x, int l, int r, int t) { 
  S[x] = (L[x] = t) * (r - l + 1);
}
void push(int x, int l, int r) {
  if (L[x] >= 0) {
    int m = (l + r) >> 1;
    apply(2 * x, l, m, L[x]);
    apply(2 * x + 1, m + 1, r, L[x]);
    L[x] = -1;
  }
}
int qry(int x, int y, int i = 1, int l = 1, int r = n) {
  if (r < x || l > y) return 0;
  else if (x <= l && r <= y) { 
    return S[i];
  }
  else {
    int m = (l + r) >> 1;
    push(i, l, r);
    int z = qry(x, y, 2 * i, l, m) + qry(x, y, 2 * i + 1, m + 1, r);
    return z;
  }
}
void upd(int x, int y, int v, int i = 1, int l = 1, int r = n) {
  if (r < x || l > y) return;
  else if (x <= l && r <= y) apply(i, l, r, v);
  else {
    int m = (l + r) >> 1;
    push(i, l, r);
    upd(x, y, v, 2 * i, l, m);
    upd(x, y, v, 2 * i + 1, m + 1, r);
    pull(i);
  }
}
void build(int i = 1, int l = 1, int r = n) {
  L[i] = -1;
  if (l == r) S[i] = a[l];
  else {
    int m = (l + r) >> 1;
    build(2 * i, l, m);
    build(2 * i + 1, m + 1, r);
    pull(i);
  }
}
bool ck(int x) { // whether the answer is > x
  for (int i = 1; i <= n; i++) a[i] = (A[i] > x);
  build();
  for (int i = 0; i < q; i++) {
    int 一 = qry(l[i], r[i]);
    if (t[i] == 0) { // sort increasing
      upd(l[i], r[i] - 一, 0);
      upd(r[i] - 一 + 1, r[i], 1);
    } else {
      upd(l[i], l[i] + 一 - 1, 1);
      upd(l[i] + 一, r[i], 0);
    }
  }
  return qry(k, k);
}
signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> q;
  for (int i = 1; i <= n; i++) cin >> A[i];
  for (int i = 0; i < q; i++) cin >> t[i] >> l[i] >> r[i];
  cin >> k;
  int r = 0;
  for (int d = n; d > 0; d /= 2) while (r + d < n && ck(r + d)) r += d;
  cout << ++r << endl;
  return 0;
}