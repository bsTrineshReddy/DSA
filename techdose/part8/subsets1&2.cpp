// subsets 1

/*
  method1: pick or no pick Backtarcking
  Time: O(n*2^n) space: O(N)
*/
class Solution {
    
    void helper(vector<int>& nums,int n, vector<vector<int>>&res,int index,vector<int>curr){
        
        if(index==n){
           res.push_back(curr);return;}
        helper(nums,n,res,index+1,curr);
        curr.push_back(nums[index]);
        helper(nums,n,res,index+1,curr);
        curr.pop_back();
    }
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n=nums.size();
        vector<vector<int>>res;
        vector<int>curr;
        helper(nums,n,res,0,curr);
        return res;
    }
};
===============
/*
  method2:  Backtarcking seocnd version
  Time: O(n*2^n) space: O(N)
*/
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> subsets;
        vector<int> currentSubset;
        subsetsHelper(subsets, currentSubset, nums, 0);
        return subsets;
    }

private:
    void subsetsHelper(vector<vector<int>>& subsets, vector<int>& currentSubset, vector<int>& nums, int index) {
        // Add the subset formed so far to the subsets list.
        subsets.push_back(currentSubset);

        for (int i = index; i < nums.size(); i++) {
 
            currentSubset.push_back(nums[i]);
            subsetsHelper(subsets, currentSubset, nums, i + 1);
            currentSubset.pop_back();
        }
    }
};
============================
/* 
  method3: cascading iterative
  Time: O(n*2^n) space: O(N)
*/
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        // initialised subsets with one entry i.e empty subset
        vector<vector<int>> subsets = { {} };

        int subsetSize = 0;

        for (int i = 0; i < nums.size(); i++) {
            subsetSize = subsets.size();
            for (int j = 0; j < subsetSize; j++) {
                vector<int> currentSubset = subsets[j];
                currentSubset.push_back(nums[i]);
                subsets.push_back(currentSubset);
            }
        }
        return subsets;
    }
};
==================
/*
 method4: bit mask
 Time: O(n*2^n) space: O(N) 
*/
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> subsets;

        for (int subsetIndex = 0; subsetIndex < pow(2, n); subsetIndex++) {
            // Append subset corresponding to that bitmask.
            vector<int> currentSubset;
      
            for (int j = 0; j < n; j++) {
                // Generate the bitmask
                int mask = 1 << j;
                int isSet = mask & subsetIndex;
                if (isSet != 0) {
                    currentSubset.push_back(nums[j]);

                }
            }
                subsets.push_back(currentSubset);
         
        }

        return subsets;
    }
};
=============================================================================
// subsets 2 with duplicates
/*
  method1: Backtarcking
  Time: O(n*2^n) space: O(N)
*/
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> subsets;
        vector<int> currentSubset;
        sort(nums.begin(), nums.end());
        subsetsWithDupHelper(subsets, currentSubset, nums, 0);
        return subsets;
    }

private:
    void subsetsWithDupHelper(vector<vector<int>>& subsets, vector<int>& currentSubset, vector<int>& nums, int index) {
        // Add the subset formed so far to the subsets list.
        subsets.push_back(currentSubset);

        for (int i = index; i < nums.size(); i++) {
            // If the current element is a duplicate, ignore.
            if (i != index && nums[i] == nums[i - 1]) {
                continue;
            }
            currentSubset.push_back(nums[i]);
            subsetsWithDupHelper(subsets, currentSubset, nums, i + 1);
            currentSubset.pop_back();
        }
    }
};
================
/*
  method2: Cascading iterative (leetcode)
  Time: O(n*2^n) space: O(N)
*/
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> subsets = {{}};

        int subsetSize = 0;

        for (int i = 0; i < nums.size(); i++) {
            int startingIndex = (i >= 1 && nums[i] == nums[i - 1]) ? subsetSize : 0;
            // subsetSize refers to the size of the subset in the previous step. This value also indicates the starting index of the subsets generated in this step.
            subsetSize = subsets.size();
            for (int j = startingIndex; j < subsetSize; j++) {
                vector<int> currentSubset = subsets[j];
                currentSubset.push_back(nums[i]);
                subsets.push_back(currentSubset);
            }
        }
        return subsets;
    }
};
====================
/*
 Method3: pick or not pick brute force with set (striver)
 Time Complexity: O( 2^n *(k log (x) )) {2^n  for generating every subset and k* log( x)  
                               to insert every combination of average length k in a set of size x.}
 Space Complexity: O( 2^n *k)
*/


/*
 generate subsets as you do in in unique nums case and when you insert into final res 2d vector,
 sort the cur vector res and push it into a set<vector<int>> which avoid duplicates
*/
===================
/*
  method4: Bitmask
  Time: O(n*2^n) space: O(N)
*/
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        int n = nums.size();

        // Sort the generated subset. This will help to identify duplicates.
        sort(nums.begin(), nums.end());
        vector<vector<int>> subsets;

        int maxNumberOfSubsets = pow(2, n);
        // To store the previously seen sets.
        unordered_set<string> seen;

        for (int subsetIndex = 0; subsetIndex < maxNumberOfSubsets; subsetIndex++) {
            // Append subset corresponding to that bitmask.
            vector<int> currentSubset;
            string hashcode = "";
            for (int j = 0; j < n; j++) {
                // Generate the bitmask
                int mask = 1 << j;
                int isSet = mask & subsetIndex;
                if (isSet != 0) {
                    currentSubset.push_back(nums[j]);
                    // Generate the hashcode by creating a comma separated string of numbers in the currentSubset.
                    hashcode.append(to_string(nums[j]) + ",");
                }
            }

            if (seen.find(hashcode) == seen.end()) {
                subsets.push_back(currentSubset);
                seen.insert(hashcode);
            }
        }

        return subsets;
    }
};
=====================