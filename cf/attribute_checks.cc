#include <bits/stdc++.h>
using namespace std;

const int N = 5e3 + 2;
int dp[N][N], a[N][N][2];
vector<int> c[N][2];

void upd(int &a, int b) { a = max(a, b); }
int ub(vector<int> &v, int x) { return upper_bound(v.begin(), v.end(), x) - v.begin(); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, p = 0; cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        if (x < 0) c[p][0].push_back(-x);
        else if (x > 0) c[p][1].push_back(x);
        else ++p;
    }
    for (int i = 0; i <= m; i++) {
        for (int t : {0, 1}) {
            sort(c[i][t].begin(), c[i][t].end());
            auto it = c[i][t].begin();
            for (int j = 0; j <= m; j++) {
                while (it != c[i][t].end() && j == *it) ++a[i][j][t], it++;
                if (j > 0) a[i][j][t] += a[i][j - 1][t];
            }
        }
    }
    dp[0][0] = 0;
    int r = 0;
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= m - i; j++) {
            int s = a[i + j][i][0] + a[i + j][j][1];
            // add to stat 1
            upd(i + j == m ? r : dp[i + 1][j], dp[i][j] + s);
            // add to stat 2
            upd(i + j == m ? r : dp[i][j + 1], dp[i][j] + s);
        }
    }
    cout << r << endl;
}
