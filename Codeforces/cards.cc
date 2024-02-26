// https://codeforces.com/contest/1278/problem/F
#include <bits/stdc++.h>
using ll = long long;
using namespace std;
const int M = 998244353;
const int K = 5e3;
ll n, m, k, dp[K + 1];
void add(ll& a, ll b) {
    a = (a + b) % M;
}
ll mul(ll a, ll b) {
    return (a * b) % M;
}
ll pw(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b % 2 == 0) a = (a * a) % M, b /= 2;
        else res = (res * a) % M, b--;
    }
    return res;
}

int main() {
    cin >> n >> m >> k;
    dp[0] = 1;
    for (int i = 0; i < k; i++) {
        for (int j = i; j >= 0; j--) {
            add(dp[j + 1], mul(dp[j], n - j));
            dp[j] = mul(dp[j], j);
        }
    }
    ll res = 0;
    for (int i = 0; i <= k; i++) {
        add(res, mul(dp[i], pw(m, k - i)));
    }
    cout << mul(res, pw(pw(m, k), M - 2)) << endl;
}