// method1: dp  time o(mn) space : O(mn) (leetcode)
class Solution {
public:
    int inf = INT_MAX;
    vector<vector<int>> dp;
    int rows, cols;

    int getMinHealth(int currCell, int nextRow, int nextCol) {
        if (nextRow >= this->rows || nextCol >= this->cols)
            return inf;
        int nextCell = this->dp[nextRow][nextCol];
        // hero needs at least 1 point to survive
        return max(1, nextCell - currCell);
    }

    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        this->rows = dungeon.size();
        this->cols = dungeon[0].size();
        this->dp = vector<vector<int>>(rows, vector<int>(cols, inf));

        int currCell, rightHealth, downHealth, nextHealth, minHealth;
        for (int row = this->rows - 1; row >= 0; --row) {
            for (int col = this->cols - 1; col >= 0; --col) {
                currCell = dungeon[row][col];

                rightHealth = getMinHealth(currCell, row, col + 1);
                downHealth = getMinHealth(currCell, row + 1, col);
                nextHealth = min(rightHealth, downHealth);

                if (nextHealth != inf) {
                    minHealth = nextHealth;
                } else {
                    minHealth = currCell >= 0 ? 1 : 1 - currCell;
                }
                this->dp[row][col] = minHealth;
            }
        }
        return this->dp[0][0];
    }
};
=====================
// method2: circularqueue to reduce spacecomplexity to N (leetcode)
class MyCircularQueue {
public:
    int capacity;
    int tailIndex;
    vector<int> queue;

    MyCircularQueue(int capacity) {
        this->queue = vector<int>(capacity);
        this->tailIndex = 0;
        this->capacity = capacity;
    }

    void enQueue(int value) {
        this->queue[this->tailIndex] = value;
        this->tailIndex = (this->tailIndex + 1) % this->capacity;
    }

    int get(int index) {
        return this->queue[index % this->capacity];
    }
};

class Solution {
public:
    int inf = INT_MAX;
    MyCircularQueue dp;
    int rows, cols;

    int getMinHealth(int currCell, int nextRow, int nextCol) {
        if (nextRow < 0 || nextCol < 0)
            return inf;

        int index = cols * nextRow + nextCol;
        int nextCell = this->dp.get(index);
        // hero needs at least 1 point to survive
        return max(1, nextCell - currCell);
    }

    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        this->rows = dungeon.size();
        this->cols = dungeon[0].size();
        this->dp = MyCircularQueue(this->cols);

        int currCell, rightHealth, downHealth, nextHealth, minHealth;
        for (int row = 0; row < this->rows; ++row) {
            for (int col = 0; col < this->cols; ++col) {
                currCell = dungeon[rows - row - 1][cols - col - 1];

                rightHealth = getMinHealth(currCell, row, col - 1);
                downHealth = getMinHealth(currCell, row - 1, col);
                nextHealth = min(rightHealth, downHealth);

                if (nextHealth != inf) {
                    minHealth = nextHealth;
                } else {
                    minHealth = currCell >= 0 ? 1 : 1 - currCell;
                }
                this->dp.enQueue(minHealth);
            }
        }

        // retrieve the last element in the queue
        return this->dp.get(this->cols - 1);
    }
};
=========================
