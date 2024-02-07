/*
word_break1
*/

//Approach-1: Memoization DP
class Solution {
    unordered_map<int,bool> mem;
    unordered_set<string> myset;//dictionary

    bool partition(string s,int pos){
        if(pos==s.size())   return true;
        if(mem.count(pos))  return mem[pos];
        
        string t="";
        for(int i=pos;i<s.size();++i)
            if(myset.count(s.substr(pos,i-pos+1)) and partition(s,i+1))
                return mem[pos] = true;
        return mem[pos] = false;
    }
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        for(auto str: wordDict)
            myset.insert(str);
        
        return partition(s,0);
    }
};
----------------------------------
//Approach-2: Tabulation DP
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        bool dp[n+1][n+1];
        
        unordered_set<string> myset;
        for(auto word: wordDict)
            myset.insert(word);
        
        for(int length=1;length<=n;++length) //Window Size
        {
            int start = 1;
            int end = length;
            while(end<=n) //Sliding Window
            {
                string temp = s.substr(start-1,length);
                if(myset.find(temp)!=myset.end())
                    dp[start][end] = true;
                else
                {
                    bool flag = false;
                    for(int i=start;i<end;++i)
                        if(dp[start][i] and dp[i+1][end])
                        {
                            flag = true;
                            break;
                        }
                    dp[start][end] = flag;
                }
                start += 1;
                end += 1;
            }
        }
        return dp[1][n];
    }
};
----------------------------------
//Approach-3: BFS
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> words(wordDict.begin(), wordDict.end());
        queue<int> queue;
        vector<bool> seen(s.length(), false);
        queue.push(0);
        
        while (!queue.empty()) {
            int start = queue.front();
            queue.pop();
            
            if (start == s.length()) {
                return true;
            }
            
            for (int end = start + 1; end <= s.length(); end++) {
                if (seen[end]) {
                    continue;
                }

                if (words.find(s.substr(start, end - start)) != words.end()) {
                    queue.push(end);
                    seen[end] = true;
                }
            }
        }
        
        return false;
    }
};

// Top down dp by going through words in dict
class Solution {
public:
    vector<int> memo;
    vector<string> wordDict;
    string s;
    
    bool wordBreak(string s, vector<string>& wordDict) {
        memo = vector(s.length(), -1);
        this->wordDict = wordDict;
        this->s = s;
        return dp(s.length() - 1);
    }
    
    bool dp(int i) {
        if (i < 0) return true;
        
        if (memo[i] != -1) {
            return memo[i] == 1;
        }
        
        for (string word: wordDict) {
            int currSize = word.length();
            // Handle out of bounds case
            if (i - currSize + 1 < 0) {
                continue;
            }

            if (s.substr(i - currSize + 1, currSize) == word && dp(i - currSize)) {
                memo[i] = 1;
                return true;
            }
        }
        
        memo[i] = 0;
        return false;
    }
};
=====================================
//bottom up dp by going thorugh words in dict
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        vector<bool> dp(s.length());
        for (int i = 0; i < s.length(); i++) {
            for (string word: wordDict) {
                // Handle out of bounds case
                if (i < word.length() - 1) {
                    continue;
                }
                
                if (i == word.length() - 1 || dp[i - word.length()]) {
                    if (s.substr(i - word.length() + 1, word.length()) == word) {
                        dp[i] = true;
                        break;
                    }
                }
            }
        }
        
        return dp[s.length() - 1];
    }
};
===============================
// Trie approach
struct TrieNode {
    bool isWord;
    unordered_map<char, TrieNode*> children;
    TrieNode() : isWord(false), children(unordered_map<char, TrieNode*>()) {}
};

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        TrieNode* root = new TrieNode();
        for (string word: wordDict) {
            TrieNode* curr = root;
            for (char c: word) {
                if (curr->children.find(c) == curr->children.end()) {
                    curr->children[c] = new TrieNode();
                }
                curr = curr->children[c];
            }
            
            curr->isWord = true;
        }
        
        vector<bool> dp(s.length());
        for (int i = 0; i < s.length(); i++) {
            if (i == 0 || dp[i - 1]) {
                TrieNode* curr = root;
                for (int j = i; j < s.length(); j++) {
                    char c = s[j];
                    if (curr->children.find(c) == curr->children.end()) {
                        // No words exist
                        break;
                    }
                    
                    curr = curr->children[c];
                    if (curr->isWord) {
                        dp[j] = true;
                    }
                }
            }
        }
        
        return dp[s.length() - 1];
    }
};
======================
// a different dp
class Solution {
public:
    bool wordBreak(std::string s, std::vector<std::string>& wordDict) {
        int n = s.length();
        std::unordered_set<std::string> words(wordDict.begin(), wordDict.end());
        std::vector<bool> dp(n + 1, false);
        dp[0] = true;

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                if (dp[j] && words.count(s.substr(j, i - j))) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[n];
    }
};
------------------------------------------------------------------------------------------------------------------------------- 
/*
word break2
*/

