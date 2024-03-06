// https://judge.yosupo.jp/problem/static_range_inversions_query
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;
using P = pair<int, int>;
const int N = 1e5 + 1;
const int S = 300;

int n, bit[N];
ll ans[N];

void upd(int i, int x) {
  for (; i <= n; i += i & -i) bit[i] += x;
}

int query(int r) {
  int res = 0;
  for (; r > 0; r -= r & -r) res += bit[r];
  return res;
}

struct Q { int l, r, i; } q[N];

int main() {
  int k; cin >> n >> k;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  vector<int> b(a);
  sort(b.begin(), b.end());
  b.erase(unique(b.begin(), b.end()), b.end());
  auto id = [&](int x) { return upper_bound(b.begin(), b.end(), a[x]) - b.begin(); };
  for (int i = 0; i < k; i++) {
    q[i].i = i;
    cin >> q[i].l >> q[i].r;
  }
  q[k++] = {0, 0};
  sort(q, q + k, [](Q x, Q y) {
    if (x.l / S != y.l / S) return x.l / S < y.l / S;
    else return x.r < y.r;
  });
  ll res = 0;
  auto edit = [&](int id, int x, bool left) {
    res += (left ? query(id - 1) : query(n) - query(id)) * x;
    upd(id, x);
  };
  for (int i = 0; i < k; i++) {
    if (i) ans[q[i].i] = res;
    if (i == k - 1) break;
    while (q[i].l > q[i + 1].l) edit(id(--q[i].l), 1, true);
    while (q[i].r < q[i + 1].r) edit(id(q[i].r++), 1, false);
    while (q[i].l < q[i + 1].l) edit(id(q[i].l++), -1, true);
    while (q[i].r > q[i + 1].r) edit(id(--q[i].r), -1, false);
  }
  for (int i = 0; i < k - 1; i++) cout << ans[i] << '\n';
}
