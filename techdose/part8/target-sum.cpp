// method1 : brute (leetcode)
public class Solution {
    int count = 0;
    
    public int findTargetSumWays(int[] nums, int S) {
        calculate(nums, 0, 0, S);
        return count;
    }
    
    public void calculate(int[] nums, int i, int sum, int S) {
        if (i == nums.length) {
            if (sum == S) {
                count++;
            }
        } else {
            calculate(nums, i + 1, sum + nums[i], S);
            calculate(nums, i + 1, sum - nums[i], S);
        }
    }
}
=============
// method2 : rec + memo (leetcode)
class Solution {
public:
    int total;

    int findTargetSumWays(std::vector<int>& nums, int S) {
        total = std::accumulate(nums.begin(), nums.end(), 0);

        std::vector<std::vector<int>> memo(nums.size(), std::vector<int>(2 * total + 1, INT_MIN));
        return calculate(nums, 0, 0, S, memo);
    }

    int calculate(const std::vector<int>& nums, int i, int sum, int S, std::vector<std::vector<int>>& memo) {
        if (i == nums.size()) {
            if (sum == S) {
                return 1;
            } else {
                return 0;
            }
        } else {
            if (memo[i][sum + total] != INT_MIN) {
                return memo[i][sum + total];
            }
            int add = calculate(nums, i + 1, sum + nums[i], S, memo);
            int subtract = calculate(nums, i + 1, sum - nums[i], S, memo);
            memo[i][sum + total] = add + subtract;
            return memo[i][sum + total];
        }
    }
};
=================
// method3: 2d dp (leetcode)
public class Solution {
    public int findTargetSumWays(int[] nums, int S) {
        int total = Arrays.stream(nums).sum();
        int[][] dp = new int[nums.length][2 * total + 1];
        dp[0][nums[0] + total] = 1;
        dp[0][-nums[0] + total] += 1;
        
        for (int i = 1; i < nums.length; i++) {
            for (int sum = -total; sum <= total; sum++) {
                if (dp[i - 1][sum + total] > 0) {
                    dp[i][sum + nums[i] + total] += dp[i - 1][sum + total];
                    dp[i][sum - nums[i] + total] += dp[i - 1][sum + total];
                }
            }
        }
        
        return Math.abs(S) > total ? 0 : dp[nums.length - 1][S + total];
    }
}
==================
// method4: 1d dp (leetcode)
public class Solution {
    public int findTargetSumWays(int[] nums, int S) {
        int total = Arrays.stream(nums).sum();
        int[] dp = new int[2 * total + 1];
        dp[nums[0] + total] = 1;
        dp[-nums[0] + total] += 1;
        
        for (int i = 1; i < nums.length; i++) {
            int[] next = new int[2 * total + 1];
            for (int sum = -total; sum <= total; sum++) {
                if (dp[sum + total] > 0) {
                    next[sum + nums[i] + total] += dp[sum + total];
                    next[sum - nums[i] + total] += dp[sum + total];
                }
            }
            dp = next;
        }
        
        return Math.abs(S) > total ? 0 : dp[S + total];
    }
}
==============
// method5 : subset diff
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {

     int n=nums.size();int sum=0;int i,j;
        for( i=0;i<n;i++)
            sum+=nums[i];
         if(sum < S || (S + sum) % 2 > 0)return   0 ;
       sum=(S+sum)/2;

        vector<int> dp(sum + 1);
        dp[0] = 1;
        for (int n : nums)
            for (int i = sum; i >= n; i--)
                dp[i] += dp[i - n];
        return dp[sum];
    }
};
=================