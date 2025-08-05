#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int K = 30;

void ac() {
    cout << 0 << endl;
    int sum; cin >> sum;
    int a = 0; for (int i = 0; i < K; i += 2) a ^= 1 << i;
    cout << a << endl; int q; cin >> q;
    int even = q - sum;
    int x = 0, y = 0;
    for (int i = 0; i < K; i += 2) {
        if (even >> i & 1) x ^= 1 << i;
        else if (even >> (i + 1) & 1);
        else x ^= (1 << i), y ^= (1 << i);
    }
    int odd = sum - x - y;
    for (int i = 1; i < K; i += 2) {
        if (odd >> i & 1) x ^= 1 << i;
        else if (odd >> (i + 1) & 1) x ^= (1 << i), y ^= (1 << i);
    }
    assert(x + y == sum && (a | x) + (a | y) == q);
    cout << "!" << endl;
    int m; cin >> m;
    cout << (m | x) + (m | y) << endl;
}

int32_t main() {
    int t; cin >> t;
    while (t--) ac();
}
