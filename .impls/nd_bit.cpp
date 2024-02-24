// https://codeforces.com/blog/entry/64914
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