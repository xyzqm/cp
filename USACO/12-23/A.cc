#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
#define int long long
const int inf = 1e18;
using P = pair<int, int>;
using T = tuple<int, int, int>;
template<typename... Args>
void print(Args... args)
{
    ((cout << args << " "), ...);
    cout << endl;
}
int n;
const int N = 751;
char c[N][N];
int a[N][N], p[N][N];
bool d[N][N];
int ad(int& a, int b) { return a = (a + b) % 2; }
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n - i; j++) {
            cin >> c[i][j];
            a[i][j] = c[i][j] - '0';
        }
    }
    int R = 0;
    for (int j = 1; j < n; j++) {
        for (int i = n - j; i > 0; i--) {
            for (int k = 1; k < j; k++) ad(p[i][j], d[i][k] * p[i + k][j - k]);
            if (p[i][j] != a[i][j]) {
                ++R, p[i][j] = a[i][j];
                d[i][j] = true;
            }
        }
    }
    cout << R << endl;
    return 0;
}