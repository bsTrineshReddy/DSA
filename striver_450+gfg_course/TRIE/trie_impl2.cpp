/*
    auto complete faeture
*/

#include<bits/stdc++.h> 
using namespace std; 

// Alphabet size (# of symbols) 
#define ALPHABET_SIZE (26) 

// Converts key current character into index 
// use only 'a' through 'z' and lower case 
#define CHAR_TO_INDEX(c) ((int)c - (int)'a') 

// trie node 
struct TrieNode 
{ 
	struct TrieNode *children[ALPHABET_SIZE]; 

	// isWordEnd is true if the node represents 
	// end of a word 
	bool isWordEnd; 
}; 

// Returns new trie node (initialized to NULLs) 
struct TrieNode *getNode(void) 
{ 
	struct TrieNode *pNode = new TrieNode; 
	pNode->isWordEnd = false; 

	for (int i = 0; i < ALPHABET_SIZE; i++) 
		pNode->children[i] = NULL; 

	return pNode; 
} 

// If not present, inserts key into trie. If the 
// key is prefix of trie node, just marks leaf node 
void insert(struct TrieNode *root, const string key) 
{ 
	struct TrieNode *pCrawl = root; 

	for (int level = 0; level < key.length(); level++) 
	{ 
		int index = CHAR_TO_INDEX(key[level]); 
		if (!pCrawl->children[index]) 
			pCrawl->children[index] = getNode(); 

		pCrawl = pCrawl->children[index]; 
	} 

	// mark last node as leaf 
	pCrawl->isWordEnd = true; 
} 

// Returns true if key presents in trie, else false 
bool search(struct TrieNode *root, const string key) 
{ 
	int length = key.length(); 
	struct TrieNode *pCrawl = root; 
	for (int level = 0; level < length; level++) 
	{ 
		int index = CHAR_TO_INDEX(key[level]); 

		if (!pCrawl->children[index]) 
			return false; 

		pCrawl = pCrawl->children[index]; 
	} 

	return (pCrawl != NULL && pCrawl->isWordEnd); 
} 

// Returns 0 if current node has a child 
// If all children are NULL, return 1. 
bool isLastNode(struct TrieNode* root) 
{ 
	for (int i = 0; i < ALPHABET_SIZE; i++) 
		if (root->children[i]) 
			return 0; 
	return 1; 
} 

// Recursive function to print auto-suggestions for given 
// node. 
void suggestionsRec(struct TrieNode* root, string currPrefix) 
{ 
	// found a string in Trie with the given prefix 
	if (root->isWordEnd) 
	{ 
		cout << currPrefix; 
		cout << endl; 
	} 

	// All children struct node pointers are NULL 
	if (isLastNode(root)) 
		return; 

	for (int i = 0; i < ALPHABET_SIZE; i++) 
	{ 
		if (root->children[i]) 
		{ 
			// append current character to currPrefix string 
			currPrefix.push_back(97 + i); 

			// recur over the rest 
			suggestionsRec(root->children[i], currPrefix); 
		} 
	} 
} 

// print suggestions for given query prefix. 
int printAutoSuggestions(TrieNode* root, const string query) 
{ 
	struct TrieNode* pCrawl = root; 

	// Check if prefix is present and find the 
	// the node (of last level) with last character 
	// of given string. 
	int level; 
	int n = query.length(); 
	for (level = 0; level < n; level++) 
	{ 
		int index = CHAR_TO_INDEX(query[level]); 

		// no string in the Trie has this prefix 
		if (!pCrawl->children[index]) 
			return 0; 

		pCrawl = pCrawl->children[index]; 
	} 

	// If prefix is present as a word. 
	bool isWord = (pCrawl->isWordEnd == true); 

	// If prefix is last node of tree (has no 
	// children) 
	bool isLast = isLastNode(pCrawl); 

	// If prefix is present as a word, but 
	// there is no subtree below the last 
	// matching node. 
	if (isWord && isLast) 
	{ 
		cout << query << endl; 
		return -1; 
	} 

	// If there are are nodes below last 
	// matching character. 
	if (!isLast) 
	{ 
		string prefix = query; 
		suggestionsRec(pCrawl, prefix); 
		return 1; 
	} 
} 

