/*
 Method1: simple bfs withy visited array
 Time Complexity: O(N*M) where n is size of the array and m is the range.
 Space Complexity:O(M/2) 
*/
int minimumOperations(vector<int>& nums, int start, int goal) {
        int n=nums.size();
        queue<int>qq;
        vector<bool>visited(1001,false);
        qq.push(start);
        int ans=0;
        while(!qq.empty()){
            int size=qq.size();
            while(size--){
                int front_element=qq.front();
                qq.pop();
                if(front_element==goal)
                    return ans;
                if(front_element>1000 or front_element<0 or visited[front_element]==true)
                    continue;
                visited[front_element]=true;
                for(int i=0;i<nums.size();i++){
                    int first=front_element+nums[i];
                    int second=front_element-nums[i];
                    int third=front_element^nums[i];
                    qq.push(first);
                    qq.push(second);
                    qq.push(third);
                }
            }
            ans++;
        }
        return -1; // not possible to reach goal
    }
============================================================================