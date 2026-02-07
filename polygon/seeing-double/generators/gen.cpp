#include "testlib.h"
#include <cassert>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int N = opt<int>(1);
    int t = 200000 / N;
    // int t = opt<int>(1); // number of test cases
    cout << t << "\n";

    assert(N > 26);
    // const int MAX_VALUE = opt<int>(3);
    while (t--) {
        vector<int> frq(26);
        for (int i = 0; i < N - 26; i++) {
            int nx = rnd.next(0, 25);
            cout << (char)('a' + nx);
            frq[nx] ^= 1;
        }
        for (int i = 0; i < 26; i++) if (frq[i]) cout << (char)('a' + i);
        cout << "\n";
    }

    return 0;
}
