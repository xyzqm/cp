#include <iostream>
#include <algorithm>
#include <set>
#include <queue>
using namespace std;
const int N = 2e5;
int n, d, b[N], e[N], dist[N];
int main() {
    freopen("piepie.in", "r", stdin);
    freopen("piepie.out", "w", stdout);
    cin >> n >> d;
    fill(dist, dist + 2 * n, -1);
    for (int i = 0; i < 2 * n; i++) cin >> b[i] >> e[i];
    auto cmpb = [](int i, int j) { return b[i] > b[j]; };
    multiset<int, decltype(cmpb)> sb(cmpb);
    auto cmpe = [](int i, int j) { return e[i] > e[j]; };
    multiset<int, decltype(cmpe)>  se(cmpe);
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (e[i] > 0) se.insert(i);
        else q.push(i), dist[i] = 1;
    }
    for (int i = n; i < 2 * n; i++) {
        if (b[i] > 0) sb.insert(i);
        else q.push(i), dist[i] = 1;
    }
    while (q.size()) {
        int i = q.front();
        q.pop();
        if (i < n) {
            while (true) {
                auto it = sb.lower_bound(i);
                if (it == sb.end() || b[i] - b[*it] > d) break;
                dist[*it] = dist[i] + 1;
                q.push(*it);
                sb.erase(it);
            }
        } else {
            while (true) {
                auto it = se.lower_bound(i);
                if (it == se.end() || e[i] - e[*it] > d) break;
                dist[*it] = dist[i] + 1;
                q.push(*it);
                se.erase(it);
            }
        }
    }
    for (int i = 0; i < n; i++) cout << dist[i] << endl;
}