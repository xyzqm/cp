#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
int main() {
    int t;
    cin >> t;
    while (t--) {
        vector<ll> a, b;
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            int x; cin >> x;
            (i % 2 == 0 ? a : b).push_back(x);
        }
        sort(a.begin(), a.end(), greater<int>());
        ll ansa = a[0];
        for (int i = 1; i < a.size(); i++) {
            if (a[i] <= 0) break;
            ansa += a[i];
        }
        if (!b.size()) {
            cout << ansa << endl;
            continue;
        }
        sort(b.begin(), b.end(), greater<int>());
        ll ansb = b[0];
        for (int i = 1; i < b.size(); i++) {
            if (b[i] <= 0) break;
            ansb += b[i];
        }
        cout << max(ansa, ansb) << endl;
    }
}