// Driver Code 
int main() 
{ 
	struct TrieNode* root = getNode(); 
	insert(root, "hello"); 
	insert(root, "dog"); 
	insert(root, "hell"); 
	insert(root, "cat"); 
	insert(root, "a"); 
	insert(root, "hel"); 
	insert(root, "help"); 
	insert(root, "helps"); 
	insert(root, "helping"); 
	int comp = printAutoSuggestions(root, "hel"); 

	if (comp == -1) 
		cout << "No other strings found with this prefix\n"; 

	else if (comp == 0) 
		cout << "No string found with this prefix\n"; 

	return 0; 
} 
-----------------------------------------------------------------------
/*
   Add and Search Word - Data structure design
*/
class WordDictionary {
    struct node {
        char c;
        int end;
        node *child[26];
    };
    node *getNode(char c)
    {
        node *newnode=new node;
        newnode->c = c;
        newnode->end = 0;
        for(int i=0;i<26;++i)
            newnode->child[i] = NULL;
        return newnode;
    }
    node *root = getNode('/');
    
    void Trie_insert(string s)
    {
        int index;
        int i=0;
        node *curr = root;
        while(s[i])
        {
            index = s[i]-'a';
            if(!curr->child[index])
                curr->child[index] = getNode(s[i]);
            curr = curr->child[index];
            ++i;
        }
        curr->end +=1;
    }
    
    bool Trie_search(string s,node *curr,int pos,int n)
    {        
        if(s[pos]=='.')
        {
            bool res = false;
            node *current = curr;
            for(int i=0;i<26;++i)
            {
                if(pos==n-1 && curr->child[i])
                {
                    current=curr->child[i];
                    res |= current->end>0?true:false;
                }
                else if(curr->child[i] && Trie_search(s,curr->child[i],pos+1,n))
                    return true;
            }
            return res;
        }
        else if(curr->child[s[pos]-'a'])
        {
            if(pos==n-1)
            {
                curr = curr->child[s[pos]-'a'];
                return curr->end>0?true:false;
            }
            return Trie_search(s,curr->child[s[pos]-'a'],pos+1,n);
        }
        return false;
    }
public:
    /** Initialize your data structure here. */
    WordDictionary() {
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        Trie_insert(word);
    }
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        return Trie_search(word,root,0,word.size());
    }
};

static const auto io_sync_off = []()
{
    // turn off sync
    std::ios::sync_with_stdio(false);
    // untie in/out streams
    std::cin.tie(nullptr);
    return nullptr;
}();
/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */

--------------------------------------------------------------------------------------------
/*
 longest duplicate substring
*/
#define p 10000007
//#define lli long long int

vector<int> roll;

class Solution {
    bool match(string s,int len,int size,string& ans)
    {
        unordered_map<int,vector<int>> m;   //Key->hashValue...Value->starting index of substring
        int hash=0;   //curr window hash
        for(int i=0;i<size;++i)
            hash = (hash*26 + (s[i]-'a'))%p;
        
        m[hash].push_back(0);
        //Rolling hash (sliding window)
        for(int j=size;j<len;++j)
        {
            hash = ((hash-roll[size-1]*(s[j-size]-'a'))%p + p)%p;
            hash = (hash*26 + (s[j]-'a'))%p;
            if(m.find(hash)!=m.end())
            {
                for(auto start: m[hash])
                {
                    string temp = s.substr(start,size);
                    string curr = s.substr(j-size+1,size);
                    if(temp.compare(curr)==0)
                    {
                        ans = temp;
                        return true;
                    }
                }
            }           
            m[hash].push_back(j-size+1);
        }
        return false;
    }

public:
    string longestDupSubstring(string S) {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        
        int len = S.size();
        if(len==0)
            return "";
        
        // Store all rolling hash values
        roll.resize(len);  // Allocating fixed space to array
        roll[0] = 1;    //Since 26^0 = 1
        for(int i=1;i<len;++i)
            roll[i] = (26*roll[i-1])%p;
        
        int low=1,high=len,mid;
        string ans = "",temp;
        while(low<=high)
        {
            temp="";
            mid = low+(high-low)/2;
            bool flag = match(S,len,mid,temp);
            if(flag)
            {
                if(temp.size()>ans.size())
                    ans=temp;
                low = mid+1;
            }
            else
                high = mid-1;
        }
        return ans;
    }
};
--------------------------------------------------------------------------------------------
