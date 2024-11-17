#include <iostream>
using namespace std;
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int x = 1;
        while (n % x == 0) ++x;
        for (int i = 0; i < n; i++) cout << char('a' + (i % x));
        cout << '\n';
    }
}