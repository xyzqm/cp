#include <bits/stdc++.h>
using namespace std;

int composite[1000000];

void ac() {
    int n; cin >> n;
    int best = 0;
    for (int i = 2; i <= n; i++) if (!composite[i] && abs(i - n / 2) <= abs(best - n / 2)) best = i;
    auto v = ranges::to<vector>(ranges::iota_view(1, n + 1));
    ranges::sort(v, [&](int x, int y) { return abs(x - best) < abs(y - best); });
    for (int &x : v) cout << x << " ";
    cout << endl;
}

int main() {
    for (int i = 2; i < 1e6; i++) if (!composite[i]) {
        for (int j = 2 * i; j < 1e6; j += i) composite[j] = 1;
    }
    int t; cin >> t;
    while (t--) ac();
}
