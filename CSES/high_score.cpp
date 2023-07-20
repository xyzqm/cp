#include <iostream>
#include <vector>
#include <tuple>
using namespace std;
using ll = long long;
const int N = 2501;
const ll inf = 1e18;
ll d[N];
int n, m;
int main() {
    cin >> n >> m;
    vector<tuple<int, int, ll>> E;
    for (int i = 0; i < m; i++) {
        int x, y;
        ll z;
        cin >> x >> y >> z;
        E.emplace_back(x, y, -z);
    }
    fill(d, d + N, inf);
    d[1] = 0;
    for (int i = 0; i < n - 1; i++) {
        for (auto [x, y, z] : E) {
            d[y] = min(d[y], d[x] + z);
        }
    }
    for (auto [x, y, z] : E) if (d[x] + z < d[y]) {
        cout << x << " " << d[x] << " " << y << " " << d[y] << " " << z << endl;
        cout << -1 << endl;
        return 0;
    }
    cout << -d[n] << endl;
}