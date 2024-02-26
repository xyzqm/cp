#include <iostream>
#include <algorithm>
using namespace std;
const int N = 2e5;
int n, a[N];
int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a, a + n);
    for (int i = 0; i < n; i ++) if (i == n - 1 || a[i] + 1 < a[i + 1]) {
        cout << a[i] + 1 << endl;
        break;
    }
}