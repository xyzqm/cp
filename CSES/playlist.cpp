#include <iostream>
#include <map>
using namespace std;
const int N = 2e5;
int a[N];
map<int, bool> seen;
int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    int i1 = 0, i2 = 1;
    seen[a[0]] = true;
    int ans = 0;
    while (i1 < n) {
        while (i2 < n && !seen[a[i2]]) seen[a[i2++]] = true;
        ans = max(ans, i2 - i1);
        seen[a[i1++]] = false;
    }
    cout << ans << endl;
}