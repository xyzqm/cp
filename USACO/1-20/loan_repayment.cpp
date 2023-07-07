#include <iostream>
using namespace std;
using ll = long long;
ll n, k, m;
bool check(ll x) {
    ll D = 0, g = n, y = n / x;
    while (y > m) {
        ll d = (g - x * y) / y + 1;
        D += d;
        g -= d * y;
        y = g / x;
    }
    D += g / m + (g % m > 0);
    return D <= k;
}
int main() {
    freopen("loan.in", "r", stdin);
    freopen("loan.out", "w", stdout);
    cin >> n >> k >> m;
    ll x = 1;
    for (ll dif = n; dif > 0; dif /= 2) {
        while (check(x + dif)) x += dif;
    }
    cout << x << endl;
}