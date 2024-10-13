#include <iostream>
#include <tuple>
#include "mint.h"
using namespace std;
const int N = 1e5 + 1;
const int K = 10;
const int M = 1e9 + 7;

int n, m, l[N], r[N], i = 1, rt;
pair<int, int> a[N][10];
mint x[1 << K];
char t[N];
int f(char t, int l, int r) {
  tie(::t[i], ::l[i], ::r[i]) = make_tuple(t, l, r);
  return i++;
}

string s; int j = 0;
int expr();
int unit() {
  if (s[j] == '(') {
    j++; int k = expr();
    return j++, k;
  }
  else {
    return -(s[j++] - '0');
  }
}
int expr() {
  int l = unit();
  while (j < s.size() && s[j] != ')') {
    char c = s[j++];
    int r = unit();
    l = f(c, l, r);
  }
  return l;
}

pair<mint, mint> ac(int m, int x = rt) {
  if (x < 1) return {!(m >> -x & 1), m >> -x & 1};
  mint a = 0, b = 0;
  auto [l0, l1] = ac(m, l[x]);
  auto [r0, r1] = ac(m, r[x]);
  if (t[x] == '?' || t[x] == '<') {
    a += l0 * r1 + l1 * r0 + l0 * r0;
    b += l1 * r1;
  }
  if (t[x] == '?' || t[x] == '>') {
    a += l0 * r0;
    b += l0 * r1 + l1 * r0 + l1 * r1;
  }
  return {a, b};
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) { 
    cin >> a[j][i].first;
    a[j][i].second = i;
  }
  cin >> s;
  rt = expr();
  for (int i = 0; i < (1 << K); i++) x[i] = ac(i).second;
  mint r = 0;
  for (int i = 0; i < n; i++) {
    sort(a[i], a[i] + m);
    int k = (1 << m) - 1;
    for (int j = 0; j < m; j++) {
      r += x[k] * (a[i][j].first - (j ? a[i][j - 1].first : 0));
      k ^= 1 << a[i][j].second;
    }
  }
  cout << r << endl;
}
