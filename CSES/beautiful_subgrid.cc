// https://cses.fi/problemset/task/2137
#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx2") 
#include <iostream>
#include <bitset>
#define N 3000
using namespace std;
using ll = long long;
bitset<N> a[N];
int main() {
    int n;
    cin >> n;
    char c;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> c;
            a[i][j] = (c == '1');
        }
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ll c = (a[i] & a[j]).count();
            ans += c * (c - 1) / 2;
        }
    }
    cout << ans << endl;
}