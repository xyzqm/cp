#include <cassert>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

const int N = 100;
const double eps = 1e-9;

template <int... D> struct M {
  double v = 0;
  void operator*= (double x) { v *= x; }
  void operator+= (double x) { v += x; }
  void operator+= (M<> x) { v += x.v; }
  void operator= (double x) { v = x; }
  string str() { return to_string(v); }
};
template <int N, int... D> struct M<N, D...> {
  M<D...> a[N];
  void operator*= (double v) {
    for (int i = 0; i < N; i++) a[i] *= v;
  }
  void operator+= (M<N, D...> &b) {
    for (int i = 0; i < N; i++) a[i] += b[i];
  }
  M<D...>& operator[] (int i) { return a[i]; }
  string str() {
    string s = "";
    for (int i = 0; i < N; i++) s += a[i].str() + (sizeof...(D) ? "\n" : " ");
    return s;
  }
  void gauss(int n) {
    for (int i = 1; i <= n; i++) {
      if (abs(a[i][i].v) < eps) {
        int r = i; 
        for (int j = i + 1; j <= n; j++) if (abs(a[j][i].v) > abs(a[r][i].v)) r = j;
        swap(a[i], a[r]);
      }
      a[i] *= 1 / a[i][i].v;
      for (int j = 1; j <= n; j++) if (j != i) {
        auto r = a[i];  
        r *= -a[j][i].v;
        a[j] += r;
      }
    }
  }
};

int n;
struct F { int x; double s; };
vector<F> v[N];

bool ck(double d) {
  M<N, N> m;
  for (int i = 1; i < n; i++) {
    m[i][i].v += 1;
    for (auto [x, s] : v[i]) {
      m[i][x] += -pow(s, d);
    }
    m[i][0] = -m[i][0].v;
  }
  m.gauss(n - 1);
  double r = 0;
  for (int i = 1; i < n; i++) if (m[i][0].v < 0) return true;
  m[0][0] = 1; for (auto [x, s] : v[0]) r += m[x][0].v * pow(s, d);
  return r > 1;
}

int main() {
  double d; cin >> d >> n;
  for (int i = 0; i < n; i++) {
    int k; cin >> k;
    for (int j = 0; j < k; j++) {
      int x; double s; cin >> x >> s;
      v[i].push_back({x, s});
    }
  }
  double x = 0;
  for (double dif = 1000; dif > 1e-5; dif /= 2) {
    while (ck(x + dif)) x += dif;
  }
  cout << fixed << setprecision(7) << x << endl;
}


