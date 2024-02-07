// PERMUTATION 1 WITH UNIQUE NUMBERS
/*
 Method1:  recursion (striver)
 Time Complexity:
 Space Complexity:
*/
class Solution {
  private:
    void recurPermute(vector < int > & ds, vector < int > & nums, vector < vector < int >> & ans, int freq[]) {
      if (ds.size() == nums.size()) {
        ans.push_back(ds);
        return;
      }
      for (int i = 0; i < nums.size(); i++) {
        if (!freq[i]) {
          ds.push_back(nums[i]);
          freq[i] = 1;
          recurPermute(ds, nums, ans, freq);
          freq[i] = 0;
          ds.pop_back();
        }
      }
    }
  public:
    vector < vector < int >> permute(vector < int > & nums) {
      vector < vector < int >> ans;
      vector < int > ds;
      int freq[nums.size()];
      for (int i = 0; i < nums.size(); i++) freq[i] = 0;
      recurPermute(ds, nums, ans, freq);
      return ans;
    }
};
===================
/*
 Method1: Backtracking
 Time Complexity:
 Space Complexity:
*/
class Solution {
  private:
    void recurPermute(int index, vector < int > & nums, vector < vector < int >> & ans) {
      if (index == nums.size()) {
        ans.push_back(nums);
        return;
      }
      for (int i = index; i < nums.size(); i++) {
        swap(nums[index], nums[i]);
        recurPermute(index + 1, nums, ans);
        swap(nums[index], nums[i]);
      }
    }
  public:
    vector < vector < int >> permute(vector < int > & nums) {
      vector < vector < int >> ans;
      recurPermute(0, nums, ans);
      return ans;
    }
};
============================================================================
// permutations 2 with duplicates in nums
class Solution {
     void helper(vector<int> nums,int index,vector<vector<int>>&res){
     if(index==nums.size()-1)
     {res.push_back(nums);return;}
        
        for(int i=index;i<nums.size();i++){
          
            if( i==index || nums[i]!=nums[index]){
                    swap(nums[i],nums[index]);  
            helper(nums,index+1,res);
             //swap(nums[i],nums[index]);
            }
      
        }
    
    
    }

public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<vector<int>>res;
        helper(nums,0,res);
        return res;
    }
};
===================
/*
 Method2 : BACTRACKING 1 leetcode
 Time Complexity: O(N!)
 Space Complexity: O(N)
*/
class Solution {
public:
    std::vector<std::vector<int>> permuteUnique(std::vector<int>& nums) {
        std::vector<std::vector<int>> results;

        // Count the occurrence of each number
        std::unordered_map<int, int> counter;
        for (int num : nums) {
            counter[num]++;
        }

        std::vector<int> comb;
        backtrack(comb, nums.size(), counter, results);
        return results;
    }

protected:
    void backtrack(
        std::vector<int>& comb,
        int N,
        std::unordered_map<int, int>& counter,
        std::vector<std::vector<int>>& results) {

        if (comb.size() == N) {
            // Make a deep copy of the resulting permutation,
            // since the permutation would be backtracked later.
            results.push_back(comb);
            return;
        }

        for (auto& entry : counter) {
            int num = entry.first;
            int count = entry.second;
            if (count == 0)
                continue;

            // Add this number into the current combination
            comb.push_back(num);
            counter[num]--;

            // Continue the exploration
            backtrack(comb, N, counter, results);

            // Revert the choice for the next exploration
            comb.pop_back();
            counter[num]++;
        }
    }
};

