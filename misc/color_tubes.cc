// https://open.kattis.com/contests/n2jtkf/problems/colortubes  
#include <array>
#include <vector>
#include <cassert>
#include <iostream>
#define int long long
using namespace std;
using P = pair<int, int>;
const int inf = 1e18;

const int N = 1e3 + 2;

int n, a[N][3];

int f(int i) {
  for (int j = 0; j < 3; j++) if (!a[i][j]) return j;
  return 3;
}

void pr() {
  for (int i = 1; i <= n + 1; i++) {
    for (int j = 0; j < 3; j++) cout << a[i][j] << " ";
    cout << endl;
  }
}

vector<P> m;

void mv(int i, int j) {
  /* pr(); */
  /* cout << j << " " << i << endl; */
  assert(i != j);
  assert(i != j && f(j) < 3 && f(i));
  m.push_back({i, j});
  swap(a[i][f(i) - 1], a[j][f(j)]);
}

P xy(int i, int v) {
  for (int j = 1; j < i; j++) for (int k = 3; k --> 0; ) if (a[j][k] == v) return {j, k};
  assert(false);
}

signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  cin >> n;
  for (int i = 1; i <= n + 1; i++) for (int j = 0; j < 3; j++) cin >> a[i][j];
  for (int i = n + 1; i > 1; i--) {
    // clear out row i
    while (f(i)) {
      /* cout << f(i) << endl; */
      for (int k = 1; k < i; k++) if (f(k) < 3) { mv(i, k); break; }
    }
    // let me cook
    assert(!a[i][0] && !a[i][1] && !a[i][2]);
    mv(i - 1, i);
    auto [w, x] = xy(i, a[i][0]);
    int c = 0; while (f(w) > x + 1) mv(w, i), ++c;
    if (w != i - 1) mv(w, i - 1);
    while (c--) mv(i, w);
    mv(i - 1, i);
    auto [y, z] = xy(i, a[i][0]);
    array<int, 2> a = {w, i - 1}; c = 0;
    while (f(y) > z + 1) {
      if (y != a[c]) mv(y, a[c]);
      c++;
    }
    mv(y, i);
  }
  cout << m.size() << endl;
  for (auto [x, y] : m) cout << x << " " << y << endl;
}
