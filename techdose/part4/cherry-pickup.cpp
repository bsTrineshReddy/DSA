// greedy fails sample case is

// method 1:  top down dp (leetcode)
class Solution {
public:
    std::vector<std::vector<std::vector<int>>> memo;
    std::vector<std::vector<int>> grid;
    int N;

    int cherryPickup(std::vector<std::vector<int>>& grid) {
        this->grid = grid;
        N = grid.size();
        memo.resize(N, std::vector<std::vector<int>>(N, std::vector<int>(N, INT_MIN)));
        return std::max(0, dp(0, 0, 0));
    }

    int dp(int r1, int c1, int c2) {
        int r2 = r1 + c1 - c2;
        if (N == r1 || N == r2 || N == c1 || N == c2 ||
            grid[r1][c1] == -1 || grid[r2][c2] == -1) {
            return -999999;
        } else if (r1 == N - 1 && c1 == N - 1) {
            return grid[r1][c1];
        } else if (memo[r1][c1][c2] != INT_MIN) {
            return memo[r1][c1][c2];
        } else {
            int ans = grid[r1][c1];
            if (c1 != c2) {
                ans += grid[r2][c2];
            }
            ans += std::max({dp(r1, c1 + 1, c2 + 1), dp(r1 + 1, c1, c2 + 1),
                             dp(r1, c1 + 1, c2), dp(r1 + 1, c1, c2)});
            memo[r1][c1][c2] = ans;
            return ans;
        }
    }
};
===============
/*
 method2: bottomup (leetcode)
At time t, let dp[c1][c2] be the most cherries that we can pick up for two people
 going from (0, 0) to (r1, c1) and (0, 0) to (r2, c2), where r1 = t-c1, r2 = t-c2. 
 Our dynamic program proceeds similarly to Approach #2.
*/
class Solution {
public:
    int cherryPickup(vector<std::vector<int>>& grid) {
        int N = grid.size();
        vector<vector<int>> dp(N, vector<int>(N, INT_MIN));
        dp[0][0] = grid[0][0];

        for (int t = 1; t <= 2*N - 2; ++t) {
            vector<vector<int>> dp2(N, vector<int>(N, INT_MIN));

            for (int i = max(0, t - (N - 1)); i <= min(N - 1, t); ++i) {
                for (int j = max(0, t - (N - 1)); j <= min(N - 1, t); ++j) {
                    if (grid[i][t - i] == -1 || grid[j][t - j] == -1) {
                        continue;
                    }
                    int val = grid[i][t-i];
                    if (i != j) {
                        val += grid[j][t - j];
                    }
                    for (int pi = i - 1; pi <= i; ++pi) {
                        for (int pj = j - 1; pj <= j; ++pj) {
                            if (pi >= 0 && pj >= 0) {
                                dp2[i][j] = max(dp2[i][j], dp[pi][pj] + val);
                            }
                        }
                    }
                }
            }
            dp = dp2;
        }
        return max(0, dp[N - 1][N - 1]);
    }
};
=====================

