#include <iostream>
#include <cmath>
#define UPD(a, b) a = min(a, b)
using namespace std;
const int N = 5e5;
const int K = 20;
int n, q, a[N], stl[N][K], str[N][K];
void build() {
    for (int i = 0; i < n; i++) stl[i][0] = str[i][0] = a[i];
    for (int j = 1; j < K; j++) {
        for (int i = 0; i < n; i++) {
            stl[i][j] = stl[i][j - 1];
            if (int k = i + (1 << (j - 1)); k < n) stl[i][j] = min(stl[i][j], stl[k][j - 1]);
            str[i][j] = str[i][j - 1];
            if (int k = i - (1 << (j - 1)); k >= 0) str[i][j] = min(str[i][j], str[k][j - 1]);
        }
    }
}
int mn(int l, int r) {
    int k = log2(r - l);
    return min(stl[l][k], str[r - 1][k]);
}
int main() {
    cin >> n >> q;
    for (int i = 0; i < n; ++i) cin >> a[i];
    build();
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        cout << mn(l, r) << endl;
    }
}