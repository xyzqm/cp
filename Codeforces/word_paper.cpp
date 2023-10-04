#include <iostream>
using namespace std;
char g[8][8];
int main() {
    int t;
    cin >> t;
    while (t--) {
        int x = -1, y = -1;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                cin >> g[i][j];
                if (g[i][j] != '.' && x == -1) x = i, y = j;
            }
        }
        for (int i = x; i < 8; i++) {
            if (g[i][y] == '.') break;
            cout << g[i][y];
        }
        cout << endl;
    }
}