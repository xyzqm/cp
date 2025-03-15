#include "Catherine.h"
#include <bits/stdc++.h>
using namespace std;

namespace {
    int A, B, lst = -1;
    bool amb = true; // whether direction is currently ambiguous
    string signs = "";
    string ord = "010011010011";
}

void Init(int A, int B) {
    ::A = A;
    ::B = B;
}

int Move(vector<int> y) {
    if (A > 2) {
        if (!y[0]) return y[1] ? 1 : 2;
        if (!y[1]) return y[2] ? 2 : 0;
        if (!y[2]) return y[0] ? 0 : 1;
        assert(false); // we should never reach here
    }
    int opt = accumulate(y.begin(), y.end(), 0) + (lst >= 0);
    if (opt > 2) { // at junction
        amb = false;
        if (lst >= 0 && !y[lst]) return -1;
        if (lst >= 0) return lst = !lst;
        else return lst = (y[1] == 1);
    }
    else if (opt == 1) { // at leaf
        amb = false;
        if (lst >= 0) return -1;
        return lst = y[1];
    }
    else if (!amb) { // at deg 2 node, direction known
        return lst = y[1]; // just pick the one edge which is not the one we just traversed
    }
    else { // at deg 2 node, direction still ambiguous
        for (int _ = 0; _ < y[0]; _++) signs.push_back('0');
        for (int _ = 0; _ < y[1]; _++) signs.push_back('1');
        if (signs.size() == 5) { // now we can decide whether we're going in the right direction
            amb = false;
            for (int i = 0; i < 6; i++) if (signs == ord.substr(i, 5)) return -1;
        }
        if (y[0] && y[1]) return lst = 1;
        return lst = (y[1] > 0);
    }
}
