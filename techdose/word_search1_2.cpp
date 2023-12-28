/*
 word search 1
*/
//method1: striver
bool searchNext(vector<vector<char>> &board, string word, int row, int col, 
    int index, int m, int n) {

        // if index reaches at the end that means we have found the word
        if (index == word.length())
            return true;

        // Checking the boundaries if the character at which we are placed is not 
        //the required character
        if (row < 0 || col < 0 || row == m || col == n || board[row][col] != 
        word[index] or board[row][col] == '!')
            return false;

        // this is to prevent reusing of the same character
        char c = board[row][col];
        board[row][col] = '!';

        // top direction
        bool top = searchNext(board, word, row - 1, col, index + 1, m, n);
        // right direction
        bool right = searchNext(board, word, row, col + 1, index + 1, m, n);
        // bottom direction
        bool bottom = searchNext(board, word, row + 1, col, index + 1, m, n);
        // left direction
        bool left = searchNext(board, word, row, col - 1, index + 1, m, n);

        board[row][col] = c; // undo change

        return top || right || bottom || left;
    }
    bool exist(vector<vector<char>> board, string word) {

        int m = board.size();
        int n = board[0].size();

        int index = 0;

        // First search the first character
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (board[i][j] == word[index]) {
                    if (searchNext(board, word, i, j, index, m, n))
                        return true;
                }
            }
        }

        return false;
    }
----------------------------
// method 2: backtarcking leetcode
class Solution {
  private char[][] board;
  private int ROWS;
  private int COLS;

  public boolean exist(char[][] board, String word) {
    this.board = board;
    this.ROWS = board.length;
    this.COLS = board[0].length;

    for (int row = 0; row < this.ROWS; ++row)
      for (int col = 0; col < this.COLS; ++col)
        if (this.backtrack(row, col, word, 0))
          return true;
    return false;
  }

  protected boolean backtrack(int row, int col, String word, int index) {
    /* Step 1). check the bottom case. */
    if (index >= word.length())
      return true;

    /* Step 2). Check the boundaries. */
    if (row < 0 || row == this.ROWS || col < 0 || col == this.COLS
        || this.board[row][col] != word.charAt(index))
      return false;

    /* Step 3). explore the neighbors in DFS */
    boolean ret = false;
    // mark the path before the next exploration
    this.board[row][col] = '#';

    int[] rowOffsets = {0, 1, 0, -1};
    int[] colOffsets = {1, 0, -1, 0};
    for (int d = 0; d < 4; ++d) {
      ret = this.backtrack(row + rowOffsets[d], col + colOffsets[d], word, index + 1);
      if (ret)
        break;
    }

    /* Step 4). clean up and return the result. */
    this.board[row][col] = word.charAt(index);
    return ret;
  }
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
class TrieNode {
  HashMap<Character, TrieNode> children = new HashMap<Character, TrieNode>();
  String word = null;
  public TrieNode() {}
}

class Solution {
  char[][] _board = null;
  ArrayList<String> _result = new ArrayList<String>();

  public List<String> findWords(char[][] board, String[] words) {

    // Step 1). Construct the Trie
    TrieNode root = new TrieNode();
    for (String word : words) {
      TrieNode node = root;

      for (Character letter : word.toCharArray()) {
        if (node.children.containsKey(letter)) {
          node = node.children.get(letter);
        } else {
          TrieNode newNode = new TrieNode();
          node.children.put(letter, newNode);
          node = newNode;
        }
      }
      node.word = word;  // store words in Trie
    }

    this._board = board;
    // Step 2). Backtracking starting for each cell in the board
    for (int row = 0; row < board.length; ++row) {
      for (int col = 0; col < board[row].length; ++col) {
        if (root.children.containsKey(board[row][col])) {
          backtracking(row, col, root);
        }
      }
    }

    return this._result;
  }
  
  private void backtracking(int row, int col, TrieNode parent) {
    Character letter = this._board[row][col];
    TrieNode currNode = parent.children.get(letter);

    // check if there is any match
    if (currNode.word != null) {
      this._result.add(currNode.word);
      currNode.word = null;
    }

    // mark the current letter before the EXPLORATION
    this._board[row][col] = '#';

    // explore neighbor cells in around-clock directions: up, right, down, left
    int[] rowOffset = {-1, 0, 1, 0};
    int[] colOffset = {0, 1, 0, -1};
    for (int i = 0; i < 4; ++i) {
      int newRow = row + rowOffset[i];
      int newCol = col + colOffset[i];
      if (newRow < 0 || newRow >= this._board.length || newCol < 0
          || newCol >= this._board[0].length) {
        continue;
      }
      if (currNode.children.containsKey(this._board[newRow][newCol])) {
        backtracking(newRow, newCol, currNode);
      }
    }

    // End of EXPLORATION, restore the original letter in the board.
    this._board[row][col] = letter;

    // Optimization: incrementally remove the leaf nodes
    if (currNode.children.isEmpty()) {
      parent.children.remove(letter);
    }
  }
}
------------------------
