#include <iostream>
#include <numeric>
#include <algorithm>
using namespace std;
const int N = 1e5 + 1;

struct DSU {
  int p[N], s[N];
  void init(int n) {
    iota(p, p + n + 1, 0);
    fill(s, s + n + 1, 1);
  }
  int fa(int x) {
  	return p[x] == x ? p[x] : (p[x] = fa(p[x]));
  }
  bool unite(int x, int y) {
  	x = fa(x), y = fa(y);
  	if (x == y) return false;
  	if (s[x] < s[y]) swap(x, y);
  	p[y] = x;
  	s[x] += s[y];
  	return true;
  }
}
