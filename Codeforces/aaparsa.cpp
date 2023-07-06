// https://codeforces.com/problemset/problem/1528/D
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
template<typename T>
void upd(T& a, T b) { a = min(a, b); }
const ll inf = 1e18;

vector<vector<pair<int, int>>> adj;
int n, m;

vector<ll> sp(int s) {
    vector<ll> dist(n, inf);
    vector<bool> marked(n, false);
    for (auto& [j, c] : adj[s]) dist[j] = c;
    for (int i = 0; i < n; i++) {
        int v = -1;
        for (int j = 0; j < n; j++) {
            if (!marked[j] && (v == -1 || dist[j] < dist[v])) v = j;
        }
        if (dist[v] == inf) break;
        marked[v] = true;
        upd(dist[(v + 1) % n], dist[v] + 1);
        for (auto& [j, c] : adj[v]) {
            upd(dist[(j + dist[v]) % n], dist[v] + c);
        }
    }
    dist[s] = 0;
    return dist;
}

int main() {
    cin >> n >> m;
    adj.resize(n);
    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        adj[a].push_back({b, c});
    }
    for (int i = 0; i < n; i++) {
        for (ll j : sp(i)) cout << j << " ";
        cout << endl;
    }
}