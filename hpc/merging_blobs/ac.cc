#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int M = 998244353;

int C2(int x) { return x * (x - 1) / 2; }

void ac() {
    int n; cin >> n;
    vector<int> a(n);
    int res = 0;
    for (int &x : a) { cin >> x; res += C2(x); }
    int ways = 1;
    while (--n) ways = ways * n % M;
    cout << C2(accumulate(a.begin(), a.end(), 0LL)) - res << " " << ways << endl;
}

int32_t main() {
    int t; cin >> t;
    while (t--) ac();
}
