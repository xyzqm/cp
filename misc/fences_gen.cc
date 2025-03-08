#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    int n = stoi(argv[1]);
    int sz = stoi(argv[2]); // bounds on abs value of side length
    int cost = stoi(argv[3]); // bounds on max cost
    cout << n << endl;
    for (int i = 0; i < n; i++) {
        int x = rnd.next(-sz, sz);
        int y = rnd.next(-sz, sz);
        assert(max(abs(x), abs(y)) <= sz);
        int c = rnd.next(1, cost);
        cout << x << " " << y << " " << c << endl;
    }
}
