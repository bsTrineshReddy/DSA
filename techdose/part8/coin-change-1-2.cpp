// coin chnage 1 = minimum coins to pick to  make given sum
/*
 method1: memorisation (striver)
 Time Complexity: O(N*T)
 Space Complexity : O(N*T) + O(N)
*/
int minimumElementsUtil(vector<int>& arr, int ind, int T, vector<vector<int>>& dp){

    // Base case: If we're at the first element
    if(ind == 0){
        // Check if the target sum is divisible by the first element
        if(T % arr[0] == 0)
            return T / arr[0]; // If yes, return the quotient as the answer
        else
            return 1e9; // Otherwise, return a very large value to indicate it's not possible
    }
    
    // If the result for this index and target sum is already calculated, return it
    if(dp[ind][T] != -1)
        return dp[ind][T];
        
    // Calculate the minimum elements needed without taking the current element
    int notTaken = 0 + minimumElementsUtil(arr, ind - 1, T, dp);
    
    // Calculate the minimum elements needed by taking the current element
    int taken = 1e9; // Initialize 'taken' to a very large value
    if(arr[ind] <= T)
        taken = 1 + minimumElementsUtil(arr, ind, T - arr[ind], dp);
        
    // Store the minimum of 'notTaken' and 'taken' in the DP array and return it
    return dp[ind][T] = min(notTaken, taken);
}

int minimumElements(vector<int>& arr, int T){
    
    int n = arr.size();
    
    vector<vector<int>> dp(n, vector<int>(T + 1, -1));
    int ans =  minimumElementsUtil(arr, n - 1, T, dp);
    
    if(ans >= 1e9)
        return -1;
    return ans; 
}
===================
/*
 method2: dp tabulation (striver)
  Time Complexity: O(N*T)
 Space Complexity : O(N*T)
*/
int minimumElements(vector<int>& arr, int T) {
    int n = arr.size();
    
    // Create a 2D DP (Dynamic Programming) table with n rows and T+1 columns
    vector<vector<int>> dp(n, vector<int>(T + 1, 0));
    
    // Initialize the first row of the DP table
    for (int i = 0; i <= T; i++) {
        if (i % arr[0] == 0)
            dp[0][i] = i / arr[0];
        else
            dp[0][i] = 1e9; // Set it to a very large value if not possible
    }
    
    // Fill the DP table using a bottom-up approach
    for (int ind = 1; ind < n; ind++) {
        for (int target = 0; target <= T; target++) {
            // Calculate the minimum elements needed without taking the current element
            int notTake = dp[ind - 1][target];
            
            // Calculate the minimum elements needed by taking the current element
            int take = 1e9; // Initialize 'take' to a very large value
            if (arr[ind] <= target)
                take = 1 + dp[ind][target - arr[ind]];
                
            // Store the minimum of 'notTake' and 'take' in the DP table
            dp[ind][target] = min(notTake, take);
        }
    }
    
    int ans = dp[n - 1][T];
    
    if (ans >= 1e9)
        return -1;
    
    return ans; 
}
=====================
/*
 method3: dp tabulation with space optimisation (striver)
  Time Complexity: O(N*T)
 Space Complexity : O(T)
*/
int minimumElements(vector<int>& arr, int T) {
    int n = arr.size();
    
    vector<int> prev(T + 1, 0);
    vector<int> cur(T + 1, 0);
    
    // Initialize the first row of the DP table
    for (int i = 0; i <= T; i++) {
        if (i % arr[0] == 0)
            prev[i] = i / arr[0];
        else
            prev[i] = 1e9; // Set it to a very large value if not possible
    }
    
    // Fill the DP table using a bottom-up approach
    for (int ind = 1; ind < n; ind++) {
        for (int target = 0; target <= T; target++) {
            // Calculate the minimum elements needed without taking the current element
            int notTake = prev[target];
            
            // Calculate the minimum elements needed by taking the current element
            int take = 1e9; // Initialize 'take' to a very large value
            if (arr[ind] <= target)
                take = 1 + cur[target - arr[ind]];
                
            // Store the minimum of 'notTake' and 'take' in the current DP state
            cur[target] = min(notTake, take);
        }
        // Update the previous DP state with the current state for the next iteration
        prev = cur;
    }
    int ans = prev[T];
    
    if (ans >= 1e9)
        return -1;
    
    return ans; 
}
/*
 Method4:  dp tabulation with loops reversed outerloop = money, inner loop = coins
 Time Complexity:
 Space Complexity:
*/
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n=coins.size();
              
        int dp[amount+ 1]; 
  
       
        dp[0] = 0; 
  
        
        for (int i = 1; i <= amount; i++) 
        dp[i] = INT_MAX; 
  
       
        for (int i = 1; i <= amount; i++) 
        { 
            
            for (int j = 0; j < n; j++) {
                if (coins[j] <= i) 
                { int sub_res=dp[i-coins[j]];
                  if(sub_res!=INT_MAX)
                  dp[i] = min(dp[i],sub_res+1);
                }
            }
        }   
        if(dp[amount]==INT_MAX)
            return -1;

        return dp[amount];
    }
};
========================================================================================
// coin change 2 : no of ways to from the given sum using given coins any number of times
/*
 Method1: Memorisation (striver)
 Time Complexity: O(N*T)
 Space Complexity: O(N*T)
*/

