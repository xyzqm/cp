// https://codeforces.com/problemset/problem/1949/F
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int N = 2e5 + 1;
const int M = 1e6 + 1;
int n, sz[N], m, c[M];
struct T {
  vector<int> v;
  int i;
};
T a[N];

int main() {
  cin >> n >> m;
  sz[0] = m;
  for (int i = 0; i < n; i++) {
    int k; cin >> k;
    sz[a[i].i = i + 1] = k;
    a[i].v.resize(k);
    for (int j = 0; j < k; j++) cin >> a[i].v[j];
  }
  sort(a, a + n, [](T& a, T& b) { return a.v.size() > b.v.size(); });
  for (int _ = 0; _ < n; _++) {
    auto &[v, i] = a[_];
    for (int y : v) {
      if (c[y] != c[v[0]]) {
        cout << "YES\n" << (sz[c[v[0]]] < sz[c[y]] ? c[v[0]] : c[y]) << " " << i << endl;
        return 0;
      }
    }
    for (int y : v) c[y] = i;
  }
  cout << "NO" << endl;
}
