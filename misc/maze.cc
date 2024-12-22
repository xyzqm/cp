#include <bits/stdc++.h>
using namespace std;

int dr[]{1, -1, 0, 0, 1, 1, -1, -1};
int dc[]{0, 0, 1, -1, 1, -1, 1, -1};

int main() {
	int r, c, n; cin >> r >> c >> n;
	auto valid = [=](int x, int y) { return min(x, y) && x <= r && y <= c; };
	vector<string> a(r + 1);
	vector<vector<int>> vis(r + 1, vector<int>(c + 1, 0));
	deque<tuple<int, int, int, int>> dq;
	int sr, sc, gr, gc; cin >> sr >> sc >> gr >> gc;
	for (int i = 1; i <= r; i++) {
		a[i].resize(c + 1);
		for (int j = 1; j <= c; j++) cin >> a[i][j];
	}
	dq.push_front({sr, sc, 0, 0});
	while (dq.size()) {
		auto [x, y, m, c] = dq[0]; dq.pop_front();
		if (vis[x][y]++) continue;
		if (x == gr && y == gc) {
			cout << c << endl;
			return 0;
		}
		for (int i = 0; i < 4 + 4 * (m > 0); i++) {
			int x_ = x + dr[i];
			int y_ = y + dc[i];
			if (!valid(x_, y_)) continue;
			if (m) dq.push_back({x_, y_, m - 1, c});
			else if (i < 4) {
                if (a[x_][y_] == '.') dq.push_front({x_, y_, 0, c});
                else dq.push_back({x_, y_, n - 1, c + 1});
           	}
		}
	}
}
