#include "testlib.h"
#include <cassert>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int N = opt<int>(1);
    int t = 1;
    // int t = opt<int>(1); // number of test cases
    cout << t << "\n";

    for (int i = 0; i < N; i++) cout << 'a';
    for (int i = N; i < 100000; i++) cout << 'b';
    for (int i = N; i < 100000; i++) cout << 'b';
    for (int i = 0; i < N; i++) cout << 'a';
    cout << "\n";

    return 0;
}
