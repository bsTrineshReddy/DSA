// method1: memorisation
class Solution {
public:
     int mod = 1e9+7;
     int dp[301][301];
    
     int f(int n, int num, int x ) {
            if(n < 0 )return 0; 
            if(n == 0)return 1; 
            if(pow(num , x) > n) return 0;
            if(dp[n][num] != -1) return dp[n][num];
          
            int temp = pow(num , x) ;
            
            int pick = f(n- temp , num + 1 , x);
            int skip = f(n , num + 1 , x);
            
            return dp[n][num] =  (skip % mod + pick % mod) % mod ;
    }
    
    
    int numberOfWays(int n, int x) {
        memset(dp, -1, sizeof(dp));
        return f(n, 1, x);
    }
};
==========
// method2: 2d dp
class Solution {
       int mod = 1e9+7;
// Function to count the number of subsets with a given sum
int findWays(vector<int>& num, int k) {
    int n = num.size();

    // Create a 2D DP table with dimensions n x k+1, initialized with zeros
    vector<vector<int>> dp(n, vector<int>(k + 1, 0));

    // Base case: If the target sum is 0, there is one valid subset (the empty subset)
    for (int i = 0; i < n; i++) {
        dp[i][0] = 1;
    }

    // Initialize the first row based on the first element of the array
    if (num[0] <= k) {
        dp[0][num[0]] = 1;
    }

    // Fill in the DP table using a bottom-up approach
    for (int ind = 1; ind < n; ind++) {
        for (int target = 1; target <= k; target++) {
            // Exclude the current element
            int notTaken = dp[ind - 1][target];

            // Include the current element if it doesn't exceed the target
            int taken = 0;
            if (num[ind] <= target) {
                taken = dp[ind - 1][target - num[ind]];
            }

            // Update the DP table
            dp[ind][target] = (notTaken%mod + taken%mod)%mod;
        }
    }

    // The final result is in the last cell of the DP table
    return dp[n - 1][k];
}

public:
    int numberOfWays(int n, int x) {


     vector<int>v;

     for (int i =1; pow(i,x)<=n; i++) {
         v.push_back(pow(i,x));
     }
     int nn = v.size();
     return findWays(v, n );
     
        
    }
};
===========
/*
method3: tabulation dp
dp[i] mean the ways to present i.
dp[i] = dp[i] + dp[i - v] where v = a ^ x.
time = nlog(n)
*/
int numberOfWays(int n, int x) {
        int dp[301] = {1}, mod = 1e9 + 7, v;
        for (int a = 1; (v = pow(a, x)) <= n; ++a)
            for (int i = n; i >= v; i--)
                dp[i] = (dp[i] + dp[i - v]) % mod;
        return dp[n];
}
==============