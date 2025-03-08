#include <bits/stdc++.h>
#define int int64_t
using namespace std;

const int N = 4e2;
const int inf = 1e18;

struct vec { int x, y;
    int cross(vec o) const { return x * o.y - y * o.x; }
    // a < b -> b is ccw of a
    bool operator<(vec o) const {
        if (y < 0 != o.y < 0) return y < 0;
        else return cross(o) > 0;
    }
    vec operator-(vec o) { return {x - o.x, y - o.y}; };
};

vec p[N];
struct T { int i, j;
    vec v() const { return p[j] - p[i]; };
    bool operator<(const T &o) const { return v() < o.v(); }
};

vector<T> g;
int c[N], dp[N];
bool ck(int s, int x) { // s is topmost point
    fill(dp, dp + N, -inf);
    for (auto [i, j] : g) {
        dp[j] = max(dp[j], max(dp[i], -inf * (i != s)) + p[i].cross(p[j]) - 2 * x * c[j]);
    }
    return dp[s] >= 0;
}

int32_t main() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y >> c[i];
        for (int j = 0; j < n; j++) if (i != j) {
            g.push_back({i, j});
        }
    }
    sort(g.begin(), g.end());
    vector<int> o(n);
    iota(o.begin(), o.end(), 0); // random shuffle
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(o.begin(), o.end(), default_random_engine(seed));
    int k = 0;
    for (int x : o) {
        if (!ck(x, k + 1)) continue;
        for (int d = 1 << 30; d > 0; d >>= 1) if (ck(x, k + d)) k += d;
    }
    cout << k << endl;
}
