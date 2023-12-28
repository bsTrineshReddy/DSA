/*
 reverse an integer without causing overflow
 integer range = -2147483648 to 2147483647  (-2^32 to 2^32 -1)
*/

// method 1:
int reverse(int x) {
        int rev = 0;
        while (x != 0) {
            int pop = x % 10;
            x /= 10;
            if (rev > INT_MAX/10 || (rev == INT_MAX / 10 && pop > 7)) return 0;
            if (rev < INT_MIN/10 || (rev == INT_MIN / 10 && pop < -8)) return 0;
            rev = rev * 10 + pop;
        }
        return rev;
}

// method 2:
int reverse(int x) {
        long int rev=0;
         int n=abs(x);
        while(n>0){
            rev=rev*10+n%10;
            n=n/10;
        }
        if(rev>INT_MAX ||rev<INT_MIN)
            return 0;
         return(x>0?rev:-rev);
        
}