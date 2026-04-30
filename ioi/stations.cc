#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

std::vector<int> label(int n, int k, std::vector<int> u, std::vector<int> v) {
	std::vector<int> labels(n);
	auto g = vector(n, vector<int>());
	for (auto [u, v] : views::zip(u, v)) {
    	g[u].push_back(v);
    	g[v].push_back(u);
	}
	vector<int> sz(n);
	[&](this auto &&dfs, int x, int p) -> int {
	    for (int y : g[x]) if (y != p) sz[x] += dfs(y, x);
		return ++sz[x];
	}(0, 0);
	[&](this auto &&label, int x, int p, bool mn) -> void {
	    mn = !mn;
		for (int cur = labels[x]; int y : g[x]) if (y != p) {
		    if (!mn) labels[y] = (cur += sz[y]);
    		else labels[y] = (cur -= sz[y]);
			label(y, x, mn);
		}
	}(0, 0, true);
	return labels;
}

int find_next_station(int s, int t, std::vector<int> c) {
    if (s < c[0]) { // s is the minimum
        for (int l = s; int r : c) {
            if (l < t && t <= r) return r;
        }
    }
    else { // s is the maximum
        ranges::reverse(c);
        for (int r = s; int l : c) {
            if (l <= t && t < r) return l;
        }
    }
    return c.back(); // should be parent of s
}

#ifndef ONLINE_JUDGE
int32_t main() {
    auto res = label(5, 10, {0, 1, 1, 2}, {1, 2, 3, 4});
    DBG(res);
}
#endif
