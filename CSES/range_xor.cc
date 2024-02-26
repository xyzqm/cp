#include <iostream>
using namespace std;
const int N = 2e5 + 1;
int n, q, p[N];
int main() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        p[i] ^= p[i - 1];
    }
    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << (p[b] ^ p[a - 1]) << endl;
    }
}