// uniquebst1 : solution1
public class Solution {
  public int numTrees(int n) {
    int[] G = new int[n + 1];
    G[0] = 1;
    G[1] = 1;

    for (int i = 2; i <= n; ++i) {
      for (int j = 1; j <= i; ++j) {
        G[i] += G[j - 1] * G[i - j];
      }
    }
    return G[n];
  }
}

// uniquebst1 : solution1: catalan solution
class Solution {
  public int numTrees(int n) {
    // Note: we should use long here instead of int, otherwise overflow
    long C = 1;
    for (int i = 0; i < n; ++i) {
      C = C * 2 * (2 * i + 1) / (i + 2);
    }
    return (int) C;
  }
}
----------------------------------------------------------------------------
// 2. uniquebst2

// recursive dp
class Solution {
public:
    vector<TreeNode*> allPossibleBST(int start, int end, map<pair<int, int>, vector<TreeNode*>>& memo) {
        vector<TreeNode*> res;
        if (start > end) {
            res.push_back(nullptr);
            return res;
        }
        if (memo.find(make_pair(start, end)) != memo.end()) {
            return memo[make_pair(start, end)];
        }
        // Iterate through all values from start to end to construct left and right subtrees recursively.
        for (int i = start; i <= end; ++i) {
            vector<TreeNode*> leftSubTrees = allPossibleBST(start, i - 1, memo);
            vector<TreeNode*> rightSubTrees = allPossibleBST(i + 1, end, memo);

            // Loop through all left and right subtrees and connect them to the ith root.
            for (auto left: leftSubTrees) {
                for (auto right: rightSubTrees) {
                    TreeNode* root = new TreeNode(i, left, right);
                    res.push_back(root);
                }
            }
        }
        return memo[make_pair(start, end)] = res;
    }

    vector<TreeNode*> generateTrees(int n) {
        map<pair<int, int>, vector<TreeNode*>> memo;
        return allPossibleBST(1, n, memo);
    }
};
----------------------------------
// iterative dp
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        vector<vector<vector<TreeNode*>>> dp(n + 1, vector(n + 1, vector<TreeNode*>(0)));
        for (int i = 1; i <= n; i++) {
            dp[i][i].push_back(new TreeNode(i));
        }

        for (int numberOfNodes = 2; numberOfNodes <= n; numberOfNodes++) {
            for (int start = 1; start <= n - numberOfNodes + 1; start++) {
                int end = start + numberOfNodes - 1;
                for (int i = start; i <= end; i++) {
                    vector<TreeNode*> leftSubtrees =
                        i - 1 >= start ? dp[start][i - 1] : vector<TreeNode*>({NULL});
                    vector<TreeNode*> rightSubtrees =
                        i + 1 <= end ? dp[i + 1][end] : vector<TreeNode*>({NULL});

                    for (auto left : leftSubtrees) {
                        for (auto right : rightSubtrees) {
                            TreeNode* root = new TreeNode(i, left, right);
                            dp[start][end].push_back(root);
                        }
                    }
                }
            }
        }
        return dp[1][n];
    }
};
----------------------------------------------------------------------------