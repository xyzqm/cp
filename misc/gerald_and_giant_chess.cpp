#include <iostream>
#include <algorithm>
using namespace std;
using ll = long long;
const int MX = 2e5 + 1;
const int M = 1e9 + 7;
const int N = 2e3 + 1;
ll F[MX], F_i[MX], res[N];
pair<int, int> P[N];
int h, w, n;
ll pw(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b % 2) res = res * a % M, --b;
        else a = a * a % M, b /= 2;
    }
    return res;
}
ll C(ll n, ll k) {
    return F[n + k] * F_i[n] % M * F_i[k] % M;
}
int main() {
    // preprocessing
    F[0] = F_i[0] = 1;
    for (int i = 1; i < MX; i++) {
        F[i] = F[i - 1] * i % M;
        F_i[i] = F_i[i - 1] * pw(i, M - 2) % M;
        // if (i < 10) cout << F[i] << " " << F_i[1] << endl;
    }
    // end preprocessing
    cin >> h >> w >> n;
    for (int i = 0; i < n; i++) cin >> P[i].first >> P[i].second;
    P[n] = {1, 1};
    sort(P, P + n + 1);
    for (int i = n; i >= 0; i--) {
        res[i] += C(h - P[i].first, w - P[i].second);
        for (int j = i + 1; j <= n; j++) {
            if (P[j].first < P[i].first || P[j].second < P[i].second) continue;
            res[i] -= C(P[j].first - P[i].first, P[j].second - P[i].second) * res[j] % M;
            res[i] %= M;
            if (res[i] < 0) res[i] += M;
        }
        // cout << res[i] << " " << P[i].first << " " << P[i].second << endl;
    }
    cout << res[0] << endl;
}