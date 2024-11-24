#include <bits/stdc++.h>
#include "mint.h"
using namespace std;

const int N = 401;
const int M = 1e9 + 7;
using X = mint;
int n, q, a[N], b[N];
X tot, dp[N], pre[N], p[N], suf[N], s[N], r[N];

X T(int n) { return n * (n + 1) / 2; }

void DP(int x) {
    // dp[i] -> probability a[i] ends up < x
    // pre[i] -> sum of prod of ranges that end at i
    // p[i] -> sum of prod of ranges that end <= i
    // suf[i] -> sum of prod of ranges that begin at i
    // s[i] -> sum of prod of ranges that begin >= i
    cout << x << endl;
    for (int i = 0; i < n; i++) dp[i] = a[i] < x;
    for (int i = 0; i < q; i++) {
        pre[0] = p[0] = dp[0];
        for (int j = 1; j < n; j++) p[j] = p[j - 1] + (pre[j] = (pre[j - 1] + 1) * dp[j]);
        suf[n - 1] = s[n - 1] = dp[n - 1];
        for (int j = n - 1; j --> 0; ) s[j] = s[j + 1] + (suf[j] = (suf[j + 1] + 1) * dp[j]);
        // for (int i = 0; i < n; i++) {
        //     cout << dp[i] << ":" << p[i] << " ";
        // }
        // cout << endl;
        for (int i = 0; i < n; i++) {
            dp[i] = (p[n - 1] - (i ? p[i - 1] : 0) - (i + 1 < n ? s[i + 1] : 0) + dp[i] * (T(i) + T(n - 1 - i))) / tot;
        }
        // cout << endl;
    }
    for (int i = 0; i < n; i++) cout << dp[i] << " ";
    cout << endl;
}

int main() {
    cin >> n >> q;
    tot = T(n); // convenience variable
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        b[i] = a[i];
    }
    sort(b, b + n);
    for (int i = 0; i < n; i++) {
        DP(b[i]);
        for (int j = 0; j < n; j++) r[j] += mint(b[i] - (i ? b[i - 1] : 0)) * (mint{1} - dp[j]);
    }
    for (int i = 0; i < n; i++) cout << r[i] * tot.exp(q) << " ";
    cout << endl;
}
