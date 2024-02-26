#include <iostream>
using namespace std;
const int N = 1e5 + 1;
int a[N], b[N];
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            cin >> a[i] >> b[i];
            if (a[i] <= 10 && b[i] > b[ans]) ans = i;
        }
        cout << ans << endl;
    }
}