// https://codeforces.com/contest/662/submission/330454469
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 1;
const int K = 20;
int v[N], dp1[1 << K][K], dp2[1 << K][K];

int main() {
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < m; j++) if (s[j] == '1') v[j] ^= (1 << i);
    }
    for (int i = 0; i < m; i++) ++dp1[v[i]][0];
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < 1 << n; i++) {
            for (int j = 0; j < n; j++) {
                dp2[i][j] = dp1[i][j] + (j ? dp1[i ^ (1 << k)][j - 1] : 0);
            }
        }
        swap(dp1, dp2);
    }
    int r = n * m;
    for (int i = 0; i < 1 << n; i++) {
        int c = 0;
        for (int j = 0; j < n; j++) c += min(j, n - j) * dp1[i][j];
        r = min(r, c);
    }
    cout << r << endl;
}
