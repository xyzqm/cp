#include <iostream>
#include <cmath>
#define UPD(a, b) a = min(a, b)
using namespace std;
const int N = 5e5;
const int K = 20;
int n, q, a[N], st[2][N][K];
int main() {
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        st[0][i][0] = st[1][i][0] = a[i];
    }
    for (int k = 1; k < K; ++k) {
        for (int i = 0; i < n; ++i) {
            st[0][i][k] = st[0][i][k - 1];
            if (int j = i + (1 << (k - 1)); j < n) UPD(st[0][i][k], st[0][j][k - 1]);
            st[1][i][k] = st[1][i][k - 1];
            if (int j = i - (1 << (k - 1)); j >= 0) UPD(st[1][i][k], st[1][j][k - 1]);
        }
    }
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        int k = log2(r - l);
        cout << min(st[0][l][k], st[1][r - 1][k]) << endl;
    }
}