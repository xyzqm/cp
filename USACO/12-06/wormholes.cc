#include <iostream>
#include <vector>
#include <tuple>
using namespace std;
using e = tuple<int, int, int>;
int main() {
    int f;
    cin >> f;
    while (f--) {
        int n, m, w; cin >> n >> m >> w;
        vector<e> edges;
        for (int i = 0; i < m; i++) {
            int a, b, c; cin >> a >> b >> c;
            edges.push_back({a, b, c});
            edges.push_back({b, a, c});
        }
        for (int i = 0; i < w; i++) {
            int a, b, c; cin >> a >> b >> c;
            edges.push_back({a, b, -c});
        }
        vector<int> dist(n + 1);
        for (int i = 0; i < n - 1; i++) {
            for (auto& [a, b, c] : edges) {
                dist[b] = min(dist[b], dist[a] + c);
            }
        }
        bool pos = false;
        for (auto& [a, b, c] : edges) {
            if (dist[a] + c < dist[b]) {
                pos = true;
                break;
            }
        }
        cout << (pos ? "YES" : "NO") << endl;
    }
}