// https://qoj.ac/contest/1016/problem/4886
#include <bits/stdc++.h>
using namespace std;

// convenience
#define loop(x, n) for (int x = 0; x < n; x++)
using ld = long double;
using cd = complex<ld>;

// globals
const int N = 301;
int n;
ld c[N][N]; // cost to use edge i->j
cd a[N];
bool valid[N][N][N];

// geometry
ld dist(int i, int j) { return abs(a[i] - a[j]); }
ld angle(int i, int j, int k) { // angle formed by IJK
    return arg((a[i] - a[j]) / (a[k] - a[j]));
}
ld area(int i, int j, int k) { // area formed by IJK
    return 0.5 * abs(imag((a[j] - a[i]) * conj(a[k] - a[i])));
}

// utility to mark triangle (a[i], a[j], a[k]) as valid
void mark(int i, int j, int k) {
    array<int, 3> a{i, j, k};
    sort(a.begin(), a.end());
    do {
        auto [i, j, k] = a;
        valid[i][j][k] = true;
    } while (next_permutation(a.begin(), a.end()));
}

// storing lines in ccw order
struct Line {
    int i, j; // from i to j
    bool rt = false; // whether to rotate by 90 degrees
    ld arg() const { return std::arg((a[j] - a[i]) * cd(rt ? 1.0i : 1)); }
    bool operator<(const Line &o) const { // sort from -pi to pi
        return arg() < o.arg();
    }
};
vector<Line> lines;

ld k = 0;
ld ck(int s, ld k) { // s -> start point
    vector<ld> dp(n, -INFINITY);
    dp[s] = 0;
    for (auto [i, j, rt] : lines) {
        if (!rt && (s == i || s == j || valid[s][i][j])) {
            dp[j] = max(dp[j], dp[i] + area(s, i, j) - k * (dist(i, j) + c[i][j]));
        } else if (rt) {
            dp[i] -= k * dist(i, j);
        }
    }
    return dp[s];
}

void ac() {
    cin >> n;
    loop(i, n) loop(j, n) {
        c[i][j] = 0;
        loop(k, n) valid[i][j][k] = 0;
    }
    loop(i, n) {
        ld x, y; cin >> x >> y;
        a[i] = {x, y};
    }
    // computing triangles with no interior points
    vector<int> o(n);
    iota(o.begin(), o.end(), 0);
    loop(j, n) {
        sort(o.begin(), o.end(), [=](int k1, int k2) { // polar sort about point
            return arg(a[k1] - a[j]) < arg(a[k2] - a[j]);
        });
        loop(i, n) if (i != j) {
            cd line = a[j] - a[i];
            auto it = o.begin();
            int t = 0;
            auto nxt = [&]() { ++t; if (++it == o.end()) it = o.begin(); };
            while (t < n && arg((a[*it] - a[j]) / line) < 0) nxt();
            while (t < n && arg((a[*it] - a[j]) / line) >= 0) nxt();
            ld alpha = 1e9;
            t = 0;
            while (t < n && arg((a[*it] - a[j]) / line) < 0) { // process all points on bottom side
                ld beta = arg(line / (a[*it] - a[i]));
                if (beta == beta && beta < alpha) { // beta == beta makes sure beta != nan
                    mark(i, j, *it);
                    alpha = beta;
                }
                nxt();
            }
        }
    }
    lines.clear();
    loop(i, n) loop(j, n) if (i != j) {
        lines.push_back({i, j});
        lines.push_back({i, j, 1});
        loop(k, n) {
            ld alpha = -angle(k, i, j), beta = angle(k, j, i);
            if (min(alpha, beta) < 0 || max(alpha, beta) >= M_PI_2) continue;
            c[i][j] += min(dist(i, k), dist(j, k));
        }
    }
    sort(lines.begin(), lines.end());
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(o.begin(), o.end(), default_random_engine(seed));
    ld x = 0;
    for (int s : o) {
        if (ck(s, x) < 0) continue;
        for (ld d = 1e6; d > 1e-8; d /= 2) if (ck(s, x + d) >= 0) x += d;
    }
    cout << fixed << setprecision(10) << x << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
