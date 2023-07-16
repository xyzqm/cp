#include <iostream>
#include <set>
#include <tuple>
#include <algorithm>
using namespace std;
using ti = tuple<int, int, int>;
const int N = 2e5;
ti c[2 * N];
int main() {
    int n, x, y;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        c[2 * i] = {x, 1, i};
        c[2 * i + 1] = {y, -1, i};
    }
    sort(c, c + 2 * n);
    int mx = 0, cur = 0;
    for (int i = 0; i < 2 * n; i++) {
        cur += get<1>(c[i]);
        mx = max(mx, cur);
    }
    cout << mx << endl;
}