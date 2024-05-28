// https://www.spoj.com/problems/COT3/
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#define int long long
using namespace std;
using P = pair<int, int>;
const int inf = 1e18;

const int N = 1e5 + 1;

int n, c[N], nim[N], o[N];
vector<int> g[N];

struct T {
  int l = 0, r = (1LL << 62) - 1, s = 0, lazy = 0; 
  T *L = NULL, *R = NULL;
  bool full() { return s == r - l + 1; }
  void push() {
    if (lazy & ((r - l + 1) >> 1)) swap(L, R);
    int m = (l + r) >> 1;
    if (L) L->l = l, L->r = m;
    if (R) R->l = m + 1, R->r = r;
    if (L) L->lazy ^= lazy;
    if (R) R->lazy ^= lazy;
    lazy ^= lazy;
  }
  int mex() {
    push();
    if (full()) return r + 1;
    if (!L) return l;
    if (L->full()) return R ? R->mex() : L->r + 1;
    return L->mex();
  }
  void upd(int i) {
    push();
    int m = (l + r) >> 1;
    if (l == r) { s = 1; return; }
    else if (i <= m) (L ? L : L = new T{l, m})->upd(i);
    else (R ? R : R = new T{m + 1, r})->upd(i);
    s = (L ? L->s : 0) + (R ? R->s : 0);
  }
  T* XOR(int x) { lazy ^= x; return this; }
  void merge(T* o) {
    push(); o->push();
    if (l == r) { s = max(s, o->s); return; }
    if (o->L) {
      if (L) L->merge(o->L);
      else L = o->L;
    }
    if (o->R) {
      if (R) R->merge(o->R);
      else R = o->R;
    }
    s = (L ? L->s : 0) + (R ? R->s : 0);
  }
} t[N];

int dfs(int x, int p) {
  for (int y : g[x]) if (y != p) o[x] ^= dfs(y, x);
  for (int y : g[x]) if (y != p) t[x].merge(t[y].XOR(o[x] ^ nim[y]));
  if (!c[x]) t[x].upd(o[x]);
  return nim[x] = t[x].mex();
}

vector<int> r;
void ac(int x, int p, int s) {
  if (!s && !c[x]) r.push_back(x);
  for (int y : g[x]) if (y != p) ac(y, x, s ^ nim[y] ^ o[y]); 
}

signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> c[i];
  for (int i = 1; i < n; i++) {
    int u, v; cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  if (!dfs(1, 0)) { cout << -1 << endl; return 0; }
  ac(1, 0, o[1]);
  sort(r.begin(), r.end());
  for (int x : r) cout << x << endl;
}
