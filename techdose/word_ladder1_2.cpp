/*
 word_ladder1
*/

// method 1 :techdose bfs
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {  
        unordered_set<string> myset;
        bool isPresent = false; //Checks if endWord is present in Dict
        //Insert all words from Dict in myset
        for(auto word: wordList)
        {
            if(endWord.compare(word)==0)
                isPresent = true;
            myset.insert(word);    //Insert word in Dict
        }
        if(isPresent==false)    //endWord is not present in Dict
            return 0;
        
        queue<string> q;
        q.push(beginWord);
        int depth = 0;
        
        while(!q.empty())
        {
            depth+=1;
            int lsize = q.size();   //No of elements at a level
            while(lsize--)
            {
                string curr = q.front();
                q.pop();
                //check for all possible 1 depth words
                for(int i=0;i<curr.length();++i)  //For each index
                {
                    string temp = curr;
                    for(char c='a';c<='z';++c)  //Try all possible chars
                    {
                        temp[i] = c;
                        if(curr.compare(temp)==0)
                            continue;   //Skip the same word
                        if(temp.compare(endWord)==0)
                            return depth+1; //endWord found
                        if(myset.find(temp)!=myset.end())
                        {
                            q.push(temp);
                            myset.erase(temp);
                        }
                    }
                }
            }
        }
        return 0;
    }
};
----------------------------
//method 2: striver
#include <bits/stdc++.h>
using namespace std;
 
class Solution
{
public:
    int wordLadderLength(string startWord, string targetWord,
                         vector<string> &wordList)
    {
    // Creating a queue ds of type {word,transitions to reach ‘word’}.
        queue<pair<string, int>> q;

        // BFS traversal with pushing values in queue 
        // when after a transformation, a word is found in wordList.
        q.push({startWord, 1});

        // Push all values of wordList into a set
        // to make deletion from it easier and in less time complexity.
        unordered_set<string> st(wordList.begin(), wordList.end());
        st.erase(startWord);
        while (!q.empty())
        {
            string word = q.front().first;
            int steps = q.front().second;
            q.pop();

            // we return the steps as soon as
            // the first occurence of targetWord is found.
            if (word == targetWord)
                return steps;

            for (int i = 0; i < word.size(); i++)
            {
                // Now, replace each character of ‘word’ with char
                // from a-z then check if ‘word’ exists in wordList.
                char original = word[i];
                for (char ch = 'a'; ch <= 'z'; ch++)
                {
                    word[i] = ch;
                    // check if it exists in the set and push it in the queue.
                    if (st.find(word) != st.end())
                    {
                        st.erase(word);
                        q.push({word, steps + 1});
                    }
                }
                word[i] = original;
            }
        }
        // If there is no transformation sequence possible
        return 0;
    }
};
----------------------------
// method3: bfs with preprocessing leetcode
class Solution {
    public int ladderLength(String beginWord, String endWord, List<String> wordList) {

        // Since all words are of same length.
        int L = beginWord.length();

        // Dictionary to hold combination of words that can be formed,
        // from any given word. By changing one letter at a time.
        Map<String, List<String>> allComboDict = new HashMap<>();

        wordList.forEach( word -> {
            for (int i = 0; i < L; i++) {
                // Key is the generic word
                // Value is a list of words which have the same intermediate generic word.
                String newWord = word.substring(0, i) + '*' + word.substring(i + 1, L);
                List<String> transformations = allComboDict.getOrDefault(newWord, new ArrayList<>());
                transformations.add(word);
                allComboDict.put(newWord, transformations);
            }
        });

        // Queue for BFS
        Queue<Pair<String, Integer>> Q = new LinkedList<>();
        Q.add(new Pair(beginWord, 1));

        // Visited to make sure we don't repeat processing same word.
        Map<String, Boolean> visited = new HashMap<>();
        visited.put(beginWord, true);

        while (!Q.isEmpty()) {
            Pair<String, Integer> node = Q.remove();
            String word = node.getKey();
            int level = node.getValue();
            for (int i = 0; i < L; i++) {

                // Intermediate words for current word
                String newWord = word.substring(0, i) + '*' + word.substring(i + 1, L);

                // Next states are all the words which share the same intermediate state.
                for (String adjacentWord : allComboDict.getOrDefault(newWord, new ArrayList<>())) {
                    // If at any point if we find what we are looking for
                    // i.e. the end word - we can return with the answer.
                    if (adjacentWord.equals(endWord)) {
                        return level + 1;
                    }
                    // Otherwise, add it to the BFS Queue. Also mark it visited
                    if (!visited.containsKey(adjacentWord)) {
                        visited.put(adjacentWord, true);
                        Q.add(new Pair(adjacentWord, level + 1));
                    }
                }
            }
        }

        return 0;
    }
}
----------------------------
// method4: bidirectional bfs
class Solution {

