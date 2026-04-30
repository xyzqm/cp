#ifdef ONLINE_JUDGE
#include "supertrees.h"
#endif
#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

struct dsu : vector<int> {
    dsu(int n) : vector(n, -1) {}
    int rep(int x) { return at(x) < 0 ? x : at(x) = rep(at(x)); }
    int sz(int x) { return -at(rep(x)); }
    bool same(int x, int y) { return rep(x) == rep(y); }
    bool join(int x, int y) {
        x = rep(x), y = rep(y);
        if (x == y) return 0;
        if (at(x) > at(y)) ::swap(x, y);
        at(x) += at(y);
        at(y) = x;
        return 1;
    }
};

int construct(std::vector<std::vector<int>> p) {
	int n = p.size();
	dsu uf1(n), uf2(n);
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
	    if (p[i][j] == 3) return 0;
		if (!p[i][j] && uf1.same(i, j)) return 0;
		if (p[i][j]) uf1.join(i, j);
		if (p[i][j] == 1) uf2.join(i, j);
		if (p[i][j] == 2 && uf2.same(i, j)) return 0;
	}
	#ifndef ONLINE_JUDGE
	for (int i = 0; i < n; i++) {
	    cout << uf1.rep(i) << ":" << uf2.rep(i) << "\n";
	}
	#endif
	auto b = vector(n, vector<int>(n));
	auto cycles = vector(n, set<int>());
	auto link = [&](int u, int v) { if (u != v) b[u][v] = b[v][u] = 1; };
	for (int i = 0; i < n; i++) {
    	link(i, uf2.rep(i));
        cycles[uf1.rep(i)].insert(uf2.rep(i));
	}
	DBG(b);
	DBG(cycles);
	for (int i = 0; i < n; i++) if (cycles[i].size() > 1) {
	    if (cycles[i].size() == 2) return 0;
		for (auto it = cycles[i].begin(); next(it) != cycles[i].end(); ++it) link(*it, *next(it));
		link(*cycles[i].begin(), *cycles[i].rbegin());
	}
	DBG(b);
	#ifdef ONLINE_JUDGE
	build(b);
	#endif
	return 1;
}

#ifndef ONLINE_JUDGE
int main() {
    construct({{1, 0}, {0, 1}});
    construct({{1, 2}, {2, 1}});
    construct({{1, 1}, {1, 1}});
    construct({{1, 2, 2}, {2, 1, 2}, {2, 2, 1}});
}
#endif
