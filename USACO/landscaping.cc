#include <bits/stdc++.h>
#define int int64_t
using namespace std;

int32_t main() {
    int n, x, y, z;
    cin >> n >> x >> y >> z;
    // f(i) = min cost given that we have extra i units of dirt
    // slopes are -pq, off = f(l)
    priority_queue<int> pq;
    int off = 0, l = 0;
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        if (a < b) { // we have to add dirt
            off += (b - a) * x;
            while (b --> a) pq.push(x - i * z);
        } else { // we have to remove dirt
            off -= (a - b) * (i * z);
            l -= a - b;
            while (a --> b) pq.push(-y - i * z);
        }
    }
    while (l++ < 0) {
        off -= pq.top();
        pq.pop();
    }
    cout << off << endl;
}
