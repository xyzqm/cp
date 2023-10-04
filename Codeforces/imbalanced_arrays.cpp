#include <iostream>
#include <deque>
#include <vector>
using namespace std;
const int N = 1e5;
int n, a[N];
int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        deque<pair<int, int>> dq;
        for (int i = 0; i < n; i++) {
            dq.emplace_back();
            cin >> dq.back().first;
            dq.back().second = i;
        }
        sort(dq.begin(), dq.end());
        int i = n + 1, c1 = 0, c2 = 0;
        bool pos = true;
        while (--i) {
            if (dq.front().first == c2) {
                a[dq.front().second] = -i;
                ++c1;
                dq.pop_front();
            } else if (dq.back().first == n - c1) {
                a[dq.back().second] = i;
                ++c2;
                dq.pop_back();
            } else break;
        }
        if (dq.size()) cout << "NO\n";
        else {
            cout << "YES\n";
            for (int j = 0; j < n; j++) cout << a[j] << " ";
            cout << "\n";
        }
    }
}