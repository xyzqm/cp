#include <bits/stdc++.h>
using namespace std;

#define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

int32_t main() {
    int n, l; cin >> n >> l;
    vector<int> p(n);
    for (int & x : p) cin >> x;
    for (int i = 0; i < n; i++) p.push_back(p[i] + l); // for circle stuff
    vector<int> res(n / 2);
    for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) {
        int len = min(p[j] - p[i], p[i + n] - p[j]);
        int cnt = 0;
        for (int a = i + 1, nx = j + 1; a < j && nx < n + i; ) {
            int mn = p[a] + len, mx = p[a + n] - len;
            if (mn <= p[nx] && p[nx] <= mx) ++cnt, ++a, ++nx;
            else if (p[nx] < mn) ++nx;
            else ++a;
        }
        res[cnt] = max(res[cnt], len);
    }
    DBG(res);
    for (int i = n / 2 - 1; i --> 0; ) {
        res[i] = max(res[i], res[i + 1]);
    }
    for (int i = 0; i < n / 2; i++) cout << res[i] << " \n"[i + 1 == n / 2];
}
