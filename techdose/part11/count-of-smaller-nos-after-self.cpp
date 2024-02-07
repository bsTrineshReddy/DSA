// 4 methods
// 1. merge sort
// 2. BST (iterate from last and keep inserting into BST)
// 3. segment tree
// 4. Binary Indexed Tree
--------------------------
// method 1: merge sort
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n);
        vector<int> indices(n);  // record the index. we are going to sort this array
        for (int i = 0; i < n; i++) {
            indices[i] = i;
        }
        // sort indices with their corresponding values in nums, i.e., nums[indices[i]]
        mergeSort(indices, 0, n-1, result, nums);
        return result;
    }

    void mergeSort(vector<int>& indices, int left, int right, vector<int>& result,
                   vector<int>& nums) {
        if(left>=right)return;
        int mid = (left + right) / 2;
        mergeSort(indices, left, mid, result, nums);
        mergeSort(indices, mid+1, right, result, nums);
        merge(indices, left, right, mid, result, nums);
    }

    void merge(vector<int>& indices, int left, int right, int mid, vector<int>& result,
               vector<int>& nums) {
        // merge [left, mid] and [mid+1, right]
        int i = left;  // current index for the left array
        int j = mid+1;   // current index for the right array
        // use temp to temporarily store sorted array
        vector<int> temp;
        while (i <= mid && j <= right) {
            if (nums[indices[i]] <= nums[indices[j]]) {
                // j - mid -1 numbers jump to the left side of indices[i]
                result[indices[i]] += j - mid-1;
                temp.push_back(indices[i]);
                i++;
            } else {
                temp.push_back(indices[j]);
                j++;
            }
        }
        // when one of the subarrays is empty
        while (i <= mid) {
            // j - mid -1 numbers jump to the left side of indices[i]
            result[indices[i]] += j - mid-1;
            temp.push_back(indices[i]);
            i++;
        }
        while (j <= right) {
            temp.push_back(indices[j]);
            j++;
        }
        // restore from temp
        move(temp.begin(), temp.end(), indices.begin() + left);
    }
};
--------------------------------
// method 2: BST (timellinit exceeded) as in set(BST) if it is not height balanced it takes o(n) time to find lower_bound
vector<int> countSmaller(vector<int>& nums) {
      int count = 0;
      int n = nums.size();
      vector <int> res(n,0);
      multiset<int> s;

        for (int i = n-1; i>=0; i--) {
            auto it = s.lower_bound(nums[i]);
            if(it != s.end()){

                int dist = std::distance(s.begin(), it);
                res[i]+=dist;
            }
            else {
                res[i]+= s.size();

            }
            s.insert(nums[i]);
        }
     
        return res;
    }
----------------------------------------------
// method2: segment tree
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int offset = 1e4;        // offset negative to non-negative
        int size = 2 * 1e4 + 1;  // total possible values in nums
        int x = (int)(ceil(log2(size))); 
        // Maximum size of segment tree 
	    int max_size = 2*(int)pow(2, x) - 1; 
        vector<int> tree(max_size, 0);
        vector<int> result;

        for (int i = nums.size() - 1; i >= 0; i--) {
            int smaller_count = query(tree, 0,size-1, 0, nums[i] + offset-1, 0);
            result.push_back(smaller_count);
            update(tree, 0, size-1,nums[i] + offset, 1,0);
        }
        reverse(result.begin(), result.end());
        return result;
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
----------------------------------------------

// method3: Fenwick Tree
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        // -104 <= nums[i] <= 104
        int offset = 1e4;        // offset negative to non-negative
        int size = 2 * 1e4 + 2;  // total possible values in nums plus one dummy
        vector<int> tree(size);
        vector<int> result;

        for (int i = nums.size() - 1; i >= 0; i--) {
            int smaller_count = query(nums[i] + offset-1, tree);
            result.push_back(smaller_count);
            update(nums[i] + offset, 1, tree, size);
        }
        reverse(result.begin(), result.end());
        return result;
    }

    // implement Binary Index Tree
    void update(int index, int value, vector<int>& tree, int size) {
        index++;  // index in BIT is 1 more than the original index
        while (index < size) {
            tree[index] += value;
            index += index & -index;
        }
    }

    int query(int index, vector<int>& tree) {
        // return sum of [0, index]
        index++;
        int result = 0;
        while (index > 0) {
            result += tree[index];
            index -= index & -index;
        }
        return result;
    }
};
----------------------------------------------