#include <bits/stdc++.h>
using namespace std;
#define int int64_t

void ac() {
    int n; cin >> n;
    int r = (n - 1) * (n - 1) + (n % 2) * (n / 2) * (n / 2);
    for (int i = (n + 1) / 2; i < n - 1; i++) r += 2 * i * i;
    cout << r << endl;
    vector<int> p(n + 1);
    p[1] = n / 2 + 1, p[n] = n / 2;
    for (int i = 2; i <= n / 2; i++) p[i] = i - 1;
    for (int i = n / 2 + 1; i < n; i++) p[i] = i + 1;
    for (int i = 1; i <= n; i++) cout << p[i] << " ";
    cout << endl;
    cout << n - 1 << endl;
    for (int i = p[1]; i != n; i = p[i]) cout << i << " " << 1 << endl;
    for (int i = p[n]; i != 1; i = p[i]) cout << i << " " << n << endl;
    cout << 1 << " " << n << endl;
}

int32_t main() {
    int t; cin >> t;
    while (t--) ac();
}
