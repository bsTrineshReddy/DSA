// method1: Recursion (techdose)
class Solution {
    int solve(int n)
    {
        if(n<=3)
            return n;
        
        int ans=n;
        for(int i=1;i*i<=n;++i)
           ans = min(ans,1+solve(n-i*i)); 
            
        return ans;
    }
public:
    int numSquares(int n) {
        int ans = solve(n);
        return ans;
    }
};
=====================
//method2: Recursion + Memoization (techdose)
class Solution {
    vector<int> dp;
    
    int solve(int n)
    {
        if(n<=3)
            return n;
        if(dp[n]!=-1)
            return dp[n];
        
        int ans = n;
        for(int i=1;i*i<=n;++i)
           ans = min(ans,1+solve(n-i*i)); 
        
        dp[n] = ans;
        return ans;
    }
public:
    int numSquares(int n) {
        dp.resize(n+1,-1);
        int ans = solve(n);
        return ans;
    }
};
=============
//method3: DP TABULATION (techdose)
class Solution {
public:
    int numSquares(int n) {
        int dp[n+1];
        dp[0] = 0;
        
        for(int i=1;i<=n;++i)
        {
            dp[i] = i;
            for(int j=1;j*j<=i;++j)
            {
                int sq = j*j;
                dp[i] = min(dp[i],1+dp[i-sq]);
            }
        }
        return dp[n];
    }
};
===============
/*
  method4: mathematics (techdose)
  - Lagrange's four-square theorem, also known as Bachet's conjecture:
    "which states that every natural number can be represented as the sum of four integer squares"
  - legendre 3 square theorem: that a positive integer can be expressed as the sum of three squares:
     "if n notequalto 4^k(8m+7)"

*/
class Solution {
public:
    int numSquares(int n) {
        if(ceil(sqrt(n))==floor(sqrt(n)))
            return 1;
        while(n%4==0)   //Remove 4^a term
            n/=4;
        
        // cant be represent as 3sum perfect or 2 sum
        if(n%8==7)      //check if the no now is in the form of (8b + 7)
            return 4;
        
        // if can be represent as  3sum perfect square check for 2 sum
        for(int i=1;i*i<=n;++i)
        {
            int base = sqrt(n-i*i);
            if(base*base==(n-i*i))
                return 2;
        }
        return 3;
    }
}
==================
// method5: brute force (leetcode)
class Solution {
public:
    int numSquares(int n) {
        std::vector<int> squareNums;
        for (int i = 1; i * i <= n; ++i) {
            squareNums.push_back(i * i);
        }

        return minNumSquares(n, squareNums);
    }

private:
    int minNumSquares(int k, const std::vector<int>& squareNums) {
        // Bottom cases: find a square number
        if (std::find(squareNums.begin(), squareNums.end(), k) != squareNums.end()) {
            return 1;
        }

        int minNum = INT_MAX;

        // Find the minimal value among all possible solutions
        for (int square : squareNums) {
            if (k < square) {
                break;
            }
            int newNum = minNumSquares(k - square, squareNums) + 1;
            minNum = std::min(minNum, newNum);
        }

        return minNum;
    }
};
====================
// method6: dp (leetcode)
class Solution {
public:
    int numSquares(int n) {
        std::vector<int> dp(n + 1, INT_MAX);
        // bottom case
        dp[0] = 0;

        // pre-calculate the square numbers.
        int max_square_index = static_cast<int>(sqrt(n)) + 1;
        std::vector<int> square_nums(max_square_index);
        for (int i = 1; i < max_square_index; ++i) {
            square_nums[i] = i * i;
        }

        for (int i = 1; i <= n; ++i) {
            for (int s = 1; s < max_square_index; ++s) {
                if (i < square_nums[s])
                    break;
                dp[i] = std::min(dp[i], dp[i - square_nums[s]] + 1);
            }
        }
        return dp[n];
    }
};
==================
// method7 : greedy (leetcode)
class Solution {
public:
    unordered_set<int> square_nums;

    bool is_divided_by(int n, int count) {
        if (count == 1) {
            return square_nums.count(n) > 0;
        }

        for (int square : square_nums) {
            if (is_divided_by(n - square, count - 1)) {
                return true;
            }
        }
        return false;
    }

    int numSquares(int n) {
        square_nums.clear();

        for (int i = 1; i * i <= n; ++i) {
            square_nums.insert(i * i);
        }

        int count = 1;
        for (; count <= n; ++count) {
            if (is_divided_by(n, count)) {
                return count;
            }
        }
        return count;
    }
};
=====================
// method8 : grredy + bfs (leetcode)
class Solution {
public:
    int numSquares(int n) {
        vector<int> square_nums;
        for (int i = 1; i * i <= n; ++i) {
            square_nums.push_back(i * i);
        }

        unordered_set<int> visited;
        queue<int> q;
        q.push(n);
        visited.insert(n);

        int level = 0;

        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                int remainder = q.front();
                q.pop();

                for (int square : square_nums) {
                    if (remainder == square) {
                        return level + 1;
                    } else if (remainder < square) {
                        break;
                    } else {
                        int next_remainder = remainder - square;
                        if (visited.find(next_remainder) == visited.end()) {
                            q.push(next_remainder);
                            visited.insert(next_remainder);
                        }
                    }
                }
            }
            level += 1;
        }

        return level;
    }
};
=======================

