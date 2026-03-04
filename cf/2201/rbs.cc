#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

const int M = 998244353;

void ad(int &a, int b) { if ((a += b) >= M) a -= M; }

void ac() {
    int n; cin >> n;
    string s; cin >> s;
    vector<int> ways(n);
    int tot = 0;
    for (int i = 0, p2 = 1, bal = 0, sum_l = 0, sum_r = 0; i < n; i++, p2 = p2 * 2 % M) {
        ways[i] = (1 + sum_l + sum_r) % M;
        if (s[i] == '(') {
            ad(tot, p2);
            ad(sum_l, ways[i]);
        }
        if (s[i] == ')') {
            ad(sum_r, ways[i]);
            ad(tot, ways[i]);
        }
        bal += (s[i] == '(' ? 1 : -1);
        if (bal < 2) sum_l = 0;
    }
    DBG(ways);
    cout << tot << "\n";
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
