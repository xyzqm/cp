// https://qoj.ac/contest/995/problem/4658
#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t


using st = array<array<int, 3>, 3>; // st[j][k]
st id = {{
    {101, 101, 101},
    {101, 101, 101},
    {101, 101, 101}
}};

st operator+(const st &s, int a) {
    st res = id;
    for (int j = 0; j < 3; j++) for (int k = 0; k < 3; k++) {
        for (int st = 0; st < 3; st++) {
            int rem = a - j - k - st;
            int need = (rem == 1);
            if (rem < 0) need = -rem;
            for (int nj = k; nj <= min((int)2, j + k); nj++) {
                res[nj][st] = min(res[nj][st], s[j][k] + need);
            }
        }
    }
    return res;
}

void ac() {
    int n, k; cin >> n >> k;
    vector<int> l(n), r(n);

    // solve l = r
    array<int, 3> cnt;
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
        ++cnt[min(l[i], (int)2)];
    }
    // k = 1:
    // if there exists an operation 2 that doesn't stretch end to end, we can always place our 1 next to it
    // also, as long as there exists an operation 1, we can simply add to it
    // therefore, the only impossible case is if there is 0 op 2 or 1 op 2
    if (k == 1 && (cnt[0] == n || cnt[1] == n)) {
        cout << 0 << endl;
        return;
    }
    st dp = id;
    dp[0][0] = 0;
    for (int &x : l) dp = dp + x;
    DBG(dp);
    cout << (dp[0][0] <= k) << endl;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
