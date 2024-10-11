#include <cmath>
#include <cassert>
#include <functional>
#include <iostream>
using namespace std;

constexpr int lg(int x) {
  return 31 - __builtin_clz(x);
}

template <int N, typename T = int>
struct ST {
  static constexpr int K = lg(N) + 1;
  function<T(T, T)> f;
	T st[N + 1][K]{};
	void build(T a[N]) {
		for (int i = 0; i < N; i++) st[i][0] = a[i];
    /* for (int i = 0; i < N; i++) cout << a[i] << " "; */
		for (int k = 1; k < K; k++) for (int i = 0; i < N; i++) {
			st[i][k] = st[i][k - 1];
			if (int j = i + (1 << (k - 1)); j < N) st[i][k] = f(st[i][k], st[j][k - 1]);
		}
	}
	T F(int l, int r) { // min on [l, r)
    assert(l < r);
    int k = lg(r - l);
    return f(st[l][k], st[r - (1 << k)][k]);
	}
};