    private int L;
    private Map<String, List<String>> allComboDict;

    Solution() {
        this.L = 0;

        // Dictionary to hold combination of words that can be formed,
        // from any given word. By changing one letter at a time.
        this.allComboDict = new HashMap<>();
    }

    private int visitWordNode(
            Queue<Pair<String, Integer>> Q,
            Map<String, Integer> visited,
            Map<String, Integer> othersVisited) {

        for (int j = Q.size(); j > 0; j--) {
            
            Pair<String, Integer> node = Q.remove();
            String word = node.getKey();
            int level = node.getValue();

            for (int i = 0; i < this.L; i++) {

                // Intermediate words for current word
                String newWord = word.substring(0, i) + '*' + word.substring(i + 1, L);

                // Next states are all the words which share the same intermediate state.
                for (String adjacentWord : this.allComboDict.getOrDefault(newWord, new ArrayList<>())) {
                    // If at any point if we find what we are looking for
                    // i.e. the end word - we can return with the answer.
                    if (othersVisited.containsKey(adjacentWord)) {
                        return level + othersVisited.get(adjacentWord);
                    }

                    if (!visited.containsKey(adjacentWord)) {

                        // Save the level as the value of the dictionary, to save number of hops.
                        visited.put(adjacentWord, level + 1);
                        Q.add(new Pair(adjacentWord, level + 1));
                    }
                }
            }
        }
        return -1;
    }

    public int ladderLength(String beginWord, String endWord, List<String> wordList) {

        if (!wordList.contains(endWord)) {
            return 0;
        }

        // Since all words are of same length.
        this.L = beginWord.length();

        wordList.forEach( word -> {
            for (int i = 0; i < L; i++) {
                // Key is the generic word
                // Value is a list of words which have the same intermediate generic word.
                String newWord = word.substring(0, i) + '*' + word.substring(i + 1, L);
                List<String> transformations =
                        this.allComboDict.getOrDefault(newWord, new ArrayList<>());
                transformations.add(word);
                this.allComboDict.put(newWord, transformations);
            }
        });

        // Queues for birdirectional BFS
        // BFS starting from beginWord
        Queue<Pair<String, Integer>> Q_begin = new LinkedList<>();
        // BFS starting from endWord
        Queue<Pair<String, Integer>> Q_end = new LinkedList<>();
        Q_begin.add(new Pair(beginWord, 1));
        Q_end.add(new Pair(endWord, 1));

        // Visited to make sure we don't repeat processing same word.
        Map<String, Integer> visitedBegin = new HashMap<>();
        Map<String, Integer> visitedEnd = new HashMap<>();
        visitedBegin.put(beginWord, 1);
        visitedEnd.put(endWord, 1);
        int ans = -1;
        
        while (!Q_begin.isEmpty() && !Q_end.isEmpty()) {
            
            // Progress forward one step from the shorter queue
            if (Q_begin.size() <= Q_end.size()) {
                ans = visitWordNode(Q_begin, visitedBegin, visitedEnd);
            } else {
                ans = visitWordNode(Q_end, visitedEnd, visitedBegin);    
            }

            if (ans > -1) {
                return ans;
            }
        }

        return 0;
    }
}
----------------------------------------------------------------------------------------------------------------
/*
word ladder2
*/

// method1: techdose dfs
class Solution {
public:
    vector<vector<string>>  ans;    //Stores all possible paths
    
