
/*
 Method1: sorting (leetcode)
 Time Complexity: NLOG(N)
 Space Complexity: LOG(N)
*/
class Solution {
public:
    int numberOfWeakCharacters(vector<vector<int>>& properties) {
        // Sort in ascending order of attack, 
        // If attack is same sort in descending order of defense
        sort(properties.begin(), properties.end(), 
             [](const vector<int>& a, vector<int>& b) -> bool { 
                 return (a[0] == b[0] ? a[1] > b[1] : a[0] < b[0]);});
             
        int weakCharacters = 0;
        int maxDefense = 0;
        for (int i = (int)properties.size() - 1; i >= 0; i--) {
            // Compare the current defense with the maximum achieved so far
            if (properties[i][1] < maxDefense) {
                weakCharacters++;
            }
            maxDefense = max(maxDefense, properties[i][1]);
        }
        
        return weakCharacters;
    }
};
===================
/*
 Method2: greedy (leetcode)
 Time Complexity: O(N+K)
 Space Complexity: O(K)
 For a pair (a, b) we can say it to be weak if the maximum defense value among all 
 the pairs with attack-value > a is greater than b. So we will keep the maximum defense value 
 among all the pairs with an attack value greater than x, for every value of x. Then the pair (a, b) will be weak 
 if the maximum defense value stored for value a + 1 is greater than b.
*/
class Solution {
public:
    int numberOfWeakCharacters(vector<vector<int>>& properties) {
        int maxAttack = 0;
        // Find the maximum atack value
        for (vector<int>& property : properties) {
            int attack = property[0];
            maxAttack = max(maxAttack, attack);
        }
        
        vector<int> maxDefense(maxAttack + 2, 0);
        // Store the maximum defense for an attack value
        for (vector<int>& property : properties) {
            int attack = property[0];
            int defense = property[1];
            
            maxDefense[attack] = max(maxDefense[attack], defense);
        }

        // Store the maximum defense for attack greater than or equal to a value
        for (int i = maxAttack - 1; i >= 1; i--) {
            maxDefense[i] = max(maxDefense[i], maxDefense[i + 1]);
        }
        
        int weakCharacters = 0;
        for (vector<int>& property : properties) {
            int attack = property[0];
            int defense = property[1];
            
            // If their is a greater defense for properties with greater attack
            if (defense < maxDefense[attack + 1]) {
                weakCharacters++;
            }
        }
        
        return weakCharacters;
    }
};
============================================================================