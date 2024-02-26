#include <iostream>
#include <vector>
#include <tuple>
using namespace std;
using ll = long long;
const int N = 2501;
const ll inf = 1e18;
ll d[N];
bool reach[N], cycle[N];
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
            if (d[x] != inf) d[y] = min(d[y], d[x] + z);
        }
    }
    for (auto [x, y, z] : E) if (d[x] != inf) cycle[y] = (d[x] + z < d[y]);
    reach[n] = true;
    for (int i = 0; i < n; i++) {
        for (auto [x, y, z] : E) {
            reach[x] = reach[x] || reach[y];
            if (reach[x] && cycle[x]) {
                cout << "-1\n";
                return 0;
            }
        }
    }
    cout << -d[n] << endl;
}