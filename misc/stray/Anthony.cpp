#include "Anthony.h"
#include <bits/stdc++.h>
using namespace std;

vector<int> Mark(int N, int M, int A, int B, vector<int> U, vector<int> V) {
    vector<vector<int>> g(N);
    for (int i = 0; i < M; i++) {
        g[U[i]].push_back(i);
        g[V[i]].push_back(i);
    }
    vector<int> a;
    if (A > 2) a = {0, 1, 2};
    else a = {0, 1, 0, 0, 1, 1};
    vector<int> idx(N, -1), X(M, -1);
    queue<int> bfs;
    bfs.push(idx[0] = 0);
    while (bfs.size()) {
        int x = bfs.front();
        bfs.pop();
        for (int y : g[x]) {
            if (X[y] < 0) X[y] = a[idx[x]];
            int z = U[y] ^ V[y] ^ x;
            if (idx[z] < 0) {
                if (g[z].size() > 2 && A == 2) idx[z] = !a[idx[x]];
                else idx[z] = (idx[x] + 1) % a.size();
                bfs.push(z);
            }
        }
    }
    return X;
}