class Solution {
    vector<string> ans;//Store all valid sentences
    struct trienode{
        char c;
        int we;
        trienode *child[26];
        trienode(char c){
            we = 0;
            this->c = c;
            for(int i=0;i<26;++i)
                child[i]=NULL;
        }
    };
    trienode *root;//root of TRIE
    void insertInTrie(const string &word){
        trienode *curr = root;
        int idx;
        for(int i=0;i<word.size();++i){
            idx = word[i]-'a';
            if(!curr->child[idx])
                curr->child[idx] = new trienode(char(97+idx));
            curr = curr->child[idx];
        }
        curr->we += 1;
    }
    bool searchInTrie(string s){
        trienode *curr = root;
        int idx;
        for(int i=0;i<s.size();++i){
            idx = s[i]-'a';
            if(!curr->child[idx])
                return false;
            curr = curr->child[idx];
        }
        return curr->we>0;
    }
    
    void solve(const string &s,string st,int pos){
        if(pos==s.size()){
            ans.push_back(st);
            return;
        }
        st += " ";
        for(int i=pos;i<s.size();++i){
            if(searchInTrie(s.substr(pos,i+1-pos)))
                solve(s,st+s.substr(pos,i+1-pos),i+1);
        }
    }
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        root = new trienode('/');
        for(auto word: wordDict)
            insertInTrie(word);
        
        for(int i=0;i<s.size();++i) {
            if(searchInTrie(s.substr(0,i+1)))
                solve(s,s.substr(0,i+1),i+1);
        }
        return ans;
    }
};
----------------------------------
// method 2 = word break2
class Solution {
public:
    void solve(string s, vector<string>& res, unordered_set<string>& st, vector<string>&temp){
        if(s.length() == 0){
            string str = "";
            for(auto it:temp){
                str += it + " ";
            }
            str.pop_back();
            res.push_back(str);
            return;
        }
        for(int i=0;i<s.length(); i++){
            if(st.count(s.substr(0, i+1))){
                temp.push_back(s.substr(0, i+1));
                solve(s.substr(i+1), res, st, temp);
                temp.pop_back();
            }
        }
    }
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        vector<string>res, temp;
        unordered_set<string>st(wordDict.begin(), wordDict.end());
        
        solve(s, res, st, temp);
        return res;
    }
};
-------
class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        //insert all the words in the set
        unordered_set<string> set;
        vector<string> res;
        for(auto word:wordDict)
            set.insert(word);
        //to store the current string 
        string curr="";
        findHelper(0,s,curr,set,res);
        return res;
    }
    
    void findHelper(int ind,string s,string curr,unordered_set<string> set,vector<string>& res)
    {
        if(ind==s.length())
        {
            //we have reached end
            curr.pop_back(); //remove the trailing space
            res.push_back(curr);
        }
        string str="";
        for(int i=ind;i<s.length();i++)
        {
            //get every substring and check if it exists in set
            str.push_back(s[i]);
            if(set.count(str))
            {
                //we have got a word in dict 
                //explore more and get other substrings
                findHelper(i+1,s,curr+str+" ",set,res);
            }
        }
    }
};
-----------------
class Solution {
    public:
        vector<string> wordBreak(string s, vector<string>& wordDict) 
        {
            int max_len = 0;
            unordered_set<string> dict;
            for(string& str : wordDict)
            {
                dict.insert(str);
                max_len = max(max_len, (int)str.length());
            }

            unordered_map<int, vector<string>> mp;
            return break_word(s, 0, dict, max_len, mp);
        }

    protected:
        vector<string> break_word(  const string& s, int n, unordered_set<string>& dict, 
                                    int max_len, unordered_map<int, vector<string>>& mp)
        {
            if(mp.count(n)) return mp[n];

            string str;
            for(int i = n; i < s.length() && str.length() <= max_len; ++i)
            {
                str += s[i];
                if(dict.count(str))
                {
                    if(i == s.length()-1)
                        mp[n].push_back(str);
                    else
                    {
                        vector<string> vs = break_word(s, i+1, dict, max_len, mp);
                        for(auto& a : vs) mp[n].push_back(str + " " + a);
                    }
                }
            }
            return mp[n];
        }
};
-------------
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <list>

class Solution {
public:
    std::vector<std::string> wordBreak(std::string s, std::unordered_set<std::string>& wordDict) {
        std::unordered_map<std::string, std::list<std::string>> memo;
        return DFS(s, wordDict, memo);
    }

private:
    std::vector<std::string> DFS(const std::string& s, const std::unordered_set<std::string>& wordDict,
                                 std::unordered_map<std::string, std::list<std::string>>& memo) {
        if (memo.find(s) != memo.end())
            return memo[s];

        std::list<std::string> res;
        if (s.empty()) {
            res.push_back("");
            return std::vector<std::string>(res.begin(), res.end());
        }

        for (const std::string& word : wordDict) {
            if (s.compare(0, word.length(), word) == 0) {
                auto sublist = DFS(s.substr(word.length()), wordDict, memo);
                for (const std::string& sub : sublist)
                    res.push_back(word + (sub.empty() ? "" : " ") + sub);
            }
        }

        memo[s] = res;
        return std::vector<std::string>(res.begin(), res.end());
    }
};

int main() {
    Solution solution;
    std::string s = "catsanddog";
    std::unordered_set<std::string> wordDict = {"cat", "cats", "and", "sand", "dog"};
    std::vector<std::string> result = solution.wordBreak(s, wordDict);

    std::cout << "Word Breaks:" << std::endl;
    for (const std::string& str : result) {
        std::cout << str << std::endl;
    }

    return 0;
}
