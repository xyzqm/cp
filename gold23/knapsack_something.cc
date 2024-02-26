#include <iostream>
#include <vector>
#include <queue>
using namespace std;
using ll = long long;
#define int long long
const int N = 2e5;
const ll inf = 1e18;
int n, q, A[N];
vector<ll> ans[N];
ll D[N];
signed main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> A[i];
    using T = pair<ll, int>;
    priority_queue<T, vector<T>, greater<T>> pq;
    fill(D, D + N, inf);
    pq.push({D[0] = 0, 0});
    ans[0] = vector<ll>(n, 0);
    while (pq.size()) {
        auto [d, x] = pq.top();
        pq.pop();
        if (d != D[x]) continue;
        // cout << d << " " << x << endl;
        for (int i = 1; i < n; i++) {
            int y = (x + A[i]) % A[0]; 
            if (d + A[i] < D[(x + A[i]) % A[0]]) {
                ans[y] = ans[x];
                ++ans[y][i];
                pq.push({D[y] = d + A[i], y});
            }
        }
    }
    cin >> q;
    while (q--) {
        int x;
        cin >> x;
        if (D[x % A[0]] <= x) {
            cout << "1\n";
            auto v = ans[x % A[0]];
            v[0] += (x - D[x % A[0]]) / A[0];
            for (int y : v) cout << y << " ";
            cout << endl;
        } else {
            cout << "0\n";
            for (int i = 0; i < n; i++) cout << "0 ";
            cout << endl;
        }
    }
}