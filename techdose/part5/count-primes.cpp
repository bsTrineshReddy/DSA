// method 1: sieve of erthothen9is
class Solution {
public:
    int countPrimes(int n) {
              if (n < 3) return 0;
        int cnt = 0;
        vector<int> prime(n + 1, 0);
        for (int i = 2; i < n; i ++){
            if (prime[i]) continue;
            cnt ++;
            for (int j = i; j <= (n / i); j ++)  prime[i * j] = 1;
        }
        return cnt;
        
    }
};
=================