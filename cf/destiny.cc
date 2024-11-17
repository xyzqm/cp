// https://codeforces.com/problemset/problem/840/D
#include <cassert>
#include <iostream>
#define int long long
#define exit(X) { cout << (X); return; }
using namespace std;
using P = pair<int, int>;
const int inf = 1e18;

const int N = 3e5 + 1;

struct T {
  int v = 0;
  T *L = NULL, *R = NULL;
  T(int v) : v(v) {}
  T(P lr = {0, N}) {
    auto [l, r] = lr;
    if (r - l < 2) return;
    int m = (l + r) >> 1;
    L = new T({l, m});
    R = new T({m, r});
  }
  T(T *L, T *R) : L(L), R(R) { v = L->v + R->v; }
  T* upd(int i, int l = 0, int r = N) {
    if (r - l == 1) return new T(v + 1);
    int m = (l + r) >> 1;
    if (i < m) return new T(L->upd(i, l, m), R);
    else return new T(L, R->upd(i, m, r));
  }
} *t[N];

int n, a[N];

int ac(T* a, T* b, int k, int l = 0, int r = N) {
  int m = (l + r) >> 1;
  if (a == NULL || b == NULL || b->v - a->v <= k) return inf; 
  else if (l + 1 == r) return l;
  else return min(ac(a->L, b->L, k, l, m), ac(a->R, b->R, k, m, r));
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  int q; cin >> n >> q;
  t[0] = new T();
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    t[i] = t[i - 1]->upd(a[i]);
  }
  while (q--) {
    int l, r, k; cin >> l >> r >> k;
    int x = ac(t[l - 1], t[r], (r - l + 1) / k);
    cout << (x == inf ? -1 : x) << endl;
  }
}
