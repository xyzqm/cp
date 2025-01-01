// https://usaco.org/index.php?page=viewproblem2&cpid=1358
#include <bits/stdc++.h>
#define int int64_t
using namespace std;

const int N = 5e3 + 1;
const int inf = 2e18;

vector<int> a, b;
int n, T, pa[N], pb[N], nb[N], na[N], sa[N], sb[N], dp[2][N][N];

int upd(int &a, int b) { return a = min(a, b); }

// functions to calculate the cost of switching to B/A-train, respectively
int sum(int *p, int l, int r) { return (r ? p[r - 1] : 0) - (l ? p[l - 1] : 0); };
int bcost(int i, int j, int t) { return t * (j - i) - sum(pb, i, j); };
int acost(int i, int j, int t) { return t * (j - i) - sum(pa, i, j); };

int32_t main() {
    cin >> n >> T;
    while (n--) {
        char c; int t;
        cin >> c >> t;
        (c == 'A' ? a : b).push_back(t);
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    // compute prefix sums of times
    partial_sum(a.begin(), a.end(), pa);
    partial_sum(b.begin(), b.end(), pb);
    // compute for each train, the next train afterwards which will have no delay
    for (int i = 0, j = 0; i < a.size(); i++) { // compute for A-trains
        while (j < b.size() && b[j] < a[i] + T) j++;
        nb[i] = j;
        // cout << nb[i] << " ";
    }
    // cout << endl;
    for (int i = 0, j = 0; i < b.size(); i++) { // compute for B-trains
        while (j < a.size() && a[j] < b[i] + T) j++;
        na[i] = j;
        // cout << na[i] << " ";
    }
    // cout << endl;
    for (int i = 0, j = 0; i < a.size(); i++) {
        while (j < a.size() && a[j] < a[i] + 2 * T) j++;
        sa[i] = j;
        // cout << sa[i] << " ";
    }
    // cout << endl;
    for (int i = 0, j = 0; i < b.size(); i++) {
        while (j < b.size() && b[j] < b[i] + 2 * T) j++;
        sb[i] = j;
        // cout << sb[i] << " ";
    }
    // cout << endl;
    // sum of [l, r)
    // DP
    for (int t : {0, 1}) for (int i = 0; i < N; i++) fill(dp[t][i], dp[t][i] + N, inf);
    dp[0][0][0] = dp[1][0][0] = 0;
    for (int i = 0; i <= a.size(); i++) for (int j = 0; j <= b.size(); j++) {
        // cout << dp[0][i][j] << ":" << dp[1][i][j] << " \n"[j == b.size()];
        if (i < a.size()) {
            upd(dp[0][i + 1][j], dp[0][i][j]); // don't switch
            int c = bcost(j, nb[i], a[i] + T);
            // cout << c << " " << j << " " << i << " " << nb[i] << endl;
            upd(dp[1][i + 1][nb[i]], dp[0][i][j] + c);
            // return to A-trains
            c += acost(i + 1, sa[i], a[i] + 2 * T);
            upd(dp[0][sa[i]][nb[i]], dp[0][i][j] + c);
        }
       if (j < b.size()) {
           upd(dp[1][i][j + 1], dp[1][i][j]); // don't switch
           int c = acost(i, na[j], b[j] + T);
           upd(dp[0][na[j]][j + 1], dp[1][i][j] + c);
            c += bcost(j + 1, sb[j], b[j] + 2 * T);
            upd(dp[1][na[j]][sb[j]], dp[1][i][j] + c);
       }
    }
    // win
    cout << min(dp[1][a.size()][b.size()], dp[0][a.size()][b.size()]) << endl;
}
