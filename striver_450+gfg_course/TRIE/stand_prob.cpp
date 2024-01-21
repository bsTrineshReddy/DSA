/*
1) Number of Distinct Substrings in a String : STRIVER ATOZ SHEET

Problem Statement: Given a string of alphabetic characters. Return the count of distinct
substrings of the string(including the empty string) using the Trie data structure

Time Complexity: O(n^2)
Space Complexity: O(n^2)
*/
#include <iostream>

using namespace std;

struct Node
{
  Node *links[26];

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
};

int countDistinctSubstrings(string &s)
{
  Node *root = new Node();
  int count = 0;
  int n = s.size();
  for (int i = 0; i < n; i++)
  {
    Node *node = root;

    for (int j = i; j < n; j++)
    {
      if (!node->containsKey(s[j]))
      {
        node->put(s[j], new Node());
        count++;
      }
      node = node->get(s[j]);
    }
  }
  return count + 1;
}

int main()
{
  string s1 = "ababa";
  cout << "Total number of distinct substrings : " << countDistinctSubstrings(s1);
  cout << "\n";

  string s2 = "ccfdf";
  cout << "Total number of distinct substrings : " << countDistinctSubstrings(s2);

  return 0;
}
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -
/*
2) Maximum XOR of Two Numbers in an Array (striver atoz problem)
Input: N=2, M=3
       arr1 = [6, 8]
       arr2 = [7, 8, 2]

Output: 15

Explanation: Possible pairs are (6, 7), (6, 8),
(6, 2), (8, 7), (8, 8), (6, 2). And 8 xor 7 will give the maximum result i.e. 15

Time Complexity: O(N*32) + O(M*32)
Space Complexity: O(N*32)
*/
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct Node
{
  Node *links[2];

  bool containsKey(int ind)
  {
    return (links[ind] != NULL);
  }
  Node *get(int ind)
  {
    return links[ind];
  }
  void put(int ind, Node *node)
  {
    links[ind] = node;
  }
};
class Trie
{
private:
  Node *root;

public:
  Trie()
  {
    root = new Node();
  }

public:
  void insert(int num)
  {
    Node *node = root;
    // cout << num << endl;
    for (int i = 31; i >= 0; i--)
    {
      int bit = (num >> i) & 1;
      if (!node->containsKey(bit))
      {
        node->put(bit, new Node());
      }
      node = node->get(bit);
    }
  }

public:
  int findMax(int num)
  {
    Node *node = root;
    int maxNum = 0;
    for (int i = 31; i >= 0; i--)
    {
      int bit = (num >> i) & 1;
      if (node->containsKey(!bit))
      {
        maxNum = maxNum | (1 << i);
        node = node->get(!bit);
      }
      else
      {
        node = node->get(bit);
      }
    }
    return maxNum;
  }
};
int maxXOR(int n, int m, vector<int> &arr1, vector<int> &arr2)
{
  Trie trie;
  for (int i = 0; i < n; i++)
  {
    trie.insert(arr1[i]);
  }
  int maxi = 0;
  for (int i = 0; i < m; i++)
  {
    maxi = max(maxi, trie.findMax(arr2[i]));
  }
  return maxi;
}
int main()
{
  vector<int> arr1 = {6, 8};
  vector<int> arr2 = {7, 8, 2};
  int n = 2, m = 3;
  cout << maxXOR(n, m, arr1, arr2) << endl;
  return 0;
}
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
// method2: Techdose solution
class Solution
{
#define N 2
  struct trienode
  {
    int number;
    trienode *child[N];
    trienode()
    {
      for (int i = 0; i < N; ++i)
        child[i] = NULL;
    }
  };
  trienode *root;
  void TrieInsert(const int &no, const string &s)
  {
    trienode *curr = root;
    int idx;
    for (int i = 0; s[i] != '\0'; ++i)
    {
      idx = s[i] == '0' ? 0 : 1;
      if (!curr->child[idx])
        curr->child[idx] = new trienode();
      curr = curr->child[idx];
    }
    curr->number = no;
  }
  int searchMaxInTrie(string candidate)
  {
    trienode *curr = root;
    int idx;
    for (int i = 0; candidate[i] != '\0'; ++i)
    {
      idx = candidate[i] == '0' ? 1 : 0;
      if (curr->child[idx])
      {
        curr = curr->child[idx];
      }
      else
      {
        curr = curr->child[!idx];
      }
    }
    return curr->number;
  }
  string convert2string(int num, int size)
  {
    string s;
    int len = 0;
    while (num)
    {
      if (num % 2 == 0)
        s.push_back('0');
      else
        s.push_back('1');
      len += 1;
      num /= 2;
    }
    for (; len < size; ++len)
      s.push_back('0');
    reverse(s.begin(), s.end());
    return s;
  }
  void Int2String(vector<int> &nums, vector<string> &nos)
  {
    int maxNo = *max_element(nums.begin(), nums.end());
    int size = maxNo >= 1 ? log2(maxNo) + 1 : 1;
    for (int num : nums)
      nos.push_back(convert2string(num, size));
  }

public:
  int findMaximumXOR(vector<int> &nums)
  {
    root = new trienode(); // Initialize Trie

    vector<string> nos;
    Int2String(nums, nos);
    // cout<<"All strings\n";
    for (int i = 0; i < nums.size(); ++i)
    {
      //    cout<<nums[i]<<": "<<nos[i]<<"\n";
      TrieInsert(nums[i], nos[i]);
    }

    int maxXOR = 0;
    for (int i = 0; i < nums.size(); ++i)
      maxXOR = max(maxXOR, nums[i] ^ searchMaxInTrie(nos[i]));
    return maxXOR;
  }
};
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -

