// https://atcoder.jp/contests/arc190/tasks/arc190_c
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

auto vec(int n, int m, int v = 0) { return vector<vector<mint>>(n, vector<mint>(m, v)); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int h, w; cin >> h >> w;
    auto a = vec(h + 1, w + 1);
    auto src = vector(2, vec(h + 2, w + 2));
    src[0][1][1] = src[1][h][w] = 1;
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            int x; cin >> x;
            a[i][j] = x;
            src[0][i + 1][j] += src[0][i][j] * a[i][j];
            src[0][i][j + 1] += src[0][i][j] * a[i][j];
        }
    }
    for (int i = h; i > 0; i--) {
        for (int j = w; j > 0; j--) {
            src[1][i - 1][j] += src[1][i][j] * a[i][j];
            src[1][i][j - 1] += src[1][i][j] * a[i][j];
        }
    }
    mint cur = src[0][h + 1][w];
    auto lz = vector{vec(h + 2, w + 2), vec(h + 2, w + 2)};
    vector<int> dif = vector{1, -1};
    int q, sh, sw; cin >> q >> sh >> sw;
    auto push = [&](int t, int h, int w) {
        if (lz[t][h][w].val()) {
            int d = dif[t];
            lz[t][h + d][w] += lz[t][h][w] * a[h][w];
            lz[t][h][w + d] += lz[t][h][w] * a[h][w];
            src[t][h][w] += lz[t][h][w];
            lz[t][h][w] = 0;
            return true;
        }
        else return false;
    };
    auto row = vector(h + 2, vector{w + 1, -1});
    auto col = vector(w + 2, vector{h + 1, -1});
    auto mark = [&](int t, int h, int w) {
        if (!lz[t][h][w].val()) return;
        int d = dif[t];
        if (d * w <= d * row[h][t]) row[h][t] = w;
        if (d * h <= d * col[w][t]) col[w][t] = h;
    };
    while (q--) {
        char c; int x; cin >> c >> x;
        if (c == 'D') ++sh;
        if (c == 'U') --sh;
        if (c == 'L') --sw;
        if (c == 'R') ++sw;
        for (int t : {0, 1}) while (true) {
            int d = dif[t];
            int h, w;
            if (d * row[sh][t] <= d * sw) {
                tie(h, w) = make_pair(sh, row[sh][t]);
                row[sh][t] += d;
            }
            else if (d * col[sw][t] <= d * sh) {
                tie(h, w) = make_pair(col[sw][t], sw);
                col[sw][t] += d;
            }
            else break;
            if (push(t, h, w)) {
                mark(t, h + d, w);
                mark(t, h, w + d);
            }
        }
        cur += (x - a[sh][sw]) * src[0][sh][sw] * src[1][sh][sw];
        cout << cur.val() << endl;
        for (int t : {0, 1}) {
            int d = dif[t];
            lz[t][sh + d][sw] += (x - a[sh][sw]) * src[t][sh][sw];
            lz[t][sh][sw + d] += (x - a[sh][sw]) * src[t][sh][sw];
            mark(t, sh + d, sw);
            mark(t, sh, sw + d);
        }
        a[sh][sw] = x;
    }
}
