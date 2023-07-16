#include <iostream>
#include <set>
using namespace std;
using ll = long long;
const int N = 2e5 + 1;
int n, a, b;
ll p[N];
int main() {
    auto cmp = [&](int i, int j) {
        if (p[i] != p[j]) return p[i] < p[j];
        else return i < j;
    };
    set<int, decltype(cmp)> s(cmp);
    cin >> n >> a >> b;
    ll ans = -1e18;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        p[i] += p[i - 1];
        if (i - a >= 0) s.insert(i - a);
        if (i - b - 1 >= 0) s.erase(i - b - 1);
        if (s.size()) ans = max(ans, p[i] - p[*s.begin()]);
    }
    cout << ans << endl;
}