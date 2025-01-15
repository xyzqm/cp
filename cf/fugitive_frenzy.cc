// https://codeforces.com/problemset/problem/1912/F
#include <bits/stdc++.h>
using namespace std;
using ld = long double;

const int N = 101;
int n, d[N][N];
vector<int> g[N];
ld e[N];

void dfs(int r, int x, int p) {
	d[r][x] = d[r][p] + 1;
	for (int y : g[x]) if (y != p) dfs(r, y, x);
}

vector<int> l;
ld upd(int i) {
	ld c = 0, v = -1; // c * e[i] = v
	for (int j : l) if (j != i) {
		c += ld(1) / e[j];
		v += 1 + ld(d[i][j]) / e[j];
	}
	return e[i] = v / c;

}

int main() {
	cin >> n;
	for (int i = 1; i < n; i++) {
		int u, v; cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (int i = 1; i <= n; i++) {
		e[i] = 1.0, d[i][0] = -1;
		dfs(i, i, 0);
		if (g[i].size() == 1) l.push_back(i);
	}
	int q = 2000; while (q--) for (int i : l) upd(i);
	int s; cin >> s;
	cout << fixed << setprecision(10) << upd(s) << endl;
}
