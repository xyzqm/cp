#include <iostream>
#include <vector>
using namespace std;
int main() {
    int t, n, x, ans;
    cin >> t;
    while (t--) {
        cin >> n;
        ans = 0;
        for (int B = 0; B < 7; B++) {
            vector<int> a, b;
            for (int i = 1; i <= n; i++) {
                if (i & (1 << B)) a.push_back(i);
                else b.push_back(i);
            }
            if (a.size() && b.size()) {
                cout << a.size() << " " << b.size() << " ";
                for (int x : a) cout << x << " ";
                for (int x : b) cout << x << " ";
                cout << endl;
                cin >> x;
                ans = max(ans, x);
            }
        }
        cout << -1 << " " << ans << endl;
    }
}