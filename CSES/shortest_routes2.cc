#include <iostream>
using namespace std;
using ll = long long;
using pil = pair<int, ll>;
const int N = 5e2 + 1;
const ll inf = 1e18;
int n, m, q;
ll dist[N][N];
int main() {
    fill(&dist[0][0], &dist[0][0] + N * N, inf);
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) dist[i][i] = 0;
    for (int i = 0; i < m; i++) {
        int a, b; ll c;
        cin >> a >> b >> c;
        dist[a][b] = min(dist[a][b], c);
        dist[b][a] = min(dist[b][a], c);
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    for (int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;
        if (dist[a][b] == inf) cout << -1 << endl;
        else cout << dist[a][b] << endl;
    }
}