    void DFS(string& beginWord, string& endWord, unordered_map<string, unordered_set<string>>& adj, vector<string> &path) {
        path.push_back(beginWord);  //Push current word
        if(beginWord == endWord)
        {
            ans.push_back(path);
            path.pop_back();
            return;
        }
        for(auto x : adj[beginWord])
            DFS(x, endWord, adj, path);
        
        path.pop_back();    //Pop current word to Backtrack
    }
    
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_map<string, unordered_set<string>> adj;   //Adjacency List
        unordered_set<string> dict(wordList.begin(),wordList.end());   //Insert WordList in SET
        
        //STEP-1: Find min-depth using BFS
        queue<string> Q;    //For BFS traversal
        Q.push(beginWord);  //Push start node (beginWord)
        unordered_map<string, int> visited; //Key->String (Node)...Value->Level (Depth of traversal)
        visited[beginWord] = 0; //Start node will always be at level 0
        while(!Q.empty())
        {
            string curr = Q.front();
            Q.pop();
            string temp = curr;
            for(int i = 0; i < curr.size(); ++i)    //For all characters
            {
                for(char x = 'a'; x <= 'z'; ++x)    //Try all possible 26 letters
                {
                    if(temp[i] == x)    //Skip if letter is same as in original word
                        continue;

                    temp[i] = x;    
                    if(dict.count(temp) > 0)    //Check if new word is present in wordList
                    {
                        if(visited.count(temp) == 0)    //check if the new word was already visited
                        {
                            visited[temp] = visited[curr] + 1;
                            Q.push(temp);
                            adj[curr].insert(temp);
                        } 
                        else if(visited[temp] == visited[curr] + 1) //If already visited and new word is the child (We should always move down)
                            adj[curr].insert(temp);
                    }
                }
                temp[i] = curr[i];  //Revert back temp to curr
            }
        }
        //STEP-2: Find all possible paths at min-depth using DFS
        vector<string> path;
        DFS(beginWord, endWord, adj, path); //Find all possible paths with min-depth
        return ans; 
    }
};
-------------------------------
//method2: striver
using namespace std;

class Solution
{
    // Create a map of type word->level to get the idea 
    // on which level the word comes after the transformations.
    unordered_map<string, int> mpp;

    // A vector for storing the final answer.
    vector<vector<string>> ans;
    string b;

private:
    void dfs(string word, vector<string> &seq)
    {
        // Function for implementing backtracking using the created map
        // in reverse order to find the transformation sequence in less time.

        // Base condition :
        // If word equals beginWord, we’ve found one of the sequences
        // simply reverse the sequence and return. 
        if (word == b)
        {
            reverse(seq.begin(), seq.end());
            ans.push_back(seq);
    
            // reverse again so that the dfs calls are not disturbed.
            reverse(seq.begin(), seq.end());
            return;
        }
        int sz = word.size();
        int steps = mpp[word];

        // Replace each character of the word with letters from a-z 
        // and check whether the transformed word is present in the map
        // and at the previous level or not.  
        for (int i = 0; i < sz; i++)
        {
            char original = word[i];
            for (char ch = 'a'; ch <= 'z'; ch++)
            {
                word[i] = ch;
                if (mpp.find(word) != mpp.end() && mpp[word] + 1 == steps)
                {
                    seq.push_back(word);
                    dfs(word, seq);
                    // pop the current word from the back of the queue
                    // to traverse other possibilities.
                    seq.pop_back();
                }
            }
            word[i] = original;
        }
    }

public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &wordList)
    {
        // Push all values of wordList into a set
        // to make deletion from it easier and in less time complexity.
        unordered_set<string> st(wordList.begin(), wordList.end());

        // Perform BFS traversal and push the string in the queue
        // as soon as they’re found in the wordList.
        queue<string> q;
        b = beginWord;
        q.push({beginWord});

        // beginWord initialised with level 1.
        mpp[beginWord] = 1;
        int sz = beginWord.size();
        st.erase(beginWord);
        while (!q.empty())
        {

            string word = q.front();
            int steps = mpp[word];
            q.pop();
            
            // Break out if the word matches the endWord
            if (word == endWord)
                break;

            // Replace each character of the word with letters from a-z 
            // and check whether the transformed word is present in the 
            // wordList or not, if yes then push to queue
            for (int i = 0; i < sz; i++)
            {
                char original = word[i];

                for (char ch = 'a'; ch <= 'z'; ch++)
                {

                    word[i] = ch;
                    if (st.count(word))
                    {
                        q.push(word);
                        st.erase(word);
                       
                        // push the word along with its level
                        // in the map data structure.
                        mpp[word] = steps + 1;
                    }
                }
                word[i] = original;
            }
        }
    
        // If we reach the endWord, we stop and move to step-2
        // that is to perform reverse dfs traversal.
        if (mpp.find(endWord) != mpp.end())
        {
            vector<string> seq;
            seq.push_back(endWord);
            dfs(endWord, seq);
        }
        return ans;
    }
};

