// https://open.kattis.com/problems/andpermutation
#include <iostream>
#include <map>
using namespace std;
using ll = long long;
const int N = 1e6;
ll a[N], b[N];
int main() {
    int n; cin >> n;
    map<ll, int> ind;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        ind[b[i] = a[i]] = i;
    }
    for (int B = 0; B < 60; B++) {
        for (int i = 0; i < n; i++) {
            if (a[i] & (1LL << B)) {
                int j = ind[b[i] - (1LL << B)];
                swap(b[i], b[j]);
                ind[b[i]] = i, ind[b[j]] = j;
            }
        }
    }
    for (int i = 0; i < n; i++) cout << b[i] << endl;
}