// https://qoj.ac/contest/1696/problem/8794
#include <bits/stdc++.h>
using namespace std;

const int N = 4000;
int v1, v2;
bitset<N> g[N], tmp[N];

void connect(int u, int v) {
    assert(u != v);
    g[u][v] = g[v][u] = 1;
}

void ac1() {
    int K = v2 - v1 - 3;
    // write list of aux nodes in v1 and v1 + 1
    for (int k = v1 + 2; k < v2; k++) connect(v1, k), connect(v1 + 1, k);
    // connect first bit to v1 + 2
    connect(v1 + 2, v1 + 3);
    // chain all bits
    for (int k = v1 + 3; k < v2 - 1; k++) connect(k, k + 1);
    // connect nodes to bits
    for (int i = 0; i < v1; i++) {
        for (int k = 0; k < K; k++) if (i >> k & 1) connect(i, v1 + 3 + k);
    }
}

void ac2() {
    bitset<N> aux;
    for (int i = 0; i < v1; i++) for (int j = i + 1; j < v1; j++) if (g[i] == g[j]) aux = g[i];
    assert(aux.count() == v1 - v2 - 2);
    int st = -1;
    for (int i = 0; i < v1; i++) if (aux[i]) {
        if (g[i].count() == 3) st = i;
    }
    assert(st >= 0);
    bitset<N> left = aux;
    left[st] = 0;
    vector<int> bits = {st};
    while (left.count()) for (int i = 0; i < v1; i++) if (left[i] && g[bits.back()][i]) {
        left[i] = 0;
        bits.push_back(i);
    }
    bits.erase(bits.begin());
    vector<int> id(v1, 0);
    for (int i = 0; i < v1; i++) if (!aux[i]) {
        for (int k = 0; k < bits.size(); k++) if (g[i][bits[k]]) id[i] += (1 << k);
    }
    for (int i = 0; i < v1; i++) {
        for (int j = 0; j < v1; j++) if (!aux[i] && !aux[j] && g[i][j]) {
            tmp[id[i]][id[j]] = 1;
        }
    }
    swap(g, tmp);
}

int main() {
    cin >> v1 >> v2;
    for (int i = 0; i < v1; i++) {
        string s; cin >> s;
        reverse(s.begin(), s.end());
        g[i] = bitset<N>(s);
    }
    if (v1 < v2) ac1();
    else ac2();
    for (int i = 0; i < v2; i++) {
        string s = g[i].to_string();
        reverse(s.begin(), s.end());
        s.resize(v2);
        cout << s << endl;
    }
}