// A comparator function to sort the answer.
bool comp(vector<string> a, vector<string> b)
{
    string x = "", y = "";
    for (string i : a)
        x += i;
    for (string i : b)
        y += i;

    return x < y;
}

int main()
{

    vector<string> wordList = {"des", "der", "dfr", "dgt", "dfs"};
    string startWord = "der", targetWord = "dfs";
    Solution obj;
    vector<vector<string>> ans = obj.findLadders(startWord, targetWord, wordList);

    // If no transformation sequence is possible.
    if (ans.size() == 0)
        cout << -1 << endl;
    else
    {
        sort(ans.begin(), ans.end(), comp);
        for (int i = 0; i < ans.size(); i++)
        {
            for (int j = 0; j < ans[i].size(); j++)
            {
                cout << ans[i][j] << " ";
            }
            cout << endl;
        }
    }

    return 0;
}
----------------------------
// method3 : bfs with backtarcking leetcode
class Solution {
public:
    unordered_map<string, vector<string>> adjList;
    vector<string> currPath;
    vector<vector<string>> shortestPaths;

    vector<string> findNeighbors(string &word, unordered_set<string> &wordList) {
        vector<string> neighbors;

        for (int i = 0; i < word.size(); i++) {
            char oldChar = word[i];

            // replace the i-th character with all letters from a to z except the original character
            for (char c = 'a'; c <= 'z'; c++) {
                word[i] = c;

                // skip if the character is same as original or if the word is not present in the
                // wordList
                if (c == oldChar || !wordList.count(word)) {
                    continue;
                }
                neighbors.push_back(word);
            }
            word[i] = oldChar;
        }
        return neighbors;
    }

    void backtrack(string &source, string &destination) {
        // store the path if we reached the endWord
        if (source == destination) {
            shortestPaths.push_back(vector<string>(currPath.rbegin(), currPath.rend()));
        }
        for (int i = 0; i < adjList[source].size(); i++) {
            currPath.push_back(adjList[source][i]);
            backtrack(adjList[source][i], destination);
            currPath.pop_back();
        }
    }

    void bfs(string& beginWord, string& endWord, unordered_set<string>& wordList) {
        queue<string> q;
        q.push(beginWord);

        // remove the root word which is the first layer
        if (wordList.find(beginWord) != wordList.end()) {
            wordList.erase(wordList.find(beginWord));
        }

        unordered_map<string, int> isEnqueued;
        isEnqueued[beginWord] = 1;

        while (!q.empty()) {
            // visited will store the words of current layer
            vector<string> visited;

            for (int i = q.size() - 1; i >= 0; i--) {
                string currWord = q.front();
                q.pop();

                // findNeighbors will have the adjacent words of the currWord
                vector<string> neighbors = findNeighbors(currWord, wordList);
                for (auto word : neighbors) {
                    visited.push_back(word);
                    // add the edge from word to currWord in the list
                    adjList[word].push_back(currWord);

                    if (isEnqueued.find(word) == isEnqueued.end()) {
                        q.push(word);
                        isEnqueued[word] = 1;
                    }
                }
            }
            // removing the words of the previous layer
            for (int i = 0; i < visited.size(); i++) {
                if (wordList.find(visited[i]) != wordList.end()) {
                    wordList.erase(wordList.find(visited[i]));
                }
            }
        }
    }

    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &wordList) {
        // copying the words into the set for efficient deletion in BFS
        unordered_set<string> copiedWordList(wordList.begin(), wordList.end());
        // build the DAG using BFS
        bfs(beginWord, endWord, copiedWordList);

        // every path will start from the endWord
        currPath = {endWord};
        // traverse the DAG to find all the paths between endWord and beginWord
        backtrack(endWord, beginWord);

        return shortestPaths;
    }
};
----------------------------
// method4 : bidirectional bfs with backtarcking leetcode
class Solution {
public:
    unordered_map<string, vector<string>> adjList;
    vector<string> currPath;
    vector<vector<string>> shortestPaths;
    
