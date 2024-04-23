// https://loj.ac/p/108
#include <iostream>
#include <complex>
#include <vector>
using namespace std;
using cd = complex<double>;

const double PI = acos(-1);

// evaluates the polynomial sum(a[i] * x^i) at w^[0...n - 1]
vector<cd> fft(vector<cd> a, cd w) {
  if (a.size() == 1) return a;
  int n = a.size();
  vector<cd> e(n / 2), o(n / 2);
  for (int i = 0; i < a.size(); i++) {
    (i % 2 ? o : e)[i / 2] = a[i];
  }
  vector<cd> E = fft(e, w * w);
  vector<cd> O = fft(o, w * w);
  vector<cd> r(n);
  cd c = 1;
  for (int i = 0; i < r.size(); i++) {
    r[i] = E[i % (n / 2)] + c * O[i % (n / 2)];
    c *= w;
  }
  return r;
}

int main() {
  int n, m; cin >> n >> m;
  ++n, ++m;
  vector<cd> a(n), b(m);
  for (cd& x : a) cin >> x;
  for (cd& x : b) cin >> x;
  int k = 1 << (32 - __builtin_clz(n + m));
  a.resize(k), b.resize(k);
  cd w(cos(2 * PI / k), sin(2 * PI / k));
  vector<cd> A = fft(a, conj(w));
  vector<cd> B = fft(b, conj(w));
  vector<cd> C(A.size());
  for (int i = 0; i < C.size(); i++) C[i] = A[i] * B[i];
  vector<cd> c = fft(C, w);
  for (int i = 0; i < n + m - 1; i++) {
    cout << int(round(real(c[i]) / k)) << " ";
  }
  cout << endl;
}
