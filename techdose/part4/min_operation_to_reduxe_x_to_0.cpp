/*
 Method1:  Memoization-->TLE
 Time Complexity:
 Space Complexity:
*/
class Solution {
    unordered_map<string,int> mem;
    int solve(vector<int>& nums,int x,int left,int right,int count)
    {
        if(x==0)    //Sum found
            return count;
        if(x<0 or left>right)   //Out of bounds
            return 1e6;
        string key = to_string(left)+"*"+to_string(right)+"*"+to_string(x); //Form Key
        if(mem.count(key))  //Check if already calculated
            return mem[key];
        
        int l = solve(nums,x-nums[left],left+1,right,count+1);  //Include left element
        int r = solve(nums,x-nums[right],left,right-1,count+1); //Include right element
        return mem[key] = min(l,r);
    }
public:
    int minOperations(vector<int>& nums, int x) {
        int ans = solve(nums,x,0,nums.size()-1,0);
        return ans>=1e6?-1:ans;
    }
};
===================
/*
 Method2: unordered_map (techdose)
 Time Complexity: O(N)
 Space Complexity: 
*/
class Solution {

        int maxSubArrayLen(vector<int>& nums, int k) {
        int prefixSum = 0;
        int longestSubarray = 0;
        unordered_map<int, int> indices;
        for (int i = 0; i < nums.size(); i++) {
            prefixSum += nums[i];

            // Check if all of the numbers seen so far sum to k.
            if (prefixSum == k) {
                longestSubarray = i + 1;
            }
            
            // If any subarray seen so far sums to k, then
            // update the length of the longest_subarray. 
            if (indices.find(prefixSum - k) != indices.end()) {
                longestSubarray = max(longestSubarray, i - indices[prefixSum - k]);
            }

            // Only add the current prefix_sum index pair to the 
            // map if the prefix_sum is not already in the map.
            if (indices.find(prefixSum) == indices.end()) {
                indices[prefixSum] = i;
            }
        }
        
        return longestSubarray;
    }
    
public:
    int minOperations(vector<int>& nums, int x) {
        int n = nums.size();
        int sum = 0;
        unordered_map<int,int> mymap;   //<sum,pos>
        for(int i=0;i<n;++i)
        {
            sum+=nums[i];
        }
        if(x>sum)   //Sum out of range
            return -1;

        sum-=x;
        int longest = maxSubArrayLen(nums, sum);
        return longest==0?(sum==0?n:-1):n-longest;
    }
};
===================
/*
 Method3:  2 pointers indirect
 // basically we modified question to find longest subarray containing all postive integers 
 // whose sum = total -x 
 // this method works only when nums contains all postive integers
 Time Complexity: O(N)
 Space Complexity: O(N)
*/
class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int total = 0;
        for (int num : nums) {
            total += num;
        }
        int n = nums.size();
        int maxi = -1;
        int left = 0;
        int current = 0;

        for (int right = 0; right < n; right++) {
            // sum([left ,..., right]) = total - x
            current += nums[right];
            // if larger, move `left` to left
            while (current > total - x && left <= right) {
                current -= nums[left];
                left += 1;
            }
            // check if equal
            if (current == total - x) {
                maxi = max(maxi, right - left + 1);
            }
        }
        return maxi != -1 ? n - maxi : -1;
    }
};
===================
/*
 Method4: 2pointers direct (leetcode)
 // this method works only beacuse nums contains all postive integers
 Time Complexity: O(N)
 Space Complexity: O(N)
*/
class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int current = 0;
        for (int num : nums) {
            current += num;
        }
        int n = nums.size();
        int mini = INT_MAX;
        int left = 0;

        for (int right = 0; right < n; right++) {
            // sum([0,..,left) + (right,...,n-1]) = x
            current -= nums[right];
            // if smaller, move `left` to left
            while (current < x && left <= right) {
                current += nums[left];
                left += 1;
            }
            // check if equal
            if (current == x) {
                mini = min(mini, (n - 1 - right) + left);
            }
        }
        return mini != INT_MAX ? mini : -1;
    }
};
============================================================================