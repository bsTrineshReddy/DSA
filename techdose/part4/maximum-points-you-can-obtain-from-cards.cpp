/*
 Method1: memo + recursion
 Time Complexity:  O(n^2*k) (this many number of dp state possible)
 Space Complexity: O(K)
*/
class Solution {
    unordered_map<string, int> dp;
    int func(vector<int>& cardPoints, int i, int j, int n,int k) {

        string s = to_string(i) + "*" + to_string(j) + "*" + to_string(k);
        if(k==0)
        return 0;
        if(i==j && k==1)return cardPoints[i];

        if(dp.find(s)!= dp.end())
         return dp[s];

        int res1 = cardPoints[i] + func(cardPoints, i+1,j,n,k-1);
        int res2 = cardPoints[j] + func(cardPoints, i,j-1,n,k-1);

        return dp[s] = max(res1,res2);

    }
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int n= cardPoints.size();

        return func(cardPoints, 0, n-1, n,k);

        
    }
};
===================
/*
 Method2:  dp (leetcode)
 Time Complexity:   O(K)
 Space Complexity:  O(1)
*/
class Solution {
public:
    int maxScore(vector<int> &cardPoints, int k) {
        int n = cardPoints.size();

        int frontSetOfCards[k + 1];
        int rearSetOfCards[k + 1];

        //Intialize 0th index in both the arrays
        frontSetOfCards[0] = rearSetOfCards[0] = 0;

        for (int i = 0; i < k; i++) {
            frontSetOfCards[i + 1] = cardPoints[i] + frontSetOfCards[i];
            rearSetOfCards[i + 1] = cardPoints[n - i - 1] + rearSetOfCards[i];
        }

        int maxScore = 0;
        // Each i represents the number of cards we take from the front.
        for (int i = 0; i <= k; i++) {
            int currentScore = frontSetOfCards[i] + rearSetOfCards[k - i];
            maxScore = max(maxScore, currentScore);
        }

        return maxScore;
    }
};
===================
/*
 Method3:  dp (space optimised)
 Time Complexity:  O(k)
 Space Complexity: o(1)
*/
class Solution {
public:
    int maxScore(vector<int> &cardPoints, int k) {
        int frontScore = 0;
        int rearScore = 0;
        int n = cardPoints.size();

        for (int i = 0; i < k; i++) {
            frontScore += cardPoints[i];
        }

        // take all k cards from the beginning
        int maxScore = frontScore;

        // take i from the beginning and k - i from the end
        for (int i = k - 1; i >= 0; i--) {
            rearScore += cardPoints[n - (k - i)];
            frontScore -= cardPoints[i];
            int currentScore = rearScore + frontScore;
            maxScore = max(maxScore, currentScore);
        }

        return maxScore;
    }
};
===================
/*
 Method4: sliding window
 Time Complexity:
 Space Complexity:
*/
class Solution {
public:
    int maxScore(vector<int> &cardPoints, int k) {
        int startingIndex = 0;
        int presentSubarrayScore = 0;
        int n = cardPoints.size();
        int requiredSubarrayLength = n - k;
        int minSubarrayScore;
        int totalScore = 0;

        // Total score obtained on selecting all the cards.
        for (int i : cardPoints) {
            totalScore += i;
        }
        
        minSubarrayScore = totalScore;

        if (k == n) {
            return totalScore;
        }

        for (int i = 0; i < n; i++) {
            presentSubarrayScore += cardPoints[i];
            int presentSubarrayLength = i - startingIndex + 1;
            // If a valid subarray (having size cardsPoints.size() - k) is possible.
            if (presentSubarrayLength == requiredSubarrayLength) {
                minSubarrayScore = min(minSubarrayScore, presentSubarrayScore);
                presentSubarrayScore -= cardPoints[startingIndex++];
            }
        }
        return totalScore - minSubarrayScore;
    }
};
============================================================================