/*
 word search 1
*/
// method 1: backtarcking leetcode
class Solution {
private:
    std::vector<std::vector<char>> board;
    int ROWS;
    int COLS;

public:
    bool exist(std::vector<std::vector<char>>& board, std::string word) {
        this->board = board;
        this->ROWS = board.size();
        this->COLS = board[0].size();

        for (int row = 0; row < this->ROWS; ++row)
            for (int col = 0; col < this->COLS; ++col)
                if (this->backtrack(row, col, word, 0))
                    return true;
        return false;
    }

private:
    bool backtrack(int row, int col, const std::string& word, int index) {
        /* Step 1). check the bottom case. */
        if (index >= word.length())
            return true;

        /* Step 2). Check the boundaries. */
        if (row < 0 || row == this->ROWS || col < 0 || col == this->COLS
            || this->board[row][col] != word[index])
            return false;

        /* Step 3). explore the neighbors in DFS */
        bool ret = false;
        // mark the path before the next exploration
        this->board[row][col] = '#';

        int rowOffsets[] = {0, 1, 0, -1};
        int colOffsets[] = {1, 0, -1, 0};
        for (int d = 0; d < 4; ++d) {
            ret = this->backtrack(row + rowOffsets[d], col + colOffsets[d], word, index + 1);
            if (ret)
                break;
        }

        /* Step 4). clean up and return the result. */
        this->board[row][col] = word[index];
        return ret;
    }
};

int main() {
    Solution solution;
    std::vector<std::vector<char>> board = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };
    std::string word = "ABCCED";
    bool result = solution.exist(board, word);
    std::cout << "Existence: " << (result ? "true" : "false") << std::endl;

    return 0;
}
------------------------------------------------------------------------------------------------
/*
 word search 2
*/
// method1: techdose
class Solution {    
    struct node{    //TrieNode
        char c;
        int ends;
        string word;
        node *child[26];
    };
    struct node *getNode(char c)    //get newnode
    {
        node *newnode = new node;
        newnode->c = c;
        newnode->ends = 0;
        newnode->word = "";
        for(int i=0;i<26;++i)
            newnode->child[i] = NULL;
        return newnode;
    }
    node *root = getNode('/');  //root
    
    //Trie INSERT
    void insert(string s)
    {
        node *curr=root;
        int index,i=0;
        while(s[i])
        {
            index = s[i]-'a';
            if(curr->child[index]==NULL)
                curr->child[index] = getNode(s[i]);
            
            curr=curr->child[index];
            i+=1;
        }
        curr->ends += 1;
        curr->word = s;
    }
    
    void solve(vector<vector<char>>& board,int i,int j,int r,int c,vector<string>& ans,node *curr)
    {
        //Base case
        //If the trie doesn't have the current char OR cell is Visited
        int index = board[i][j]-'a';
        if(board[i][j]=='$' || curr->child[index]==NULL)  
            return;
        
        curr = curr->child[index];
        if(curr->ends > 0)
        {
            ans.push_back(curr->word);
            curr->ends -=1;
        }
        
        //Body
        char ch = board[i][j];   //Store current char
        board[i][j] = '$';  //Mark current node visited
        
        if(i>0)     //TOP
            solve(board,i-1,j,r,c,ans,curr);
        if(i<r-1)   //DOWN
            solve(board,i+1,j,r,c,ans,curr);
        if(j>0)     //LEFT
            solve(board,i,j-1,r,c,ans,curr);
        if(j<c-1)   //RIGHT
            solve(board,i,j+1,r,c,ans,curr);
        
        board[i][j] = ch;    //Mark current node as Unvisited by restoring the value
    }
    
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {        
        int r=board.size();
        int c=board[0].size();
        
        //Insert all words in TRIE
        for(int i=0;i<words.size();++i)
            insert(words[i]);
        
        //Now search words
        vector<string> ans;
        for(int i=0;i<r;++i)
        {
            for(int j=0;j<c;++j)
                solve(board,i,j,r,c,ans,root);
        }
        return ans;
    }
};
-------------------------
// method2: bcaktracking with trie(leetcode)
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

class TrieNode {
public:
    std::unordered_map<char, TrieNode*> children;
    std::string word;

    TrieNode() : word("") {}
};

class Solution {
private:
    std::vector<std::vector<char>> board;
    std::vector<std::string> result;

public:
    std::vector<std::string> findWords(std::vector<std::vector<char>>& board, std::vector<std::string>& words) {
        TrieNode* root = new TrieNode();

        // Step 1). Construct the Trie
        for (const std::string& word : words) {
            TrieNode* node = root;

            for (char letter : word) {
                if (node->children.find(letter) != node->children.end()) {
                    node = node->children[letter];
                } else {
                    TrieNode* newNode = new TrieNode();
                    node->children[letter] = newNode;
                    node = newNode;
                }
            }
            node->word = word;  // store words in Trie
        }

        this->board = board;
        // Step 2). Backtracking starting for each cell in the board
        for (int row = 0; row < board.size(); ++row) {
            for (int col = 0; col < board[row].size(); ++col) {
                if (root->children.find(board[row][col]) != root->children.end()) {
                    backtracking(row, col, root);
                }
            }
        }

        return this->result;
    }

private:
    void backtracking(int row, int col, TrieNode* parent) {
        char letter = this->board[row][col];
        TrieNode* currNode = parent->children[letter];

        // check if there is any match
        if (!currNode->word.empty()) {
            this->result.push_back(currNode->word);
            currNode->word = "";
        }

        // mark the current letter before the EXPLORATION
        this->board[row][col] = '#';

        // explore neighbor cells in around-clock directions: up, right, down, left
        int rowOffset[] = {-1, 0, 1, 0};
        int colOffset[] = {0, 1, 0, -1};
        for (int i = 0; i < 4; ++i) {
            int newRow = row + rowOffset[i];
            int newCol = col + colOffset[i];
            if (newRow < 0 || newRow >= this->board.size() || newCol < 0 || newCol >= this->board[0].size()) {
                continue;
            }
            if (currNode->children.find(this->board[newRow][newCol]) != currNode->children.end()) {
                backtracking(newRow, newCol, currNode);
            }
        }

        // End of EXPLORATION, restore the original letter in the board.
        this->board[row][col] = letter;

        // Optimization: incrementally remove the leaf nodes
        if (currNode->children.empty()) {
            parent->children.erase(letter);
            delete currNode;
        }
    }
};
------------------------
