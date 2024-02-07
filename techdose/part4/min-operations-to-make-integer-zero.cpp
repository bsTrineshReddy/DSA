/*

/*
 Method1:
 Time Complexity: O(logtarget)
 Space Complexity: O(1)
*/
class Solution {
public:
    int makeTheIntegerZero(int num1, int num2) {
        for (int k = 0; k < 61; ++k) {
            long long target = (long long)num1 - (long long)k*num2;
            bitset<64> bits(target);
            if (target >= 0 && bits.count() <= k && k <= target) {
                return k;
            }
        }
        return -1;
    }
};