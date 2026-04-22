import math
from itertools import pairwise

def compute_worst_case_work(n_max):
    """
    Computes f(n) for all n from 1 to n_max based on the DP observation.

    f(n) >= k^2 + sum(a_i * f(i))
    where a_i in {0, 1}, sum(a_i * i) = n - 1, and k is the number of 1s.
    """
    if n_max < 1:
        return []

    # The maximum possible number of distinct elements k summing to n_max
    # is roughly when 1 + 2 + ... + k <= n_max  => k ~ sqrt(2 * n_max)
    max_k = int(math.sqrt(2 * n_max)) + 2

    # dp[s][k] = max sum of f(i) for subsets of sizes summing to s with exactly k elements
    # Initialize with negative infinity
    INF = float('-inf')
    dp = [[INF] * (max_k + 1) for _ in range(n_max + 1)]

    # Base case: 0 items sum to 0 with value 0
    dp[0][0] = 0

    # Array to store the answers for f(1) through f(n_max)
    f = [0] * (n_max + 1)

    for i in range(1, n_max + 1):
        # 1. Compute f(i) using previously computed values in the DP table
        # We need a subset of sizes summing to (i - 1)
        target_sum = i - 1
        best_val = 1

        for k in range(max_k + 1):
            if dp[target_sum][k] != INF:
                # The total value is k^2 + sum(f(sizes))
                val = k * k + dp[target_sum][k]
                if val > best_val:
                    best_val = val

        f[i] = best_val

        # 2. Update the DP table with the new subtree size `i` and its value `f[i]`
        # We iterate backwards through sums and counts to use each size `i` at most once (0/1 knapsack)
        for s in range(n_max, i - 1, -1):
            for k in range(max_k, 0, -1):
                if dp[s - i][k - 1] != INF:
                    new_val = dp[s - i][k - 1] + f[i]
                    if new_val > dp[s][k]:
                        dp[s][k] = new_val

    return f

# Example usage to verify the author's benchmark mentioned in Image 2
if __name__ == "__main__":
    N = 500
    results = compute_worst_case_work(N)
    print(results)
    diffs = [y - x for x, y in pairwise(results)]
    print(diffs)
    print(f"When n={N}, the worst time f({N}) is: {results[N]}")
    # Output should align with the "~2700 operations" mentioned in the post.
