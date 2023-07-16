#include <iostream>
#define int long long
using namespace std;
const int M = 1e9 + 7;
int pw(int a, int b) {
    int res = 1;
    while (b) {
        if (b % 2 == 0) a = a * a % M, b /= 2;
        else res = res * a % M, b--;
    }
    return res;
}
signed main() {
    int n;
    cin >> n;
    cout << pw(2, n) << endl;
}