#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    int n = 100000;
    cout << 5 << " " << 1 << endl;
    for (int i = 0; i < 5; i++) {
        cout << n << endl;
        for (int j = 1; j < 2 * n; j += 2) {
            int l = rnd.next(1, 2 * n - 1);
            int r = rnd.next(l + 1, 2 * n);
            cout << j << " " << l << " " << j + 1 << " " << r << endl;
        }
    }
}
