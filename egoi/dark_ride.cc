#include <bits/stdc++.h>
using namespace std;

const int K = 15;

bool same[K], v[K];

int n;

int qry(int msk) { // returns whether a sup msk = b sup msk
    string s(n, '0');
    for (int j = 0; j < n; j++) if ((j & msk) == msk) s[j] = '1';
    cout << "?" << " " << s << endl;
    int x; cin >> x;
    return (x % 2 == 0);
}

int main() {
    cin >> n;
    int dif = -1;
    for (int i = 0; i < K; i++) {
        same[i] = qry(1 << i);
        if (!same[i]) dif = i;
    }
    // use dif bit to check other bits
    for (int i = 0; i < K; i++) if (i != dif) {
        if (same[i]) {
            v[i] = !qry((1 << dif) | (1 << i));
        }
        else {
            v[i] = qry((1 << dif) | (1 << i));
        }
    }
    int a = 0, b = (1 << dif);
    for (int i = 0; i < K; i++) if (i != dif) {
        if (same[i]) a ^= v[i] << i, b ^= v[i] << i;
        else a ^= v[i] << i, b ^= (v[i] ^ 1) << i;
    }
    cout << "! " << a << " " << b << endl;
}
