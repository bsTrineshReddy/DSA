/*
1. leetcode: 1430
https://leetcode.com/problems/check-if-a-string-is-a-valid-sequence-from-root-to-leaves-path-in-a-binary-tree/description/
*/

//method 1: 
bool func(TreeNode* root, vector<int>& arr,int i=0) {
        //check if root is null but some elements of arr are left
        if( !root && i <= arr.size()-1 )
            return false;
	//if we are on the last element of arr, then check it is leaf condition
        if( i == arr.size()-1 ){
            return root->val == arr[i] && root->left == NULL && root->right == NULL;
        }
	// if root->val is same as arr index value, call for next values in arr 
	// on left and right subtrees
        return root->val == arr[i] && ( func(root->left,arr,i+1) || 
                                     func(root->right,arr,i+1) );

}

// method2: techdose
bool isValidSequence(TreeNode* root,int n,int pos,vector<int>& arr)
    {
        if(!root)
            return false;
        else if(pos==n)
            return false;
        else if(root->val!=arr[pos])
            return false;
        else if(!root->left && !root->right && pos==n-1)
            return true;
        
        return (isValidSequence(root->left,n,pos+1,arr) || isValidSequence(root->right,n,pos+1,arr));
}
----------------------------------------------------------------------------
/*
 2. leetcode:1429
 first unique number
*/

// method1: queue + hashmap
class FirstUnique {

  private Queue<Integer> queue = new ArrayDeque<>();
  private Map<Integer, Boolean> isUnique = new HashMap<>();

  public FirstUnique(int[] nums) {
    for (int num : nums) {
      // Notice that we're calling the "add" method of FirstUnique; not of the queue. 
      this.add(num);
    }
  }

  public int showFirstUnique() {
    // We need to start by "cleaning" the queue of any non-uniques at the start.
    // Note that we know that if a value is in the queue, then it is also in
    // isUnique, as the implementation of add() guarantees this.
    while (!queue.isEmpty() && !isUnique.get(queue.peek())) {
      queue.remove();
    }
    // Check if there is still a value left in the queue. There might be no uniques.
    if (!queue.isEmpty()) {
      return queue.peek(); // We don't want to actually *remove* the value.
    }
    return -1;
  }

  public void add(int value) {
    // Case 1: We need to add the number to the queue and mark it as unique. 
    if (!isUnique.containsKey(value)) {
      isUnique.put(value, true);
      queue.add(value);
    // Case 2 and 3: We need to mark the number as no longer unique.
    } else {
      isUnique.put(value, false);
    }
  }
}
-------------------
// method2: queue as linked list + hashmap
class FirstUnique {
  
  private Set<Integer> setQueue = new LinkedHashSet<>();
  private Map<Integer, Boolean> isUnique = new HashMap<>();
  
  public FirstUnique(int[] nums) {
    for (int num : nums) {
      this.add(num);
    }
  }
    
  public int showFirstUnique() {
    // If the queue contains values, we need to get the first one from it.
    // We can do this by making an iterator, and getting its first item.
    if (!setQueue.isEmpty()) {
       return setQueue.iterator().next();
    }
    return -1;
  }
    
  public void add(int value) {
    // Case 1: This value is not yet in the data structure.
    // It should be ADDED.
    if (!isUnique.containsKey(value)) {
      isUnique.put(value, true);
      setQueue.add(value);
    // Case 2: This value has been seen once, so is now becoming
    // non-unique. It should be REMOVED.
    } else if (isUnique.get(value)) {
      isUnique.put(value, false);
      setQueue.remove(value);
    }
  }
}
-----------------------------------------------------------------------------------------------
/*
 3. leetcode 201
*/
// method1: techdose
int rangeBitwiseAnd(int m, int n) {
        
        int count = 0;
        while(m!=n)
        {
            m>>=1;
            n>>=1;
            count+=1;
        }
        return m<<=count;
}
----------------
// method2: leetcode (bitshift)
class Solution {
  public int rangeBitwiseAnd(int m, int n) {
    int shift = 0;
    // find the common 1-bits
    while (m < n) {
      m >>= 1;
      n >>= 1;
      ++shift;
    }
    return m << shift;
  }
}
----------------
// method3: Brian Kernighan's Algorithm (leetcode)
class Solution {
  public int rangeBitwiseAnd(int m, int n) {
    while (m < n) {
      // turn off rightmost 1-bit
      n = n & (n - 1);
    }
    return m & n;
  }
}
------------------------------------------------------------------------------------------------
/*
4. leetcode: 678
https://leetcode.com/problems/valid-parenthesis-string/description/
*/

// method1: techdose 2 stacks
bool checkValidString(string s) {
        
        stack<int> open,star;
        int len = s.length();
        
        for(int i=0;s[i]!='\0';++i)
        {
            if(s[i]=='(')
                open.push(i);
            else if(s[i]=='*')
                star.push(i);
            else
            {
                if(!open.empty())
                    open.pop();
                else if(!star.empty())
                    star.pop();
                else
                    return false;
            }
        }
        
        //Now process leftover opening brackets
        while(!open.empty())
        {
            if(star.empty())
                return false;
            else if(open.top() < star.top())
            {
                open.pop();
                star.pop();
            }
            else    //CASE: open.top() > star.top()
                return false;
        }
        return true;
    }
};
---------------
// explore leetcode 3 methods


/*
 5. happy number
*/

//method1: set (techdose)
bool isHappy(int n) {
        set<int> myset;
        int val;
        int index;
        
        while(1)
        {
            val = 0;
            while(n)
            {
                index = n%10;
                val += index*index;
                n /=10;
            }
            if(val==1)
                return true;
            else if(myset.find(val)!=myset.end())
                return false;
            
            myset.insert(val);
            n = val;
        }
        return false;
    }
----------------
// method2: leetcode (slow and fast)
class Solution {

     public int getNext(int n) {
        int totalSum = 0;
        while (n > 0) {
            int d = n % 10;
            n = n / 10;
            totalSum += d * d;
        }
        return totalSum;
    }

    public boolean isHappy(int n) {
        int slowRunner = n;
        int fastRunner = getNext(n);
        while (fastRunner != 1 && slowRunner != fastRunner) {
            slowRunner = getNext(slowRunner);
            fastRunner = getNext(getNext(fastRunner));
        }
        return fastRunner == 1;
    }
}
--------------------------------------------------------------------------------
/*
 leetcode : 1232

 https://leetcode.com/problems/check-if-it-is-a-straight-line/
*/

bool checkStraightLine(vector<vector<int>>& coordinates) {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);
        
        int points = coordinates.size();
        int xdiff = abs(coordinates[1][0]-coordinates[0][0]);
        int ydiff = abs(coordinates[1][1]-coordinates[0][1]);
        int curr_xdiff,curr_ydiff;
        
        for(int i=2;i<points;++i)
        {
            curr_xdiff = abs(coordinates[i][0]-coordinates[i-1][0]);
            curr_ydiff = abs(coordinates[i][1]-coordinates[i-1][1]);
            if(ydiff*curr_xdiff != xdiff*curr_ydiff)
                return false;
        }
        return true;
        
    }
-------------------------