/*
3) Maximum Xor Queries | Trie : striver ato z sheet

You are given an array/list ‘ARR’ consisting of ‘N’ non-negative integers.
You are also given a list ‘QUERIES’ consisting of ‘M’ queries, where the ‘i-th’ query
is a list/array of two non-negative integers ‘Xi’, ‘Ai’, i.e ‘QUERIES[i]’ = [‘Xi’, ‘Ai’].

The answer to the ith query, i.e ‘QUERIES[i]’ is the maximum bitwise xor value of ‘Xi’
 with any integer less than or equal to ‘Ai’ in ‘ARR’.

You should return an array/list consisting of ‘N’ integers where the ‘i-th’ integer
is the answer of ‘QUERIES[i]’.

Time Complexity:O(M) + O(MlogM) + O(M*32 + N*32)
space : o(32)*N
*/

#include <bits/stdc++.h>

using namespace std;

struct Node
{
  Node *links[2];

  bool containsKey(int ind)
  {
    return (links[ind] != NULL);
  }
  Node *get(int ind)
  {
    return links[ind];
  }
  void put(int ind, Node *node)
  {
    links[ind] = node;
  }
};
class Trie
{
private:
  Node *root;

public:
  Trie()
  {
    root = new Node();
  }

public:
  void insert(int num)
  {
    Node *node = root;
    // cout << num << endl;
    for (int i = 31; i >= 0; i--)
    {
      int bit = (num >> i) & 1;
      if (!node->containsKey(bit))
      {
        node->put(bit, new Node());
      }
      node = node->get(bit);
    }
  }

public:
  int findMax(int num)
  {
    Node *node = root;
    int maxNum = 0;
    for (int i = 31; i >= 0; i--)
    {
      int bit = (num >> i) & 1;
      if (node->containsKey(!bit))
      {
        maxNum = maxNum | (1 << i);
        node = node->get(!bit);
      }
      else
      {
        node = node->get(bit);
      }
    }
    return maxNum;
  }
};
vector<int> maxXorQueries(vector<int> &arr, vector<vector<int>> &queries)
{
  vector<int> ans(queries.size(), 0);
  vector<pair<int, pair<int, int>>> offlineQueries;
  sort(arr.begin(), arr.end());
  int index = 0;
  for (auto &it : queries)
  {
    offlineQueries.push_back({it[1],
                              {it[0],
                               index++}});
  }
  sort(offlineQueries.begin(), offlineQueries.end());
  int i = 0;
  int n = arr.size();
  Trie trie;

  for (auto &it : offlineQueries)
  {
    while (i < n && arr[i] <= it.first)
    {
      trie.insert(arr[i]);
      i++;
    }
    if (i != 0)
      ans[it.second.second] = trie.findMax(it.second.first);
    else
      ans[it.second.second] = -1;
  }
  return ans;
}
int main()
{
  int t;
  cin >> t;
  while (t--)
  {
    int n, m;
    cin >> n >> m;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
      cin >> arr[i];
    }
    vector<vector<int>> queries;

    for (int i = 0; i < m; i++)
    {
      vector<int> temp;
      int xi, ai;
      cin >> xi >> ai;
      temp.push_back(xi);
      temp.push_back(ai);
      queries.push_back(temp);
    }

    vector<int> ans = maxXorQueries(arr, queries);
    for (int j = 0; j < ans.size(); j++)
    {
      cout << ans[j] << " ";
    }
    cout << endl;
  }
}
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -
