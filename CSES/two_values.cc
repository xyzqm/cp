#include <iostream>
#include <algorithm>
using namespace std;
const int N = 2e5;
int n, x, a[N], ind[N];
int main() {
    cin >> n >> x;
    for (int i = 0; i < n; i++) cin >> a[ind[i] = i];
    sort(ind, ind + n, [](int i, int j) { return a[i] < a[j]; });
    int l = 0, r = n - 1;
    while (l < r) {
        if (a[ind[l]] + a[ind[r]] == x) {
            cout << ind[l] + 1 << " " << ind[r] + 1 << endl;
            return 0;
        } else if (a[ind[l]] + a[ind[r]] < x) ++l;
        else --r;
    }
    cout << "IMPOSSIBLE" << endl;
}