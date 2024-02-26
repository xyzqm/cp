#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e4;
// the input is a successor graph that has up to n cycles
// the amount of steps required is the lcm of all cycle lengths
// naive algorithm: fix k and check if it works
// => try to find minimum sum of numbers that have lcm k
// Obs. 1: never optimal to have two numbers w/ gcd > 1 -> one number can be divided by this gcd without changing the answer
// Obs. 2: this means the minimum is achieved by splitting by prime factorization (e.g. 20 -> 4 and 5)
// solution: sum every k that satisfies such a condition
// dp solution: parameterize how many primes can be used
// dp[N][N] -> dp[i][j] = sum of k with the first i primes, max sum of j
// dp[i][j] = sum_k(dp[i - 1][j - p[j] ^ k] * p[j] ^ k) -> each sum term counts the sum of K s.t. p[j] ^ k | K
// note: we choose primes as the first dimension b/c then the dp table depends strictly on the row before it
int n, m, dp[N + 1], composite[N + 1];
vector<int> primes;
signed main() {
	freopen("exercise.in", "r", stdin);
	freopen("exercise.out", "w", stdout);
	for (int i = 2; i <= N; i++) {
		if (composite[i]) continue;
		primes.push_back((i));
		for (int j = i * i; j <= N; j += i) composite[j] = true;
	}
	cin >> n >> m;
	for (int i = 0; i <= n; i++) dp[i] = 1; // we set dp[0][0] to 1 for convenience
	for (int i = 0; i < primes.size(); i++) {
		for (int j = n; j > 0; j--) {
			int p_k = primes[i]; // p ^ k
			while (p_k <= j) {
				dp[j] += dp[j - p_k] * p_k % m, dp[j] %= m;
				p_k *= primes[i];
			}
		}
	}
	cout << dp[n] << endl;
}
