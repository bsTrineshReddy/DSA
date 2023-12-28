/*
merge overlapping sub intervals
*/

// methos1: brute force
vector<vector<int>> mergeOverlappingIntervals(vector<vector<int>> &arr) {
    int n = arr.size(); // size of the array

    //sort the given intervals:
    sort(arr.begin(), arr.end());

    vector<vector<int>> ans;

    for (int i = 0; i < n; i++) { // select an interval:
        int start = arr[i][0];
        int end = arr[i][1];

        //Skip all the merged intervals:
        if (!ans.empty() && end <= ans.back()[1]) {
            continue;
        }

        //check the rest of the intervals:
        for (int j = i + 1; j < n; j++) {
            if (arr[j][0] <= end) {
                end = max(end, arr[j][1]);
            }
            else {
                break;
            }
        }
        ans.push_back({start, end});
    }
    return ans;
}
----------------------
// method2: optimised approach
vector<vector<int>> mergeOverlappingIntervals(vector<vector<int>> &arr) {
    int n = arr.size(); // size of the array

    //sort the given intervals:
    sort(arr.begin(), arr.end());

    vector<vector<int>> ans;

    for (int i = 0; i < n; i++) {
        // if the current interval does not
        // lie in the last interval:
        if (ans.empty() || arr[i][0] > ans.back()[1]) {
            ans.push_back(arr[i]);
        }
        // if the current interval
        // lies in the last interval:
        else {
            ans.back()[1] = max(ans.back()[1], arr[i][1]);
        }
    }
    return ans;
}
------------------------------------------------------------------

/*
insert interval
given sorted list of intervals , insert the given new interval
*/
vector<vector<int>> insert(vector<vector<int>>& a, vector<int>& ni) {
int n = a.size();
vector<vector<int>> ans;
for(int i = 0;i<n;i++)
{
if(ni[1]<a[i][0]) //if interval to be merged is less than interval in array
{
ans.push_back(ni);
for(;i<n;i++)
{
ans.push_back(a[i]);
}
return ans;
}
else if(a[i][1] < ni[0]) //If current interval is before newInterval
ans.push_back(a[i]);
else
{
ni[0] = min(ni[0],a[i][0]);
ni[1] = max(ni[1],a[i][1]);
}
}
ans.push_back(ni);
return ans;
}