#include <cmath>
#include <cassert>
#include <functional>
using namespace std;

const int inf = 1e18;

template <int N>
struct ST {
  static constexpr int K = log2(N);
  function<int(int, int)> f;
	int st[N + 1][K]{};
	//---SPARSE TABLE---
	void build(int a[N]) { // m -> whether to use min(true) or max(false)
		for (int i = 0; i < N; i++) st[i][0] = a[i];
		for (int k = 1; k < K; k++) for (int i = 0; i < N; i++) {
			st[i][k] = st[i][k - 1];
			if (int j = i + (1 << k - 1); j < N) st[i][k] = f(st[i][k], st[j][k - 1]);
		}
	}
	int F(int l, int r) { // min on [l, r)
    assert(l < r);
    int k = log2(r - l);
    return f(st[l][k], st[r - (1 << k)][k]);
	}
};
