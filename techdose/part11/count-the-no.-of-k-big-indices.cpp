
 max_heap, segment tree, binary indexed tree
class Solution {
public:
    int kBigIndices(vector<int>& nums, int k) {
        int n = nums.size(); 
        vector<bool> prefix(n); 
        priority_queue<int> pq; 
        for (int i = 0; i < n; ++i) {
            if (pq.size() == k && pq.top() < nums[i]) prefix[i] = true; 
            pq.push(nums[i]); 
            if (pq.size() > k) pq.pop(); 
        }
        int ans = 0; 
        pq = priority_queue<int>(); 
        for (int i = n-1; i >= 0; --i) {
            if (pq.size() == k && pq.top() < nums[i] && prefix[i]) ++ans; 
            pq.push(nums[i]); 
            if (pq.size() > k) pq.pop(); 
        }
        return ans; 
        
    }
};

// segment tree
class Solution {
public:
    int kBigIndices(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int>res(n,0);
        int size = (int)1e5 + 1;
        int x = (int)(ceil(log2(size))); 
	    int max_size = 2*(int)pow(2, x) - 1; 
        vector<int> tree(max_size);

        // call left
        for (int i=0; i< n;i++) {
            int curr = query(tree, 0,size-1, 0, nums[i]-1, 0);
            if(curr>=k)res[i]++;
            update(tree, 0, size-1,nums[i], 1,0);
        }
        
        for(auto &x: tree)
           x=0;

        // cal right
        for (int i=n-1; i>=0;i--) {
            int curr = query(tree, 0,size-1, 0, nums[i]-1, 0);
            if(curr>=k)res[i]++;
            update(tree, 0, size-1,nums[i], 1,0);
        }
 
        int count =0;
        for(int i=0;i<res.size();i++){
            if(res[i]==2)count++;
        }
        return count;
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




