
// method1 : rec+ memorisation
vector<vector<int>> dp;

int solve(vector<int>& nums, int i, int target){
    if(target == 0) return 0;                          // when target is zero that means we found set of elements that sum up to target   
    if(target < 0 || i >= nums.size()) return -1001;   // if target is less then 0 or i is greater than nums size then its invalid case and just return with very small number     
    if(dp[i][target] != - 1) return dp[i][target];     // if already seen this condition then just return the stored result
    int take = 1 + solve(nums, i+1, target - nums[i]); // when we take, we add 1 to the count and decrease target by nums[i]
    int notTake = solve(nums, i+1, target);            // when not-take, simple move to next element
    return dp[i][target] = max(take, notTake);         // save the max result for future use
}

int lengthOfLongestSubsequence(vector<int>& nums, int target) {
    dp.resize(1001, vector<int>(1001, -1));            // initialise dp with -1
    int ans = solve(nums, 0, target);                  // get the result with starting i = 0
    return (ans > 0)?ans: -1;                          // return -1 if the ans is less than equal to 0, otherwise return ans
}
==================
// method2: 2d dp
int lengthOfLongestSubsequence(vector<int>& nums, int sum) {
        int n=nums.size();
        vector<vector<int>> dp(n+1, vector<int> (sum+1,-1));
        
        for(int i=0;i<n+1;i++) dp[i][0]=0; // longest subsequence when target sum = 0
        
        for(int i=1;i<n+1;i++){
            for(int j=1;j<sum+1;j++){
				// achieving sum = j for elements [0,i]
                dp[i][j] = dp[i-1][j]; 
		
				// if element can contribute to sum
                if(j >= nums[i-1] && dp[i-1][j-nums[i-1]]!=-1) dp[i][j] = max(1+dp[i-1][j-nums[i-1]], dp[i][j]);
            }
        }
        
        return (dp[n][sum]);
}
=====================
// method3: 1d tabulation
class Solution {
public:
    int lengthOfLongestSubsequence(vector<int>& nums, int target){
        vector<int> dp(target+1,0);
        for(int num : nums) 
            for(int t=target;t>=num;t--) 
                if(t-num == 0 || dp[t-num]) 
                    dp[t] = max(dp[t],1+dp[t-num]);
        return dp[target] ? dp[target] : -1;
    }
};
====================
