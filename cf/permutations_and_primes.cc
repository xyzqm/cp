#include <iostream>
#include <vector>
using namespace std;
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> a(n);
        a[0] = 2;
        a[n / 2] = 1;
        if (n > 2) a[n - 1] = 3;
        int i = 0;
        for (int x = 4; x <= n; x++) {
            while (a[i]) ++i;
            a[i] = x;
        }
        for (int x : a) cout << x << " ";
        cout << endl;
    }
}