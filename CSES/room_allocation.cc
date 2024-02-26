#include <iostream>
#include <set>
#include <tuple>
#include <algorithm>
using namespace std;
using ti = tuple<int, int, int>;
const int N = 2e5;
ti c[2 * N];
int ans[N];
int main() {
    int n, x, y;
    cin >> n;
    set<int> r;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        c[2 * i] = {x, -1, i};
        c[2 * i + 1] = {y, 1, i};
        r.insert(i + 1);
    }
    sort(c, c + 2 * n);
    int mx = 0, cur = 0;
    for (int i = 0; i < 2 * n; i++) {
        auto [x, C, I] = c[i];
        if (C == -1) {
            ans[I] = *r.begin();
            mx = max(mx, ans[I]);
            r.erase(r.begin());
        } else r.insert(ans[I]);
    }
    cout << mx << endl;
    for (int i = 0; i < n; i++) cout << ans[i] << " ";
    cout << endl;
}