#include <bits/stdc++.h>
using namespace std;

#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
const int MX = 5;
#else
const int MX = 100;
#endif
int dp[MX << 1][MX << 1]; // first dimension is what's on the chopping block
array<int, 2> bst[MX << 1][MX << 1];

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    // precompute optimal queries when total set size < MX
    for (int i = 0; i < MX << 1; i++) fill(dp[i], dp[i] + (MX << 1), 100);
    for (int i = 0; i <= 3; i++) for (int j = 0; j <= 3; j++) if (i + j < 3) dp[i][j] = 0;
    for (int s = 3; s < MX; s++) for (int j = 0; j <= s; j++) {
        int i = s - j;
        for (int k = 0; k <= i; k++) for (int h = 0; h <= j; h++) if (k + h) {
            if (int x = max(dp[j - h][k + h], dp[h][i - k + j - h]) + 1; x < dp[i][j]) {
                bst[i][j] = {k, h};
                dp[i][j] = x;
            }
        }
    }
    int n; cin >> n;
    vector<int> a, b(n); // a is on chopping block, b is not
    iota(b.begin(), b.end(), 1);
    while (a.size() + b.size() > 2) {
        cout << "? ";
        int k = a.size() / 2, h = b.size() / 2;
        if (a.size() + b.size() < MX) {
            assert(dp[a.size()][b.size()] != 100);
            tie(k, h) = bst[a.size()][b.size()];
        }
        cout << k + h << " ";
        for (int i = 0; i < k; i++) cout << a[i] << " ";
        for (int i = 0; i < h; i++) cout << b[i] << " ";
        cout << endl;
        string resp; cin >> resp;
        vector<int> na, nb;
        if (resp == "NO") {
            na = vector(b.begin(), b.begin() + h);
            nb = vector(a.begin() + k, a.end());
            nb.insert(nb.end(), b.begin() + h, b.end());
        }
        else {
            na = vector(b.begin() + h, b.end());
            nb = vector(a.begin(), a.begin() + k);
            nb.insert(nb.end(), b.begin(), b.begin() + h);
        }
        a = na, b = nb;
    }
    a.insert(a.end(), b.begin(), b.end());
    for (int x : a) {
        cout << "! " << x << endl;
        string s; if (cin >> s; s == ":)") exit(0);
    }
}
