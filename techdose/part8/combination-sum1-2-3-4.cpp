// combination -1

/*
 Method1:   Backtracking (striver)
 Time Complexity: O(2^t * k)   (t= target sum, k = average len of vector)
 Space Complexity: O(k*x), k is the average length and x is the no. of combinations
*/
class Solution {
  public:
    void findCombination(int ind, int target, vector < int > & arr, vector < vector < int >> & ans, vector < int > & ds) {
      if (ind == arr.size()) {
        if (target == 0) {
          ans.push_back(ds);
        }
        return;
      }
      // pick up the element 
      if (arr[ind] <= target) {
        ds.push_back(arr[ind]);
        findCombination(ind, target - arr[ind], arr, ans, ds);
        ds.pop_back();
      }

      findCombination(ind + 1, target, arr, ans, ds);

    }
  public:
    vector < vector < int >> combinationSum(vector < int > & candidates, int target) {
      vector < vector < int >> ans;
      vector < int > ds;
      findCombination(0, target, candidates, ans, ds);
      return ans;
    }
};
============================================================================

// combination-2
/*
 Method1:  Bactracking(striver)
 Time Complexity:
 Space Complexity:
*/

void findCombination(int ind, int target, vector < int > & arr, vector < vector < int >> & ans, vector < int > & ds) {
  if (target == 0) {
    ans.push_back(ds);
    return;
  }
  for (int i = ind; i < arr.size(); i++) {
    if (i > ind && arr[i] == arr[i - 1]) continue;
    if (arr[i] > target) break;
    ds.push_back(arr[i]);
    findCombination(i + 1, target - arr[i], arr, ans, ds);
    ds.pop_back();
  }
}
vector < vector < int >> combinationSum2(vector < int > & candidates, int target) {
  sort(candidates.begin(), candidates.end());
  vector < vector < int >> ans;
  vector < int > ds;
  findCombination(0, target, candidates, ans, ds);
  return ans;
}
============================================================================
// combination 3
/*
 Method1:  Bactracking (trinesh)
 Time Complexity:
 Space Complexity:
*/
class Solution {
    vector<vector<int>>res;
    void helper(vector<int>curr,int sum,int k,vector<int>visited){
        if(sum==0 && k==0)
        {res.push_back(curr);return;}
        if(k<0 || sum<0)return ;
        
        for(int i=1;i<=9;i++){
            if(visited[i]!=1 && sum>=i && k>=1){
                curr.push_back(i);visited[i]=1;
                helper(curr,sum-i,k-1,visited);
                curr.pop_back();
                
                
            }
        }
        return;
        
    }
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<int>curr;
        vector<int> visited(10,0);
        helper(curr,n,k,visited);
        return res;
    }
};

/*
 Method1:
 Time Complexity:
 Space Complexity:
*/
class Solution {
public:
    void backtrack(int remain, int k,
                    std::vector<int>& comb, int next_start,
                    std::vector<std::vector<int>>& results) {

        if (remain == 0 && comb.size() == k) {
            results.push_back(comb);
            return;
        } else if (remain < 0 || comb.size() == k) {
            return;
        }

        // Iterate through the reduced list of candidates.
        for (int i = next_start; i <= 9; ++i) {
            comb.push_back(i);
            backtrack(remain - i , k, comb, i+1 , results);
            comb.pop_back();
        }
    }

    std::vector<std::vector<int>> combinationSum3(int k, int n) {
        std::vector<std::vector<int>> results;
        std::vector<int> comb;

        this->backtrack(n, k, comb, 1, results);
        return results;
    }
};
============================================================================
// combination 4
/*
 Method1: Top Down Dp :memorisation (leetcode)
 Time Complexity: O(T⋅N)
 Space Complexity: O(n)
*/
class Solution {
private:
    std::unordered_map<int, int> memo;

public:
    int combinationSum4(std::vector<int>& nums, int target) {
        memo.clear();
        return combs(nums, target);
    }

private:
    int combs(const std::vector<int>& nums, int remain) {
        if (remain == 0)
            return 1;
        if (memo.find(remain) != memo.end())
            return memo[remain];

        int result = 0;
        for (int num : nums) {
            if (remain - num >= 0)
                result += combs(nums, remain - num);
            // minor optimization, early stopping
            // else
            //     break;
        }
        memo[remain] = result;
        return result;
    }
};
===================
/*
 Method1: Bottom Up DP : iterative (leetcode)
 Time Complexity:
 Space Complexity:
*/
class Solution {
    public:

    int combinationSum4(vector<int> nums, int target) {
        // minor optimization
        // Arrays.sort(nums);
        vector<int>dp(target+1, 0);
        dp[0] = 1;

        for (int combSum = 1; combSum < target + 1; ++combSum) {
            for (int num : nums) {
                if (combSum - num >= 0)
                    dp[combSum] += dp[combSum - num];
                // minor optimizaton, early stopping
                // else
                //     break;
            }
        }
        return dp[target];
    }
};
============================================================================