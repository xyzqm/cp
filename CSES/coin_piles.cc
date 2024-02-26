#include <iostream>
using namespace std;
int main() {
    int t;
    cin >> t;
    while (t--) {
        long long a, b;
        cin >> a >> b;
        cout << ((a + b) % 3 == 0 && 2 * a >= b && 2 * b >= a && (2 * a - b) % 3 == 0 && (2 * b - a) % 3 == 0 ? "YES" : "NO") << endl;
    }
}