    vector<string> findNeighbors(string &word, unordered_set<string>& wordList) {
        vector<string> neighbors;
        
        for (int i = 0; i < word.size(); i++) {
            char oldChar = word[i];   
            
            // replace the i-th character with all letters from a to z except the original character
            for (char c = 'a'; c <= 'z'; c++) {
                word[i] = c;
                
                // skip if the character is same as original or if the word is not present in the wordList
                if (c == oldChar || !wordList.count(word)) {
                    continue;
                }
                neighbors.push_back(word);
            }
            word[i] = oldChar;
        }
        return neighbors;
    }
    
    void backtrack(string &source, string &destination) {
        // store the path if we reached the endWord
        if (source == destination) {
            shortestPaths.push_back(currPath);
        }
        for (int i = 0; i < adjList[source].size(); i++) {
            currPath.push_back(adjList[source][i]);
            backtrack(adjList[source][i], destination);
            currPath.pop_back();
        }
    }
    
    void addEdge(string &word1, string &word2, int direction) {
        if(direction == 1) {
            adjList[word1].push_back(word2);
        } else {
            adjList[word2].push_back(word1);
        }
    }
    
    bool bfs(string beginWord, string endWord, unordered_set<string> wordList) {
        if (wordList.count(endWord) == 0) {
            return false;
        }
        
        // remove the root word which is the first layer
        if (wordList.find(beginWord) != wordList.end()) {
            wordList.erase(wordList.find(beginWord));
        }

        unordered_set<string> forwardQueue, backwardQueue;
        forwardQueue.insert(beginWord);
        backwardQueue.insert(endWord);
        
        bool found = false;
        int direction = 1;
        
        while (forwardQueue.size() != 0)  {
            // visited will store the words of current layer
            unordered_set<string> visited;
            
            // swap the queues because we are always extending the forwardQueue
            if (forwardQueue.size() > backwardQueue.size()) {
                swap(forwardQueue, backwardQueue);
                direction ^= 1;
            }
            
            for (auto currWord : forwardQueue) {
                vector<string> neighbors = findNeighbors(currWord, wordList);

                 for (auto word : neighbors) {
                    
                     // if the backwardQueue already contains it we can stop after completing this level
                     if (backwardQueue.find(word) != backwardQueue.end()) {
                         found = true;
                         addEdge(currWord, word, direction);
                    
                     /* the word shouldn't be presnt in forwardQueue because if it is then the edge will
                        be between two words at the same level which we don't want */
                     } else if (!found && wordList.count(word) != 0 && forwardQueue.count(word) == 0) {
                         visited.insert(word);
                         addEdge(currWord, word, direction);
                     }
                 }
            }
            
            // removing the words of the previous layer
            for (auto currWord : forwardQueue) {
                if (wordList.find(currWord) != wordList.end()) {
                    wordList.erase(wordList.find(currWord));
                }
            }
            if (found) {
                break;
            }
            
            forwardQueue = visited;
        }
        return found;
    }
    
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        // copying the words into the set for efficient deletion in BFS
        unordered_set<string> copiedWordList(wordList.begin(), wordList.end());
        // build the DAG using BFS
        bool sequence_found = bfs(beginWord, endWord, copiedWordList);
        
        // There is no valid sequence that connects `beginWord` to `endWord`
        if (sequence_found == false) {
            return shortestPaths;
        }
        // every path will start from the beginWord
        currPath = {beginWord};
        // traverse the DAG to find all the paths between beginWord and endWord
        backtrack(beginWord, endWord);
        
        return shortestPaths;
    }
};
------------------------------------------------------------------------------------