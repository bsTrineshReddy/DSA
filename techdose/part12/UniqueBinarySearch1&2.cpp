// uniquebst1 : solution1
class Solution
{
public:
    int numTrees(int n)
    {
        int catalan[n + 1];
        catalan[0] = catalan[1] = 1;

        for (int i = 2; i <= n; ++i)
        {
            catalan[i] = 0;
            for (int j = 0; j < i; ++j)
                catalan[i] += catalan[j] * catalan[i - j - 1];
        }
        return catalan[n];
    }
};
-- -- -- -- -- -- -- -- -- -- -- --
// uniquebst1 : solution1: catalan solution
Cn +1 = (2(2n + 1) / n + 2) Cn;
class Solution
{
public
    int numTrees(int n)
    {
        // Note: we should use long here instead of int, otherwise overflow
        long C = 1;
        for (int i = 0; i < n; ++i)
        {
            C = C * 2 * (2 * i + 1) / (i + 2);
        }
        return (int)C;
    }
} 
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
// 2. uniquebst2

// recursive dp
class Solution
{
public:
    vector<TreeNode *> allPossibleBST(int start, int end, map<pair<int, int>, vector<TreeNode *>> &memo)
    {
        vector<TreeNode *> res;
        if (start > end)
        {
            res.push_back(nullptr);
            return res;
        }
        if (memo.find(make_pair(start, end)) != memo.end())
        {
            return memo[make_pair(start, end)];
        }
        // Iterate through all values from start to end to construct left and right subtrees recursively.
        for (int i = start; i <= end; ++i)
        {
            vector<TreeNode *> leftSubTrees = allPossibleBST(start, i - 1, memo);
            vector<TreeNode *> rightSubTrees = allPossibleBST(i + 1, end, memo);

            // Loop through all left and right subtrees and connect them to the ith root.
            for (auto left : leftSubTrees)
            {
                for (auto right : rightSubTrees)
                {
                    TreeNode *root = new TreeNode(i, left, right);
                    res.push_back(root);
                }
            }
        }
        return memo[make_pair(start, end)] = res;
    }

    vector<TreeNode *> generateTrees(int n)
    {
        map<pair<int, int>, vector<TreeNode *>> memo;
        return allPossibleBST(1, n, memo);
    }
};
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
// iterative dp
class Solution
{
public:
    vector<TreeNode *> generateTrees(int n)
    {
        vector<vector<vector<TreeNode *>>> dp(n + 1, vector(n + 1, vector<TreeNode *>(0)));
        for (int i = 1; i <= n; i++)
        {
            dp[i][i].push_back(new TreeNode(i));
        }

        for (int numberOfNodes = 2; numberOfNodes <= n; numberOfNodes++)
        {
            for (int start = 1; start <= n - numberOfNodes + 1; start++)
            {
                int end = start + numberOfNodes - 1;
                for (int i = start; i <= end; i++)
                {
                    vector<TreeNode *> leftSubtrees =
                        i - 1 >= start ? dp[start][i - 1] : vector<TreeNode *>({NULL});
                    vector<TreeNode *> rightSubtrees =
                        i + 1 <= end ? dp[i + 1][end] : vector<TreeNode *>({NULL});

                    for (auto left : leftSubtrees)
                    {
                        for (auto right : rightSubtrees)
                        {
                            TreeNode *root = new TreeNode(i, left, right);
                            dp[start][end].push_back(root);
                        }
                    }
                }
            }
        }
        return dp[1][n];
    }
};
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --

class Solution
{
    //  function for constructing trees
    vector<TreeNode *> constructTrees(int start, int end)
    {
        vector<TreeNode *> list;

        /*  if start > end   then subtree will be empty so returning NULL
            in the list */
        if (start > end)
        {
            list.push_back(NULL);
            return list;
        }

        /*  iterating through all values from start to end  for constructing\
            left and right subtree recursively  */
        for (int i = start; i <= end; i++)
        {
            /*  constructing left subtree   */
            vector<TreeNode *> leftSubtree = constructTrees(start, i - 1);

            /*  constructing right subtree  */
            vector<TreeNode *> rightSubtree = constructTrees(i + 1, end);

            /*  now looping through all left and right subtrees and connecting
                them to ith root  below  */
            for (int j = 0; j < leftSubtree.size(); j++)
            {
                TreeNode *left = leftSubtree[j];
                for (int k = 0; k < rightSubtree.size(); k++)
                {
                    TreeNode *right = rightSubtree[k];
                    TreeNode *node = new TreeNode(i); // making value i as root
                    node->left = left;                // connect left subtree
                    node->right = right;              // connect right subtree
                    list.push_back(node);             // add this tree to list
                }
            }
        }
        return list;
    }

public:
    vector<TreeNode *> generateTrees(int n)
    {

        vector<TreeNode *> totalTreesFrom1toN = constructTrees(1, n);
        return totalTreesFrom1toN;
    }
};
--------------------
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        vector<vector<TreeNode*>> dp(n + 1);
        dp[0].push_back(NULL);

        for (int numberOfNodes = 1; numberOfNodes <= n; numberOfNodes ++) {
            for (int i = 1; i <= numberOfNodes; i ++) {
                int j = numberOfNodes - i;
                for (auto left : dp[i - 1]) {
                    for (auto right : dp[j]) {
                        TreeNode* root = new TreeNode(i, left, clone(right, i));
                        dp[numberOfNodes].push_back(root);
                    }
                }
            }
        }
        return dp[n];
    }

private:
    TreeNode* clone(TreeNode* node, int offset) {
        if (node == NULL) {
            return NULL;
        }
        TreeNode* clonedNode = new TreeNode(node->val + offset);
        clonedNode->left = clone(node->left, offset);
        clonedNode->right = clone(node->right, offset);
        return clonedNode;
    }
};
-----------------------------------------------------------