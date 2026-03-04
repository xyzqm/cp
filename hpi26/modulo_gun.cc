#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

void ac() {
    int n, m, k; cin >> n >> m >> k;
    vector<int> sms(k);
    int ans = 0;
    for (int i = 0, v; i < n; i++) {
        cin >> v;
        sms[i % k] += v - (m - 1);
    }
    // ans = (n - k) * (m - 1);
    for (int &sm : sms) {
        sm %= m;
        if (sm < 0) sm += m;
    }
    ranges::sort(sms);
    DBG(sms);
    int res = 0;
    for (int i = k, ad = 0, cur = accumulate(sms.begin(), sms.end(), 0LL); i --> 0; ) {
        cur += k * (m - 1 - sms[i] - ad);
        res = max(res, cur);
        ad = m - sms[i], cur += k - m;
    }
    DBG(res);
    cout << res + (n - k) * (m - 1) << "\n";
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
