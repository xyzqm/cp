#include <iostream>
#include <numeric>
#include <vector>
#include <tuple>
#include <cmath>
using namespace std;
const int N = 15e4;
const int K = 20;
vector<int> add[N], rem[N];
tuple<int, int, int> q[N];
int n, m, a[N], cnt[17], stl[N][K], str[N][K];
int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        add[--x].push_back(z);
        if (y < n) rem[y].push_back(z);
        q[i] = {x, y, z};
    }
    for (int i = 0; i < n; i++) {
        for (int x : add[i]) ++cnt[x];
        for (int x : rem[i]) --cnt[x];
        a[i] = 1;
        for (int j = 2; j <= 16; j++) if (cnt[j]) a[i] = lcm(a[i], j);
        stl[i][0] = str[i][0] = a[i];
    }
    for (int k = 1; k < K; k++) {
        for (int i = 0; i < n; i++) {
            stl[i][k] = stl[i][k - 1];
            if (int j = i + (1 << (k - 1)); j < n) stl[i][k] = gcd(stl[i][k], stl[j][k - 1]);
            str[i][k] = str[i][k - 1];
            if (int j = i - (1 << (k - 1)); j >= 0) str[i][k] = gcd(str[i][k], str[j][k - 1]);
        }
    }
    for (int i = 0; i < m; i++) {
        auto [x, y, w] = q[i];
        int k = log2(y - x);
        if (gcd(stl[x][k], str[y - 1][k]) != w) {
            cout << "Impossible\n";
            return 0;
        }
    }
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl;
}