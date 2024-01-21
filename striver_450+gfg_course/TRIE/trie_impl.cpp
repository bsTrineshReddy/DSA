/*
  Implement Trie
  Total 4 different types (no need to worry every methos is almost similar)
  i)Leetcode editorial
  ii)Techdose 1stmethod
  iii)Striver 1stmethod
  iv) Striver 2nd method
*/

//1) method1: leetcode editorial solution
class TrieNode {
public:
    TrieNode* links[26];
    int wordsEndingHere = 0;
    int wordsStartingHere = 0;
};

class Trie {
public:
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        TrieNode* node = root;
        for (char& w : word) {
            int charIndex = w - 'a';
            if (!node->links[charIndex]) {
                node->links[charIndex] = new TrieNode();
            }
            node = node->links[charIndex];
            node->wordsStartingHere++;
        }
        node->wordsEndingHere++;
    }

    int countWordsEqualTo(string word) {
        TrieNode* node = root;
        for (char& w : word) {
            int charIndex = w - 'a';
            if (!node->links[charIndex]) {
                return 0;
            }
            node = node->links[charIndex];
        }
        return node->wordsEndingHere;
    }

    int countWordsStartingWith(string prefix) {
        TrieNode* node = root;
        for (char& w : prefix) {
            int charIndex = w - 'a';
            if (!node->links[charIndex]) {
                return 0;
            }
            node = node->links[charIndex];
        }
        return node->wordsStartingHere;
    }

    void erase(string word) {
        TrieNode* node = root;
        for (char& w : word) {
            int charIndex = w - 'a';
            node = node->links[charIndex];
            node->wordsStartingHere--;
        }
        node->wordsEndingHere--;
    }
};
---------------------------------------------------------
/*
  2) Techdose 1st method
  CODE TO Count_Number_Of_Strings_With_Given_Prefix
  Assumption: All characters are in lowercase
*/
struct Trienode
{
  char data;
  int wc; // wc:word_count
  Trienode *child[26];
};

Trienode nodepool[100000]; // Pool of 100K Trienodes
Trienode *root;            // Root of Trie
int poolcount;             // Always points to next free Trienode

void init() // Initializer function
{
  poolcount = 0;
  root = &nodepool[poolcount++];
  root->data = '/';
  for (register int i = 0; i < 26; ++i)
    root->child[i] = NULL;
}

Trienode *getNode(char c)
{
  Trienode *newnode = &nodepool[poolcount++];
  newnode->data = c;
  for (register int i = 0; i < 26; ++i)
    newnode->child[i] = NULL;
  newnode->wc = 0;
  return newnode;
}

void insert(char *s)
{
  Trienode *curr = root;
  int index;
  for (int i = 0; s[i] != '\0'; ++i)
  {
    index = s[i] - 'a';
    if (curr->child[index] == NULL)
      curr->child[index] = getNode(s[i]);
    curr->child[index]->wc += 1;
    curr = curr->child[index];
  }
}

bool search(char *s)
{
  Trienode *curr = root;
  int index;
  for (int i = 0; s[i] != '\0'; ++i)
  {
    index = s[i] - 'a';
    if (curr->child[index] == NULL || curr->child[index]->wc == 0)
      return false;
    curr = curr->child[index];
  }
  return true;
}

bool Triedelete(char *s)
{
  if (search(s))
  {
    Trienode *curr = root;
    int index;
    for (int i = 0; s[i] != '\0'; ++i)
    {
      index = s[i] - 'a';
      curr->child[index]->wc -= 1;
      curr = curr->child[index];
    }
  }
}

int countPrefix(string s)
{
  Trienode *curr = root;
  int index;
  for (int i = 0; s[i] != '\0'; ++i)
  {
    index = s[i] - 'a';
    if (curr->child[index] == NULL || curr->child[index]->wc == 0)
      return 0; // No string with given prefix is present
    curr = curr->child[index];
  }
  return curr->wc;
}
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
/*
  3) striver method1
*/
#include <bits/stdc++.h>
using namespace std;
#define IOS                \
  ios::sync_with_stdio(0); \
  cin.tie(0);              \
  cout.tie(0);
