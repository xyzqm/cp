#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
using P = pair<int, int>;
using T = tuple<int, int, int>;
const int N = 5e5;
const int Q = 3;
const int X = 10;
template<typename... Args>
void print(Args... args)
{
    ((cout << args << " "), ...);
}
signed main(int argc, char *argv[]) {
    cin.tie(0)->sync_with_stdio(0);
    srand(stoi(argv[1]));
    print(N);
    cout << endl;
    for (int i = 1; i <= N; i++) print(rand() % X + 1);
    cout << endl;
    for (int i = 1; i <= N; i++) print(i);
    cout << endl;
    return 0;
}