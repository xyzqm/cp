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
    vector<int> v(n);
    vector<int> d;
    for (int lst = 0, i = 0; i < n; i++) {
        cin >> v[i];
        if (lst) d.push_back(abs(v[i] - lst));
        lst = v[i];
    }
    array<vector<int>, K> st;
    st[0] = d;
    DBG(d);
    for (int i = 0; i + 1 < K; i++) {
        st[i + 1] = st[i];
        for (int j = 0; j + (1 << i) < n - 1; j++) {
            st[i + 1][j] = gcd(st[i][j], st[i][j + (1 << i)]);
        }
    }
    int fast = n;
    for (int i = 0; i < n - 1; i++) {
        int j = i;
        for (int k = K, cur = 0; k --> 0; ) {
            if (j < n - 1 && __builtin_popcountll(gcd(st[k][j], cur)) != 1) {
                cur = gcd(st[k][j], cur);
                j += (1 << k); 
            }
        }
        fast += max(n - 1 - j, 0LL);
    }
    // cout << fast << "\n";
    for (int i = 0, cur = -1, run = 0; i < n; i++) {
        if (v[i] != cur) cur = v[i], run = 1;
        else ++run;
        fast += run - 1;
    }
    cout << fast << "\n";
    // int ans = 0;
    // for (int i = 0; i < n; i++) {
    //     for (int j = i, cur = 0; j < n; j++) {
    //         cur = gcd(cur, v[j] - v[i]);
    //         if (!cur || __builtin_popcountll(cur) == 1) ++ans;
    //     }
    // }
    // cout << ans << "\n";
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}