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
cd a[N];
bool valid[N][N][N];

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
    ld arg() const { return std::arg((a[j] - a[i]) * cd(rt ? 1 : 1.0i)); }
    bool operator<(Line &o) const { // sort from -pi to pi
        return arg() < o.arg();
    }
};
vector<Line> lines;

ld k = 0;
ld ck(int s, ld k) { // s -> start point
    vector<ld> dp(n);
    for (auto [i, j, rt] : lines) {

    }

}

void ac() {
    cin >> n;
    loop(i, n) loop(j, n) loop(k, n) valid[i][j][k] = 0;
    loop(i, n) {
        ld x, y; cin >> x >> y;
        a[i] = {x, y};
    }
    // computing triangles with no interior points
    vector<int> o(n);
    iota(o.begin(), o.end(), 0);
    loop(i, n) {
        loop(j, n) if (i != j) {
            cd line = a[j] - a[i];
            sort(o.begin(), o.end(), [=](int k1, int k2) { // sort from -pi to pi from line
                cd v1 = (a[k1] - a[j]) / line;
                cd v2 = (a[k2] - a[j]) / line;
                return arg(v1) < arg(v2);
            });
            auto it = o.begin();
            ld alpha = 1e9;
            while (it != o.end() && arg((a[*it] - a[j]) / line) < 0) { // process all points on bottom side
                ld beta = arg(line / (a[*it] - a[i]));
                // cout << beta << endl;
                assert(beta != beta || beta > 0);
                if (beta == beta && beta < alpha) {
                    // cout << i << " " << j << " " << *it << " " << beta << endl;
                    mark(i, j, *it);
                    alpha = beta;
                }
                it++;
            }
            // auto r = o.end();
            // alpha = 1e9;
            // while (r-- != it) { // process all points on top side
            //     ld beta = arg((a[*r] - a[i]) / line);
            //     cout << beta << endl;
            //     assert(beta >= 0);
            //     if (beta && beta < alpha) {
            //         mark(i, j, r - o.begin());
            //         alpha = beta;
            //     }
            // }
        }
    }
    loop(i, n) loop(j, n) if (i != j) {
        lines.push_back({i, j});
        lines.push_back({i, j, 1});
    }
    sort(lines.begin(), lines.end());
    loop(i, n) loop(j, n) loop(k, n)
        if (i < j && j < k && valid[i][j][k])
            cout << i << " " << j << " " << k << endl;
    cout << "-----\n";
}

int main() {
   int t; cin >> t;
   while (t--) ac();
}
