#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iomanip>
using namespace std;
#define int long long
#define double long double
const int inf = 1e18;
const int T = 1e3 + 1;
const int K = 30;
int t, k;
double P[T]; 
double E(double k, int n) {
    double r = 1;
    for (n <<= 1; n >>= 1; k = k * k) if (n & 1) r *= k;
    return r;
}
double G(double k, int n) {
    return (1 - E(k, n)) / (1 - k);
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> t >> k;
    P[0] = 1;
    for (int i = 1; i < t; i++) P[0] /= 2;
    double S = 0;
    for (int i = 1; i < t; i++) {
        P[i] = P[i - 1] * (t - i) / i;
        S += i * P[i];
    }
    double x = 0, p = P[0];
    int T = 1;
    for (int i = 1; i < t; i++) {
        int y = 0;
        if (x < i) {
            for (int j = k; j > 0; j /= 2) {
                while (T + y + j <= k && x * E(p, y + j) + S * G(p, y + j) < i) {
                    y += j;
                }
            }
            T += ++y, x = x * E(p, y) + S * G(p, y);
            if (T == k + 1) break;
        }
        p += P[i], S -= i * P[i];
    }
    cout << fixed << setprecision(6) << x + 1 << endl;
    return 0;
}