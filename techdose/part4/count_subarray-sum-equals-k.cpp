/*
 Method1: Brute force
 Time Complexity: O(N3)
 Space Complexity: O(1)
*/
int findAllSubarraysWithGivenSum(vector < int > & arr, int k) {
    int n = arr.size(); // size of the given array.
    int cnt = 0; // Number of subarrays:

    for (int i = 0 ; i < n; i++) { // starting index i
        for (int j = i; j < n; j++) { // ending index j

            // calculate the sum of subarray [i...j]
            int sum = 0;
            for (int K = i; K <= j; K++)
                sum += arr[K];

            // Increase the count if sum == k:
            if (sum == k)
                cnt++;
        }
    }
    return cnt;
}
===================
/*
 Method2: Better approach
 Time Complexity: O(N^2)
 Space Complexity: O(1)
*/
int findAllSubarraysWithGivenSum(vector < int > & arr, int k) {
    int n = arr.size(); // size of the given array.
    int cnt = 0; // Number of subarrays:

    for (int i = 0 ; i < n; i++) { // starting index i
        int sum = 0;
        for (int j = i; j < n; j++) { // ending index j
            // calculate the sum of subarray [i...j]
            // sum of [i..j-1] + arr[j]
            sum += arr[j];

            // Increase the count if sum == k:
            if (sum == k)
                cnt++;
        }
    }
    return cnt;
}
===================
/*
 Method1:  unordered_map + prefix sum
 Time Complexity:
 Space Complexity:
*/
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int count = 0, sum = 0;
        unordered_map<int, int> map;
        // this line takes care of case where current prefix sum == k
        map[0] = 1;
        
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            // [-1,-1,1] k =0 , if we keep this insert in map step here 
            // all cases where k =0 fails 
            // map[sum]++
            if (map.find(sum - k) != map.end())
                count += map[sum - k];
            map[sum]++;
        }
        return count;
    }
};
============================================================================