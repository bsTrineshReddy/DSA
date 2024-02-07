/*
 Method1: sort and build groups like this 1, 2, 3,4 --
 Time Complexity:O(Nlog(N))
 Space Complexity:1
*/
int maximumGroups(vector<int>& grades) {
    sort(grades.begin(), grades.end());

    int prevSum = 0, curSum = 0;
    int prevCount = 0, curCount = 0, res = 0;

    for(int grade: grades){
        curSum += grade;
        curCount++;
        if(curCount > prevCount && curSum > prevSum){
            res++;
            prevSum = curSum; prevCount = curCount;
            curSum = curCount = 0;
        }
    }

    return res;
}

/*
 Method2: if we observe sorting is redundant here we can just count numbers
 Time Complexity: O(n)
 Space Complexity:0(1)
*/
class Solution {
public:
    int maximumGroups(vector<int>& grades) {
        int k = 0, total = 0, n = grades.size();

        // total + k +1 means if cur_count + next_count(k+1) <=n then only consider
        while (total + k + 1 <= n) {
            total += k +1;
            k++;
        }
            
        return k;
        
    }
};
=======
/*
 Method3: Mathematics
 1+2+3+---k <=n  (k(k+1)/2<=n) ===  k^2+k-2*n<=0  ==> k = (-1 + sqrt(n*8+1))/2
 Time Complexity:
 Space Complexity:
*/
    int maximumGroups(vector<int>& grades) {
        return (int)((sqrt(grades.size() * 8 + 1) - 1)/2);
    }