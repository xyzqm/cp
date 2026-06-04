#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

const int K = 20;

void ac() {
    int n; cin >> n;    
    vector<int> a(n);
    for (int &x : a) cin >> x;
    auto pre = [&]() {
        vector<int> mn(n + 1, n + 1), mx(n + 1, 0);
        for (int i = 0; i < n; i++) {
            mn[i + 1] = min(mn[i], a[i]);
            mx[i + 1] = max(mx[i], a[i]);
        }
        mn.push_back(0), mx.push_back(n + 1);
        vector<int> ptr(n + 2, 0); // the prefix that can appear (exclusive) before a given right point
        // for (int i = 1; i <= n; i++) if (a[i - 1] == mn[i] || a[i - 1] == mx[i]) ptr[0] = i;
        for (int i = 1, cmn = n + 1, cmx = 0, i_mn = 0, i_mx = 0; i <= n; i++) {
            if (cmn <= a[n - i] && cmx >= a[n - i]) return make_pair(ptr, i);
            else ptr[i] = n;
            cmn = min(cmn, a[n - i]);   
            cmx = max(cmx, a[n - i]);
            if (a[n - i] == cmn) { // we can add greater values before
                while (mn[i_mn + 1] > cmn) ++i_mn;
                ptr[i] = min(ptr[i], i_mn);
            }
            if (a[n - i] == cmx) { // we can add smaller values before
                while (mx[i_mx + 1] < cmx) ++i_mx;
                ptr[i] = min(ptr[i], i_mx);
            }
            if (i == 1) ptr[i] = max(i_mn, i_mx);
        }
        return make_pair(ptr, n + 1);
        // return ptr;
    };
    auto [mx_a, A] = pre();
    ranges::reverse(a);
    auto [mx_b, B] = pre();
    DBG(mx_a);
    DBG(mx_b);
    DBG(A);
    DBG(B);
    // try a naive dp first
    // int ans = 0;
    // auto dp = vector(n + 2, vector<bool>(n + 2));
    // dp[0][0] = true;
    // for (int i = 0; i < A; i++) {
    //     for (int j = 0; j < B; j++) if (dp[i][j]) {
    //         DBG(make_pair(i, j));
    //         ans = max(ans, i + j);
    //         if (j <= mx_a[i + 1]) dp[i + 1][j] = true;
    //         if (i <= mx_b[j + 1]) dp[i][j + 1] = true;
    //     }
    // }
    // cout << ans << "\n";
    vector<int> dp(A + 1);
    array<vector<int>, K> jmp;
    jmp[0] = mx_b;
    jmp[0].erase(jmp[0].begin()); // offset by 1
    for (int k = 0; k + 1 < K; k++) {
        jmp[k + 1] = jmp[k];
        for (int i = 0; i + (1 << k) < jmp[k].size(); i++) {
            jmp[k + 1][i] = min(jmp[k][i], jmp[k][i + (1 << k)]);
        }
    }
    DBG(jmp[0]);
    int ans = 0;
    for (int i = 0; i < A; i++) { 
        // first, advance B as much as possible
        for (int k = K; k --> 0; ) if (dp[i] + (1 << k) < B) {
            if (i <= jmp[k][dp[i]]) dp[i] += (1 << k);
        }
        ans = max(ans, dp[i] + i); 
        dp[i + 1] = min(dp[i], mx_a[i + 1]);
    }
    DBG(dp);
    cout << ans << "\n";
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}