#include <iostream>
using namespace std;

template <int... ArgsT> struct BIT {
  int v = 0;
  void U(int v) { this->v += v; }
  int Q() { return v; }
};
template <int N, int... Ns> struct BIT<N, Ns...> {
  BIT<Ns...> A[N + 1];
  template <typename... Args> void U(int i, Args... args) {
    for (; i <= N; i += i & -i) A[i].U(args...);
  }
  template <typename... Args> int Q(int l, int r, Args... args) {
    int R = 0;
    for (; r >= 1; r -= r & -r) R += A[r].Q(args...);
    for (--l; l >= 1; l -= l & -l) R -= A[l].Q(args...);
    return R;
  }
};

const int N = 1e3;
int n, q;
BIT<N, N> st;

int main() {
  // s.U(1, 2);
  // cout << s.Q(1, 3) << endl;
  cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      char c; cin >> c;
      st.U(i, j, c == '*');
    }
  }
  while (q--) {
    int t; cin >> t;
    if (t == 1) {
      int y, x; cin >> y >> x;
      st.U(y, x, -2 * st.Q(y, y, x, x) + 1);
    } else {
      int y1, x1, y2, x2; cin >> y1 >> x1 >> y2 >> x2;
      cout << st.Q(y1, y2, x1, x2) << endl;
    }
  }
}
