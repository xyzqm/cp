#include <bits/stdc++.h>
using namespace std;
#define loop(i, l, r) for (int i = l; i < r; i++)
#define pool(i, l, r) for (int i = r; i --> l; )
#define exit() { cout << "NO\n"; return 0; }

const int N = 1e3 + 2;
char a[N][N];
struct T { char x; int dr, dc; };
vector<T> st[N][N];

bool isletter(char c) { return c >= 'A' && c <= 'Z'; }

int n, m;
bool out(int r, int c) { return min(r, c) < 1 || r > n || c > m; }

int main() {
	cin >> n >> m;
	loop(i, 0, n + 2) loop(j, 0, m + 2) cin >> a[i][j];
	queue<pair<int, int>> q;
	loop(i, 1, n + 1) if (isletter(a[i][0])) {
		st[i][0].push_back({a[i][0], 0, 1});
		q.push({i, 0});
	}
	loop(j, 1, m + 1) if (isletter(a[0][j])) {
		st[0][j].push_back({a[0][j], 1, 0});
		q.push({0, j});
	}
	loop(i, 1, n + 1) if (isletter(a[i][m + 1])) {
		st[i][m + 1].push_back({a[i][m + 1], 0, -1});
		q.push({i, m + 1});
	}
	loop(j, 1, m + 1) if (isletter(a[n + 1][j])) {
		st[n + 1][j].push_back({a[n + 1][j], -1, 0});
		q.push({n + 1, j});
	}
	while (q.size()) {
		auto [r, c] = q.front(); q.pop();
		while (st[r][c].size()) {
			auto [x, dr, dc] = st[r][c].back();
			st[r][c].pop_back();
			int cr = r, cc = c;
			while (out(cr, cc) || a[cr][cc] == 'x') {
				cr += dr, cc += dc;
				// cout << x << " " << cr << " " << cc << endl;
				if (out(cr, cc)) exit();
				if (isletter(a[cr][cc]) && a[cr][cc] != x) {
					a[cr][cc] = 'x';
					q.push({cr, cc});
				}
				else if (a[cr][cc] == '.') a[cr][cc] = x;
			}
			st[cr][cc].push_back({x, dr, dc});
		}
	}
	cout << "YES" << endl;
	loop(i, 1, n + 1) {
		loop(j, 1, m + 1) {
			if (a[i][j] == 'x') a[i][j] = '.';
			cout << a[i][j];
		}
		cout << endl;
	}
}
