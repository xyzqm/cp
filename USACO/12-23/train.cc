#include <bits/stdc++.h>
using namespace std;
#define all(v) v.begin(), v.end()
#define loop(i, x) for (int i = 0; i < x; i++)
#define int int64_t

const int N = 5e3 + 1;
const int inf = 2e18;

vector<int> t[2];
int n, T, dp[2][N][N];

int32_t main() {
    cin >> n >> T;
    while (n--) {
        char c; int t; cin >> c >> t;
        ::t[c == 'B'].push_back(t);
    }
    sort(all(t[0]));
    sort(all(t[1]));
    loop(t, 2) loop(i, N) fill(dp[t][i], dp[t][i] + N, inf);
}
