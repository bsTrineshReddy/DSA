// method1: recursion (self)
// time = space = 
class Solution { 
private: 
    void combine(int n, int k, vector<vector<int>> &output, vector<int> &temp, int start){
        if(temp.size() == k){
            output.push_back(temp);
            return;
        }
        for(int i=start; i<=n; i++){
            temp.push_back(i);
            combine(n, k, output, temp, i+1);
            temp.pop_back();
        }
    }     
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> output;
        vector<int> temp;
        combine(n, k, output, temp, 1);
        return output;
    }
};
===================
// method2: recursion (leetcode)
class Solution {
public:
    int k;
    int n;
    
    vector<vector<int>> combine(int n, int k) {
        this->k = k;
        this->n = n;
        vector<vector<int>> ans;
        vector<int> curr;
        backtrack(curr, 1, ans);
        return ans;
    }
    
    void backtrack(vector<int>& curr, int firstNum, vector<vector<int>>& ans) {
        if (curr.size() == k) {
            ans.push_back(curr);
            return;
        }
        
        int need = k - curr.size();
        int remain = n - firstNum + 1;
        int available = remain - need;
        // Finally, we can calculate available = remain - need. This value represents the count of numbers available to us as children. 
        // We should only consider children in the range [firstNum, firstNum + available] 
        // instead of the range [firstNum, n] like in the above code.
        for (int num = firstNum; num <= firstNum + available; num++) {
            curr.push_back(num);
            backtrack(curr, num + 1, ans);
            curr.pop_back();
        }

        return;
    }
};
============
/*
method3: iterative
- not intuitive method
*/
class Solution {
public:
	vector<vector<int>> combine(int n, int k) {
		vector<vector<int>> result;
		int i = 0;
		vector<int> p(k, 0);
		while (i >= 0) {
			p[i]++;
			if (p[i] > n) --i;
			else if (i == k - 1) result.push_back(p);
			else {
			    ++i;
			    p[i] = p[i - 1];
			}
		}
		return result;
	}
};
=================