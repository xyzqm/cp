#include <bits/stdc++.h>
using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    Node *l = 0, *r = 0;
    int v, y;
    Node(int v) : v(v), y(rng()) {}
};

int main() {

}
