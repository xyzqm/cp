#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int N = 1e5 + 1;
int c[N][2][2];

using T = array<int, 2>;

T operator+(T a, T b) { return {a[0] + b[0], a[1] + b[1]}; }
void operator+=(T &a, T b) { a[0] += b[0], a[1] += b[1]; }

bool ac() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) for (int side : {0, 1}) for (int dim : {0, 1}) {
        cin >> c[i][dim][side];
        // coord[i][dim][side] *= 2; // to avoid any floating point issues
    }
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    // sort by top edge
    sort(ord.begin(), ord.end(), [&](int i, int j) { return c[i][1][1] > c[j][1][1]; });
    vector<T> com(n); // com * 2 * total mass
    auto cmp = [&](T a, T b) { return a[0] < b[0]; };
    multiset<T, decltype(cmp)> pts(cmp);
    for (int i : ord) {
        decltype(pts.begin()) it;
        while ((it = pts.lower_bound({c[i][0][0], -1})) != pts.end()) {
            if ((*it)[0] > c[i][0][1]) break;
            int j = (*it)[1];
            com[i] += com[j];
            for (int k : {0, 1}) pts.erase({c[j][0][k], j});
        }
        int mass = (c[i][0][1] - c[i][0][0]) * (c[i][1][1] - c[i][1][0]);
        com[i] += {mass * (c[i][0][0] + c[i][0][1]), mass * (c[i][1][0] + c[i][1][1])};
        for (int t : {0, 1}) {
            if (com[i][t] < mass * c[i][t][0] || com[i][t] > mass * c[i][t][1]) return false;
        }
        for (int t : {0, 1}) pts.insert({c[i][0][t], i});
    }
    return true;
}

int32_t main() {
    int t; cin >> t;
    while (t--) cout << (ac() ? "Stable" : "Unstable") << endl;
}