// Function to count the number of ways to make change for a given target sum
long countWaysToMakeChangeUtil(vector<int>& arr, int ind, int T, vector<vector<long>>& dp) {
    // Base case: if we're at the first element
    if (ind == 0) {
        // Check if the target sum is divisible by the first element
        return (T % arr[0] == 0);
    }
    
    // If the result for this index and target sum is already calculated, return it
    if (dp[ind][T] != -1)
        return dp[ind][T];
        
    // Calculate the number of ways without taking the current element
    long notTaken = countWaysToMakeChangeUtil(arr, ind - 1, T, dp);
    
    // Calculate the number of ways by taking the current element
    long taken = 0;
    if (arr[ind] <= T)
        taken = countWaysToMakeChangeUtil(arr, ind, T - arr[ind], dp);
        
    // Store the sum of ways in the DP table and return it
    return dp[ind][T] = notTaken + taken;
}

// Function to count the number of ways to make change for the target sum
long countWaysToMakeChange(vector<int>& arr, int n, int T) {
    vector<vector<long>> dp(n, vector<long>(T + 1, -1)); // Create a DP table
    
    // Call the utility function to calculate the answer
    return countWaysToMakeChangeUtil(arr, n - 1, T, dp);
}
===================
/*
 Method2: dp tabulation (striver)
 Time Complexity: O(N*T)
 Space Complexity: O(N*T)
*/

long countWaysToMakeChange(vector<int>& arr, int n, int T) {
    vector<vector<long>> dp(n, vector<long>(T + 1, 0)); // Create a DP table

    // Initializing base condition
    for (int i = 0; i <= T; i++) {
        if (i % arr[0] == 0)
            dp[0][i] = 1;
        // Else condition is automatically fulfilled,
        // as dp array is initialized to zero
    }

    for (int ind = 1; ind < n; ind++) {
        for (int target = 0; target <= T; target++) {
            long notTaken = dp[ind - 1][target];

            long taken = 0;
            if (arr[ind] <= target)
                taken = dp[ind][target - arr[ind]];

            dp[ind][target] = notTaken + taken;
        }
    }

    return dp[n - 1][T];
}
===================
/*
 Method3: dp tabulation with space optimisation (striver)
 Time Complexity: O(N*T)
 Space Complexity: O(T)
*/
long countWaysToMakeChange(vector<int>& arr, int n, int T) {
    vector<long> prev(T + 1, 0);  // Create a vector to store the previous DP state

    // Initialize base condition
    for (int i = 0; i <= T; i++) {
        if (i % arr[0] == 0)
            prev[i] = 1;  // There is one way to make change for multiples of the first coin
        // Else condition is automatically fulfilled,
        // as the prev vector is initialized to zero
    }

    for (int ind = 1; ind < n; ind++) {
        vector<long> cur(T + 1, 0); 
        for (int target = 0; target <= T; target++) {
            long notTaken = prev[target];  

            long taken = 0;
            if (arr[ind] <= target)
                taken = cur[target - arr[ind]]; 
                
            cur[target] = notTaken + taken;  
        }
        prev = cur; 
    }

    return prev[T]; 
}
============================================================================

