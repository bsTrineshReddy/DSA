/*
 Method1:
 Time Complexity:
 Space Complexity:
*/
class Solution {
public:
    int brokenCalc(int startValue, int target) {
        int ans = 0;
        while (target > startValue) {
            ans++;
            if (target % 2 == 1)
                target++;
            else
                target /= 2;
        }

        return ans + startValue - target;
    }
};
===================
/*
 Method1: bfs (own)
    TLE coming for this
 Time Complexity:
 Space Complexity:
*/
class Solution {
public:
    int brokenCalc(int startValue, int target) {

        queue<int>q;
        q.push(target);
        int level =0;

        while(q.empty()==false) {
            int size = q.size();
            while(size--) {
                int cur = q.front();
                q.pop();
                if(cur == startValue)
                 return level;
                q.push(cur/2);
                q.push(cur + 1);

            }
            level++;
            
        }
        return level;
    }
};
============================================================================