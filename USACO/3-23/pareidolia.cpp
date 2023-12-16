#include <iostream>
#include <string>
using namespace std;
using P = pair<int, int>;
const int inf = 1e9;
const string BESSIE = "bessie";
P operator+(P a, P b) { return {a.first + b.first, a.second + b.second}; }
P& upd(P& a, P b) { return a = (b.first > a.first || b.first == a.first && b.second < a.second ? b : a); }
template<typename... Args>
void print(Args... args)
{
    ((cout << args << " "), ...);
    cout << endl;
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    string s; cin >> s;
    s.insert(s.begin(), '\0');   
    int v[s.size()];
    for (int i = 1; i < s.size(); i++) cin >> v[i];
    P dp[s.size()][6];
    for (int i = 0; i < s.size(); i++) 
        for (int j = 0; j < 6; j++) 
            dp[i][j] = {-inf, 0};
    dp[0][5] = {0, 0};
    for (int i = 1; i < s.size(); i++) {
        for (int j = 0; j < 6; j++) {
            upd(
                upd(dp[i][j], dp[i - 1][j] + P{0, (j != 5) * v[i]}),
                s[i] == BESSIE[j] ? 
                    dp[i - 1][(j + 5) % 6] + P{j == 5, 0} :
                    P{-inf, 0}
            );
        }
    }
    P r = {-inf, 0};
    for (int i = 0; i < 6; i++) upd(r, dp[s.size() - 1][i]);
    cout << r.first << endl << r.second << endl;
    return 0;
}