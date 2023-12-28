// remove k digits in a string to get smallest string
// O(N) solution
class Solution {
  public String removeKdigits(String num, int k) {
    LinkedList<Character> stack = new LinkedList<Character>();
        
    for(char digit : num.toCharArray()) {
      while(stack.size() > 0 && k > 0 && stack.peekLast() > digit) {
        stack.removeLast();
        k -= 1;
      }
      stack.addLast(digit);
    }
        
    /* remove the remaining digits from the tail. */
    for(int i=0; i<k; ++i) {
      stack.removeLast();
    }
        
    // build the final string, while removing the leading zeros.
    StringBuilder ret = new StringBuilder();
    boolean leadingZero = true;
    for(char digit: stack) {
      if(leadingZero && digit == '0') continue;
      leadingZero = false;
      ret.append(digit);
    }
        
    /* return the final string  */

---------------------------------------------------------
//my brute force solution 0(n2)
class Solution {

string removeOneDigit(string num){

    int n =num.length();

    if(n==1)return "0";

    string temp="";
    int j=0,index =-1;

    for(int i=0;i<=n-2;i++){
        cout<<"loop:"<<i<<endl;

        if((num[i] -'0') > (num[i+1]-'0') ){
       
          index = i;
          cout<<"index:"<<index<<"char"<<num[index]<<endl;
          break;  
          cout<<"break;";
        }
    }

    index = index==-1?n-1:index;

    string finalans="";
    
    if(index == 0){
        j=1;
        while(j<n && num[j]=='0')
        {j++;}
        while(j<n){
            finalans+=num[j];j++;
        }
    }
    else{
        j=0;
        while(j<n){ if(j!=index)finalans+=num[j];j++;}
    }

    return finalans;
}
public:
    string removeKdigits(string num, int k) {

        string cur=num;
        while(k>=1){
            if(cur=="")
           { cur="0";
             break;}
            cur = removeOneDigit(cur);
            k--;
        }

        if(cur=="")return "0";

        return cur;
    }
};
---------------------------------------------------------
/*
 asteroid collision
 https://leetcode.com/problems/asteroid-collision/solutions/
*/
    vector<int> asteroidCollision(vector<int>& asteroids) {

                stack<int> st;
        
        for (int asteroid : asteroids) {
            int flag = 1;
            while (!st.empty() && (st.top() > 0 && asteroid < 0)) {
                // If the top asteroid in the stack is smaller, then it will explode.
                // Hence pop it from the stack, also continue with the next asteroid in the stack.
                if (abs(st.top()) < abs(asteroid)) {
                    st.pop();
                    continue;
                }
                // If both asteroids are the same size, then both asteroids will explode.
                // Pop the asteroid from the stack; also, we won't push the current asteroid to the stack.
                else if (abs(st.top()) == abs(asteroid)) {
                    st.pop();
                }

                // If we reach here, the current asteroid will be destroyed
                // Hence, we should not add it to the stack
                flag = 0;
                break;
            }
            
            if (flag) {
                st.push(asteroid);
            }
        }
        
        // Add the asteroids from the stack to the vector in the reverse order.
        vector<int> remainingAsteroids (st.size());
        for (int i = remainingAsteroids.size() - 1; i >= 0; i--){
            remainingAsteroids[i] = st.top();
            st.pop();
        }
        
        return remainingAsteroids;
    }
---------------------------------------------------------
/*
Sum of Subarray Minimums
https://leetcode.com/problems/sum-of-subarray-minimums/description/
*/
// method 1:
int sumSubarrayMins(vector<int>& arr) {
        
        int n = arr.size();
        
        vector<int> left(n,-1), right(n,n);
        // for every i find the Next smaller element to left and right
        
        // Left
        stack<int> st;
        for(int i=0; i<n; i++)
        {
            while(st.size() && arr[i] < arr[st.top()]) st.pop();
            if(st.size()) left[i] = i - st.top();
            else left[i] = i+1;
            st.push(i);
        }
        
        while(st.size()) st.pop();
        
        // Right
        for(int i=n-1; i>=0; i--)
        {
            while(st.size() && arr[i] <= arr[st.top()]) st.pop();
            if(st.size()) right[i] = st.top() - i;
            else right[i] = n - i;
            st.push(i);
        }
        
        // for(int i=0; i<n; i++) cout << left[i] << " : " << right[i] << endl;
        
        // for each i, contribution is (Left * Right) * Element 
        
        int res = 0;
        int MOD = 1e9 + 7;
        for (int i = 0; i < n; i++)
        {
            long long prod = (left[i]*right[i])%MOD;
            prod = (prod*arr[i])%MOD;
            res = (res + prod)%MOD;
        }
        
        return res%MOD;
    }
-----------------------------------------------------------

// method 2:
// undersatnd this thoroughly how it handles duplicates written in comments in solution
//  Notice the sign ">=", This ensures that no contribution
class Solution {
    public int sumSubarrayMins(int[] arr) {
        int MOD = 1000000007;

        Stack<Integer> stack = new Stack<>();
        long sumOfMinimums = 0;

        // building monotonically increasing stack
        for (int i = 0; i <= arr.length; i++) {

            // when i reaches the array length, it is an indication that
            // all the elements have been processed, and the remaining
            // elements in the stack should now be popped out.

            while (!stack.empty() && (i == arr.length || arr[stack.peek()] >= arr[i])) {

                // Notice the sign ">=", This ensures that no contribution
                // is counted twice. rightBoundary takes equal or smaller 
                // elements into account while leftBoundary takes only the
                // strictly smaller elements into account

                int mid = stack.pop();
                int leftBoundary = stack.empty() ? -1 : stack.peek();
                int rightBoundary = i;

                // count of subarrays where mid is the minimum element
                long count = (mid - leftBoundary) * (rightBoundary - mid) % MOD;

                sumOfMinimums += (count * arr[mid]) % MOD;
                sumOfMinimums %= MOD;
            }
            stack.push(i);
        }

        return (int) (sumOfMinimums);
    }
}
-----------------------------------------------------------

// method 3: dp solution  
// VVVIMP
class Solution {
    public int sumSubarrayMins(int[] arr) {
        int MOD = 1000000007;

        Stack<Integer> stack = new Stack<>();

        // make a dp array of the same size as the input array `arr`
        int[] dp = new int[arr.length];

        // making a monotonic increasing stack
        for (int i = 0; i < arr.length; i++) {
            // pop the stack until it is empty or
            // the top of the stack is greater than or equal to
            // the current element
            while (!stack.empty() && arr[stack.peek()] >= arr[i]) {
                stack.pop();
            }

            // either the previousSmaller element exists
            if (stack.size() > 0) {
                int previousSmaller = stack.peek();
                dp[i] = dp[previousSmaller] + (i - previousSmaller) * arr[i];
            } else {
                // or it doesn't exist, in this case the current element
                // contributes with all subarrays ending at i
                dp[i] = (i + 1) * arr[i];
            }
            // push the current index
            stack.push(i);
        }

        // Add all elements of the dp to get the answer
        long sumOfMinimums = 0;
        for (int count : dp) {
            sumOfMinimums += count;
            sumOfMinimums %= MOD;
        }

        return (int) sumOfMinimums;
    }
}
-----------------------------------------------------------
/*
	Sum of subarray ranges (in given array find for all subarrays value of (Max -min) in that subarray and 
    sum each value)
    https://leetcode.com/problems/sum-of-subarray-ranges/description/
*/

class Solution {
public:
    long long subArrayRanges(vector<int>& nums) {
        int n = nums.size();
        long long answer = 0;
        stack<int> stk;
        
        // Find the sum of all the minimum.
        for (int right = 0; right <= n; ++right) {
            while (!stk.empty() && (right == n || nums[stk.top()] >= nums[right])) {
                int mid = stk.top();
                stk.pop();
                int left = stk.empty() ? -1 : stk.top();
                answer -= (long long)nums[mid] * (right - mid) * (mid - left);
            }
            stk.push(right); 
        }
        
        // Find the sum of all the maximum.
        stk.pop();
        for (int right = 0; right <= n; ++right) {
            while (!stk.empty() && (right == n || nums[stk.top()] <= nums[right])) {
                int mid = stk.top();
                stk.pop();
                int left = stk.empty() ? -1 : stk.top();
                answer += (long long)nums[mid] * (right - mid) * (mid - left);
            }
            stk.push(right); 
        }
        return answer;
    }
};



/*
TODO:
Number of NGEs to the right
https://www.codingninjas.com/studio/problems/count-of-greater-elements-to-the-right_8365436?utm_source=striver&utm_medium=website&utm_campaign=a_zcoursetuf&leftPanelTabValue=PROBLEM
see if you can find any efficient solution for this 
*/

vector<int> countGreater(vector<int>&arr, vector<int>&query) {

	// Initialize integer variables 'n' and 'q' with arr.length and query.length respectively.
	int n = arr.size(), q = query.size();

	// Declare an integer array 'answer' of length 'q'.
	vector<int> answer(q, 0);

	for (int i = 0; i < q; i++) {
		int queryIndex = query[i];

		// Check for all the greater elements to the right.
		for (int j = queryIndex + 1; j < n; j++) {
			if (arr[j] > arr[queryIndex]) {
				answer[i]++;
			}
		}
	}

	// Return 'answer'
	return answer;
}
-------------------------------------------------------
/*
see if you can find any efficient solution for this 
below solution wont work
sample test case:
 8 3
1 3 6 5 8 9 13 4
0 1 5
my output: 5 4 1 
desired output: 7 6 1 
*/
vector<int> countGreater(vector<int>&arr, vector<int>&query) {
    int n = arr.size();
      vector < int > nge(n, 0);
      stack < int > st;
      for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && st.top() <= arr[i]) {
          st.pop();
        }

    
        if (!st.empty()) nge[i] = st.size();

        st.push(arr[i]);
      }
      vector<int>res(query.size(), 0);

      for (int i=0; i<query.size(); i++){
          res[i] = nge[query[i]];

      }

      return res;

}
---------------------------