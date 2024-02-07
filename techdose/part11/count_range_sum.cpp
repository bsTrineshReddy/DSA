// brute force 0(n2)

class Solution {
public:
    int countRangeSum(std::vector<int>& nums, int lower, int upper) {
        int n = nums.size();
        std::vector<long long> sums(n, 0);
        sums[0] = nums[0];
        for (int i = 1; i < n; ++i)
            sums[i] = sums[i-1] + nums[i];
        
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j){
                long long  cur_sum = sums[j] - sums[i] + nums[i];
            
                if (cur_sum >= lower && cur_sum <= upper)
                    ans++;
            }
        }
        
        return ans;
    }
};