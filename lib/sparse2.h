// a sparse sparse table!
#include <bits/stdc++.h>

#ifndef LG
#define LG
constexpr int lg(int x) {
  return 31 - __builtin_clz(x);
}
#endif

template <typename T = int>
struct ST2 {
    function<T(T, T)> f;
    vector<int> I;
    vector<vector<T>> st;
	void build(vector<pair<int, T>> a, decltype(f) f) {
    	if (!a.size()) return;
    	this->f = f;
    	sort(a.begin(), a.end());
        int N = a.size();
		int K = lg(N) + 1;
		st.assign(N, vector<T>(K));
		I.resize(N);
		for (int i = 0; i < N; i++) tie(I[i], st[i][0]) = a[i];
		for (int k = 1; k < K; k++) for (int i = 0; i < N; i++) {
			st[i][k] = st[i][k - 1];
			if (int j = i + (1 << (k - 1)); j < N) st[i][k] = f(st[i][k], st[j][k - 1]);
		}
	}
	T F(int l, int r) { // min on [l, r]
    	if (!I.size()) return 1e18;
    	assert(l <= r);
        l = lower_bound(I.begin(), I.end(), l) - I.begin();
        r = upper_bound(I.begin(), I.end(), r) - I.begin();
        if (l == r) return 1e18;
        int k = lg(r - l);
        // cout << k << ":" << st[l][k] << ":" << st[r - (1 << k)][k] << endl;
        return f(st[l][k], st[r - (1 << k)][k]);
	}
};
