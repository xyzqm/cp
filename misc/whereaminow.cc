// https://open.kattis.com/problems/whereaminow
#include <iostream>
#include <vector>
using namespace std;

const int N = 1e2 + 2;

int n, m;
char c[N + 2][N + 2], g[2 * N][2 * N];
bool v[2 * N][2 * N];
struct V { 
  int x, y;
  V l() { return {y, -x}; }
  V r() { return {-y, x}; }
  bool operator==(const V o) const { return x == o.x && y == o.y; }
  V operator+(V o) const { return {x + o.x, y + o.y}; }
  V operator-(V o) const { return {x - o.x, y - o.y}; }
  V transform(V a, V b) const { return {a.x * x + a.y * y, b.x * x + b.y * y }; }
  friend ostream& operator<<(ostream &os, V v) { return os << v.x << " " << v.y << endl; }
};

V d = {1, 0};
vector<V> tr[2 * N][2 * N];
int ds = 0, ops = 0;
int input() { int x; cin >> x; return ++ops, ds = x; }
int rtl() {
  cout << "left" << endl;
  d = d.l();
  return input();
}
int rtr() {
  cout << "right" << endl;
  d = d.r();
  return input();
}
int step() {
  cout << "step" << endl;
  return input();
}
int face(V x) {
  if (x == d) return ds;
  else if (x == d.l()) return rtl();
  else if (x == d.r()) return rtr();
  else return rtr(), rtr();
}

template <typename T, int N>
T& at(T a[N][N], V p) { return a[p.x][p.y]; }

void dfs(V r) {
  int i = 0;
  at(g, r) = '.';
  at(v, r) = true;
  for (V v = d; i < 4; v = v.r(), i++) {
    if (face(v) && !at(::v, r + v)) {
      step();
      dfs(r + v);
      face(v.r().r());
      step();
    } else if (!ds) at(g, r + v) = '#';
  }
}

bool test(int x, int y, V a, V b) { // (x, y) correspond to (N, N), a and b are basis vectors
  for (int i = 0; i < 2 * N; i++) {
    for (int j = 0; j < 2 * N; j++) if (g[i][j] != 'x') {
      V c = (V{i, j} - V{N, N}).transform(a, b);
      V d = V{x, y} + c;
      if (min(d.x, d.y) < 0 || d.x > n + 1 || d.y > m + 1 || at(::c, d) != g[i][j]) return false;
    }
  }
  for (int i = 0; i < 2 * N; i++) {
    for (int j = 0; j < 2 * N; j++) if (g[i][j] != 'x') {
      V c = (V{i, j} - V{N, N}).transform(a, b);
      V d = V{x, y} + c;
      if (!tr[i][j].size() || !(d == tr[i][j].back())) tr[i][j].push_back(d);
    }
  }
  return true;
}

vector<V> path;
V p;
bool to(V r) {
  at(::v, r) = true;
  if (r == p) return true;
  int i = 0;
  for (V v = {1, 0}; i < 4; v = v.l(), i++) {
    if (!at(::v, r + v) && at(g, r + v) == '.' && to(v + r)) {
      path.push_back(v);
      return true;
    }
  }
  return false;
}

int main() {
  cin >> n >> m;
  for (int i = 0; i < 2 * N; i++) {
    for (int j = 0; j < 2 * N; j++) g[i][j] = 'x';
  }
  for (int i = 1; i <= n; i++) {
    c[i][0] = c[i][m + 1] = '#';
    for (int j = 1; j <= m; j++) cin >> c[i][j];
  }
  for (int j = 0; j <= m + 1; j++) c[0][j] = c[n + 1][j] = '#';
  input();
  dfs({N, N});
  int i = 0;
  for (V v = {1, 0}; i < 4; v = v.l(), i++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) test(i, j, v, v.l());
    }
  }
  p = {N, N};
  for (int i = 0; i < 2 * N; i++) {
    for (int j = 0; j < 2 * N; j++) {
      if (tr[i][j].size() == 1 && g[i][j] == '.') p = {i, j};
    }
  }
  if (at(tr, p).size() != 1) cout << "no" << endl;
  else {
    for (int i = 0; i < 2 * N; i++) {
      for (int j = 0; j < 2 * N; j++) {
        v[i][j] = 0;
      }
    }
    to({N, N});
    while (path.size()) face(path.back()), step(), path.pop_back();
    cout << "yes " << at(tr, p)[0];
  }
}
