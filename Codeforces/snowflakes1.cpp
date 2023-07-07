#include <iostream>
#include <cmath>
using namespace std;
using ll = long long;
const int M = 1e6 + 1;
bool works[M];
ll pw(ll a, int b) {
    ll res = 1;
    while (b) {
        if (b % 2) --b, res *= a;
        else a *= a, b /= 2;
    }
    return res;
}
int main() {
    for (int k = 2; k < 1000; k++) {
        int c = k * k, t = 1 + k + k * k;
        while (t < M) {
            works[t] = true;
            t += (c *= k);
        }
    }
    for (int x = 1; x < M; x++) {
        bool w = false;
        for (int n = 3; n < 60; n++) {
            ll k = 2;
            ll mx = ceil(pow(x, 1.0 / (n - 1)));
            for (ll dif = 1e9; dif > 0; dif /= 2) {
                while (k + dif <= mx && (pw(k + dif, n) - 1) / (k + dif - 1) <= x) k += dif;
            }
            // cout << (int) k << " " << n << endl;
            if (k <= mx && (pw(k, n) - 1) / (k - 1) == x) {
                w = true;
                break;
            }
        }
        if (w != works[x]) {cout << x << endl; break; }
    }
}