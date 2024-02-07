// 3 methods, 1.Merge sort 2.Segment Tree 3.Binary Indexed Tree
// method1: merge sort
class Solution {
    vector<int> smaller;
    vector<int> larger;

public:
    int createSortedArray(vector<int>& instructions) {
        int n = instructions.size();
        smaller.resize(n);
        larger.resize(n);
        // Note: raw array used here
        int temp[n][2]; // record some temporal information
        long cost = 0;
        long MOD = 1000000007;

        int arrSmaller[n][2];
        int arrLarger[n][2];

        for (int i = 0; i < n; i++) {
            arrSmaller[i][0] = instructions[i];
            arrSmaller[i][1] = i;
            arrLarger[i][0] = instructions[i];
            arrLarger[i][1] = i;
            smaller[i] = 0;
            larger[i] = 0;
        }

        sortSmaller(arrSmaller, 0, n - 1, temp);
        sortLarger(arrLarger, 0, n - 1, temp);

        for (int i = 0; i < n; i++) {
            cost += min(smaller[i], larger[i]);
            cost %= MOD;
        }
        return (int)(cost % MOD);
    }

    void sortSmaller(int arr[][2], int left, int right, int temp[][2]) {
        if (left == right) {
            return;
        }
        int mid = (left + right) / 2;
        sortSmaller(arr, left, mid, temp);
        sortSmaller(arr, mid + 1, right, temp);
        mergeSmaller(arr, left, right, mid, temp);
    }

    void mergeSmaller(int arr[][2], int left, int right, int mid,
                      int temp[][2]) {
        // merge [left, mid] and [mid+1, right]
        int i = left;
        int j = mid + 1;
        int k = left;
        // use temp[left...right] to temporarily store sorted array
        while (i <= mid && j <= right) {
            if (arr[i][0] < arr[j][0]) {
                temp[k][0] = arr[i][0];
                temp[k][1] = arr[i][1];
                k++;
                i++;
            } else {
                temp[k][0] = arr[j][0];
                temp[k][1] = arr[j][1];
                k++;
                smaller[arr[j][1]] += i - left;
                j++;
            }
        }
        while (i <= mid) {
            temp[k][0] = arr[i][0];
            temp[k][1] = arr[i][1];
            k++;
            i++;
        }
        while (j <= right) {
            temp[k][0] = arr[j][0];
            temp[k][1] = arr[j][1];
            k++;
            smaller[arr[j][1]] += i - left;
            j++;
        }
        // restore from temp
        for (i = left; i <= right; i++) {
            arr[i][0] = temp[i][0];
            arr[i][1] = temp[i][1];
        }
    }

    void sortLarger(int arr[][2], int left, int right, int temp[][2]) {
        if (left == right) {
            return;
        }
        int mid = (left + right) / 2;
        sortLarger(arr, left, mid, temp);
        sortLarger(arr, mid + 1, right, temp);
        mergeLarger(arr, left, right, mid, temp);
    }

    void mergeLarger(int arr[][2], int left, int right, int mid,
                     int temp[][2]) {
        // merge [left, mid] and [mid+1, right]
        int i = left;
        int j = mid + 1;
        int k = left;
        // use temp[left...right] to temporarily store sorted array
        while (i <= mid && j <= right) {
            if (arr[i][0] <= arr[j][0]) {
                temp[k][0] = arr[i][0];
                temp[k][1] = arr[i][1];
                k++;
                i++;
            } else {
                temp[k][0] = arr[j][0];
                temp[k][1] = arr[j][1];
                k++;
                larger[arr[j][1]] += mid - i + 1;
                j++;
            }
        }
        while (i <= mid) {
            temp[k][0] = arr[i][0];
            temp[k][1] = arr[i][1];
            k++;
            i++;
        }
        while (j <= right) {
            temp[k][0] = arr[j][0];
            temp[k][1] = arr[j][1];
            k++;
            larger[arr[j][1]] += mid - i + 1;
            j++;
        }
        // restore from temp
        for (i = left; i <= right; i++) {
            arr[i][0] = temp[i][0];
            arr[i][1] = temp[i][1];
        }
    }
};
-------------------------------------
// method2: segment tree
class Solution {
public:
    int createSortedArray(vector<int>& instructions) {
        int size = (int)1e5 + 1;
        //  vector<int> tree(size * 2);
        int x = (int)(ceil(log2(size))); 
        // Maximum size of segment tree 
	    int max_size = 2*(int)pow(2, x) - 1; 
        vector<int> tree(max_size);

        long cost = 0;
        long MOD = (int)1e9 + 7;
        for (int x : instructions) {
            cost += min(query(tree, 0,size-1, 0, x-1, 0), 
                        query(tree, 0,size-1, x+1, size-1, 0));
            update(tree, 0, size-1,x, 1,0);
        }
        return (int)(cost % MOD);
    }

    void update(vector<int>&tree, int ss, int se, int i, int diff, int si) 
{ 
	// Base Case: If the input index lies outside the range of 
	// this segment 
	if (i < ss || i > se) 
		return; 

	// If the input index is in range of this node, then update 
	// the value of the node and its children 
	tree[si] = tree[si] + diff; 
	if (se != ss) 
	{ 
		int mid = ss + (se-ss)/2;
		update(tree, ss, mid, i, diff, 2*si + 1); 
		update(tree, mid+1, se, i, diff, 2*si + 2); 
	} 
} 


    int query(vector<int>&tree, int ss, int se, int qs, int qe, int si) 
    { 
	// If segment of this node is a part of given range, then return 
	// the sum of the segment 
	if (qs <= ss && qe >= se) 
		return tree[si]; 

	// If segment of this node is outside the given range 
	if (se < qs || ss > qe) 
		return 0; 

	// If a part of this segment overlaps with the given range 
	int mid = ss + (se-ss)/2; 
	return query(tree, ss, mid, qs, qe, 2*si+1) + 
		query(tree, mid+1, se, qs, qe, 2*si+2); 
    } 
};
------------------------------
// method3: binary indexed tree
class Solution {
public:
    int createSortedArray(vector<int>& instructions) {
        int m = 100002;
        vector<int> bit(m);
        long cost = 0;
        long MOD = 1000000007;
        int n = instructions.size();

        for (int i = 0; i < n; i++) {
            int leftCost = query(instructions[i] - 1, bit);
            int rightCost = i - query(instructions[i], bit);
            cost += min(leftCost, rightCost);
            update(instructions[i], 1, bit, m);
        }
        return (int)(cost % MOD);
    }

    // implement Binary Index Tree
    void update(int index, int value, vector<int>& bit, int m) {
        index++;
        while (index < m) {
            bit[index] += value;
            index += index & -index;
        }
    }

    int query(int index, vector<int>& bit) {
        index++;
        int result = 0;
        while (index >= 1) {
            result += bit[index];
            index -= index & -index;
        }
        return result;
    }
};
-------------------------------------