#define endl "\n"
#define MAXN 100001
#define INF 1e18 + 1
struct Node
{
  Node *links[26];
  bool flag = false;
  // checks if the reference trie is present or not
  bool containKey(char ch)
  {
    return (links[ch - 'a'] != NULL);
  }
  // creating reference trie
  void put(char ch, Node *node)
  {
    links[ch - 'a'] = node;
  }
  // to get the next node for traversal
  Node *get(char ch)
  {
    return links[ch - 'a'];
  }
  // setting flag to true at the end of the word
  void setEnd()
  {
    flag = true;
  }
  // checking if the word is completed or not
  bool isEnd()
  {
    return flag;
  }
};
class Trie
{
private:
  Node *root;

public:
  Trie()
  {
    // creating new obejct
    root = new Node();
  }

  void insert(string word)
  {
    // initializing dummy node pointing to root initially
    Node *node = root;
    for (int i = 0; i < word.size(); i++)
    {
      if (!node->containKey(word[i]))
      {
        node->put(word[i], new Node());
      }
      // moves to reference trie
      node = node->get(word[i]);
    }
    node->setEnd();
  }

  bool search(string word)
  {
    Node *node = root;
    for (int i = 0; i < word.size(); i++)
    {
      if (!node->containKey(word[i]))
      {
        return false;
      }
      node = node->get(word[i]);
    }
    return node->isEnd();
  }

  bool startsWith(string prefix)
  {
    Node *node = root;
    for (int i = 0; i < prefix.size(); i++)
    {
      if (!node->containKey(prefix[i]))
      {
        return false;
      }
      node = node->get(prefix[i]);
    }
    return true;
  }
};
---------------------------------------------------------------------------------------------------------------------
/*
  4) striver method2
*/
#include <bits/stdc++.h>
using namespace std;
struct Node
{
  Node *links[26];
  int cntEndWith = 0;
  int cntPrefix = 0;

  bool containsKey(char ch)
  {
    return (links[ch - 'a'] != NULL);
  }
  Node *get(char ch)
  {
    return links[ch - 'a'];
  }
  void put(char ch, Node *node)
  {
    links[ch - 'a'] = node;
  }
  void increaseEnd()
  {
    cntEndWith++;
  }
  void increasePrefix()
  {
    cntPrefix++;
  }
  void deleteEnd()
  {
    cntEndWith--;
  }
  void reducePrefix()
  {
    cntPrefix--;
  }
  int getEnd()
  {
    return cntEndWith;
  }
  int getPrefix()
  {
    return cntPrefix;
  }
};
class Trie
{
private:
  Node *root;

public:
  /** Initialize your data structure here. */
  Trie()
  {
    root = new Node();
  }

  /** Inserts a word into the trie. */
  void insert(string word)
  {
    Node *node = root;
    for (int i = 0; i < word.length(); i++)
    {
      if (!node->containsKey(word[i]))
      {
        node->put(word[i], new Node());
      }
      node = node->get(word[i]);
      node->increasePrefix();
    }
    node->increaseEnd();
  }

  int countWordsEqualTo(string &word)
  {
    Node *node = root;
    for (int i = 0; i < word.length(); i++)
    {
      if (node->containsKey(word[i]))
      {
        node = node->get(word[i]);
      }
      else
      {
        return 0;
      }
    }
    return node->getEnd();
  }

  int countWordsStartingWith(string &word)
  {
    Node *node = root;
    for (int i = 0; i < word.length(); i++)
    {
      if (node->containsKey(word[i]))
      {
        node = node->get(word[i]);
      }
      else
      {
        return 0;
      }
    }
    return node->getPrefix();
  }

  void erase(string &word)
  {
    Node *node = root;
    for (int i = 0; i < word.length(); i++)
    {
      if (node->containsKey(word[i]))
      {
        node = node->get(word[i]);
        node->reducePrefix();
      }
      else
      {
        return;
      }
    }
    node->deleteEnd();
  }
};

int main()
{
  Trie T;
  T.insert("apple");
  T.insert("apple");
  T.insert("apps");
  T.insert("apps");
  string word1 = "apps";
  cout << "Count Words Equal to " << word1 << " " << T.countWordsEqualTo(word1) << endl;
  string word2 = "abc";
  cout << "Count Words Equal to " << word2 << " " << T.countWordsEqualTo(word2) << endl;
  string word3 = "ap";
  cout << "Count Words Starting With " << word3 << " " << T.countWordsStartingWith(word3)
       << endl;
  string word4 = "appl";
  cout << "Count Words Starting With " << word4 << " " << T.countWordsStartingWith(word4)
       << endl;
  T.erase(word1);
  cout << "Count Words equal to " << word1 << " " << T.countWordsEqualTo(word1) << endl;
  return 0;
}
------------------------------------------------------------------------