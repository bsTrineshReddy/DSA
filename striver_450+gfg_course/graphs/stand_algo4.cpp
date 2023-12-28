/*
 1) bridges in a graph : striver
 Time Complexity: O(V+2E)
 Space Complexity : O(V+2E) + O(3V)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    int timer = 1;
    void dfs(int node, int parent, vector<int> &vis,
             vector<int> adj[], int tin[], int low[], vector<vector<int>> &bridges) {
        vis[node] = 1;
        tin[node] = low[node] = timer;
        timer++;
        for (auto it : adj[node]) {
            if (it == parent) continue;
            if (vis[it] == 0) {
                dfs(it, node, vis, adj, tin, low, bridges);
                low[node] = min(low[it], low[node]);
                // node --- it
                if (low[it] > tin[node]) {
                    bridges.push_back({it, node});
                }
            }
            else {
                low[node] = min(low[node], low[it]);
            }
        }
    }
public:
    vector<vector<int>> criticalConnections(int n,
    vector<vector<int>>& connections) {
        vector<int> adj[n];
        for (auto it : connections) {
            int u = it[0], v = it[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<int> vis(n, 0);
        int tin[n];
        int low[n];
        vector<vector<int>> bridges;
        dfs(0, -1, vis, adj, tin, low, bridges);
        return bridges;
    }
};

int main() {

    int n = 4;
    vector<vector<int>> connections = {
        {0, 1}, {1, 2},
        {2, 0}, {1, 3}
    };

    Solution obj;
    vector<vector<int>> bridges = obj.criticalConnections(n, connections);
    for (auto it : bridges) {
        cout << "[" << it[0] << ", " << it[1] << "] ";
    }
    cout << endl;
    return 0;
}

--------------------------------------------------------------------------------

/*
1.1) bridges in a graph: techdose
TIME COMPLEXITY: O(V+E)
*/
#include<bits/stdc++.h>
using namespace std;
#define V 5
#define pb push_back

unordered_map<int,vector<int>> adj;

void DFS(int u,vector<int>& disc,vector<int>& low,vector<int>& parent,vector<pair<int,int>>& bridge)
{
	static int time = 0;
	disc[u] = low[u] = time;
	time+=1;

	for(int v: adj[u])
	{
		if(disc[v]==-1)	//If v is not visited
		{
			parent[v] = u;
			DFS(v,disc,low,parent,bridge);
			low[u] = min(low[u],low[v]);

			if(low[v] > disc[u])
				bridge.pb({u,v});
		}
		else if(v!=parent[u])	//Ignore child to parent edge
			low[u] = min(low[u],disc[v]);
	}
}

void findBridges_Tarjan()
{
	vector<int> disc(V,-1),low(V,-1),parent(V,-1);
	vector<pair<int,int>> bridge;

	for(int i=0;i<V;++i)
		if(disc[i]==-1)
			DFS(i,disc,low,parent,bridge);

	cout<<"Bridges are: \n";
	for(auto it: bridge)
		cout<<it.first<<"-->"<<it.second<<"\n";
}

int main()
{
	adj[0].pb(2);
	adj[2].pb(0);
	adj[0].pb(3);
	adj[3].pb(0);
	adj[1].pb(0);
	adj[0].pb(1);
	adj[2].pb(1);
	adj[1].pb(2);
	adj[3].pb(4);
	adj[4].pb(3);

	findBridges_Tarjan();
	return 0;
}
--------------------------------------------------------------------------------
/*
 2) articulation points
 Time Complexity: O(V+2E)
 Space Complexity : O(V+2E) + O(3V)
*/

#include <bits/stdc++.h>
using namespace std;

//User function Template for C++

class Solution {
private:
    int timer = 1;
    void dfs(int node, int parent, vector<int> &vis, int tin[], int low[],
             vector<int> &mark, vector<int>adj[]) {
        vis[node] = 1;
        tin[node] = low[node] = timer;
        timer++;
        int child = 0;
        for (auto it : adj[node]) {
            if (it == parent) continue;
            if (!vis[it]) {
                dfs(it, node, vis, tin, low, mark, adj);
                low[node] = min(low[node], low[it]);
                if (low[it] >= tin[node] && parent != -1) {
                    mark[node] = 1;
                }
                child++;
            }
            else {
                low[node] = min(low[node], tin[it]);
            }
        }
        if (child > 1 && parent == -1) {
            mark[node] = 1;
        }
    }
public:
    vector<int> articulationPoints(int n, vector<int>adj[]) {
        vector<int> vis(n, 0);
        int tin[n];
        int low[n];
        vector<int> mark(n, 0);
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                dfs(i, -1, vis, tin, low, mark, adj);
            }
        }
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (mark[i] == 1) {
                ans.push_back(i);
            }
        }
        if (ans.size() == 0) return { -1};
        return ans;
    }
};
int main() {

    int n = 5;
    vector<vector<int>> edges = {
        {0, 1}, {1, 4},
        {2, 4}, {2, 3}, {3, 4}
    };

    vector<int> adj[n];
    for (auto it : edges) {
        int u = it[0], v = it[1];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    Solution obj;
    vector<int> nodes = obj.articulationPoints(n, adj);
    for (auto node : nodes) {
        cout << node << " ";
    }
    cout << endl;
    return 0;
}

--------------------------------------------------------------------------------
/*
  2.1) articulation points:techdose
  TIME COMPLEXITY: O(V+E)
*/
#include<bits/stdc++.h>
using namespace std;
#define V 5
#define pb push_back

unordered_map<int,vector<int>> adj;

void DFS(int u,vector<int>& disc,vector<int>& low,vector<int>& parent,vector<bool>& articulation_Point)
{
	static int time = 0;
	disc[u] = low[u] = time;
	time+=1;
	int children = 0;

	for(int v: adj[u])
	{
		if(disc[v]==-1)	//If v is not visited
		{
			children += 1;
			parent[v] = u;
			DFS(v,disc,low,parent,articulation_Point);
			low[u] = min(low[u],low[v]);

			if(parent[u]==-1 and children>1)	//Case-1: U is root
				articulation_Point[u] = true;

			if(parent[u]!=-1 and low[v]>=disc[u])	//Case-2: Atleast 1 component will get separated
				articulation_Point[u] = true;
		}
		else if(v!=parent[u])	//Ignore child to parent edge
			low[u] = min(low[u],disc[v]);
	}	
}

void findAPs_Tarjan()
{
	vector<int> disc(V,-1),low(V,-1),parent(V,-1);
	vector<bool> articulation_Point(V,false);	//Avoids cross-edge

	for(int i=0;i<V;++i)
		if(disc[i]==-1)
			DFS(i,disc,low,parent,articulation_Point);

	cout<<"Articulation Points are: ";
	for(int i=0;i<V;++i)
		if(articulation_Point[i]==true)
			cout<<i<<" ";
}

int main()
{
	adj[0].pb(2);
	adj[2].pb(0);
	adj[0].pb(3);
	adj[3].pb(0);
	adj[1].pb(0);
	adj[0].pb(1);
	adj[2].pb(1);
	//adj[2].pb(4);
	//adj[4].pb(2);
	adj[1].pb(2);
	adj[3].pb(4);
	adj[4].pb(3);

	findAPs_Tarjan();
	return 0;
}
--------------------------------------------------------------------------------
/*
 3) kosaraju algorithm
 Time Complexity: O(V+E) + O(V+E) + O(V+E)
 Space Complexity: O(V)+O(V)+O(V+E)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
private:
    void dfs(int node, vector<int> &vis, vector<int> adj[],
             stack<int> &st) {
        vis[node] = 1;
        for (auto it : adj[node]) {
            if (!vis[it]) {
                dfs(it, vis, adj, st);
            }
        }

        st.push(node);
    }
private:
    void dfs3(int node, vector<int> &vis, vector<int> adjT[]) {
        vis[node] = 1;
        for (auto it : adjT[node]) {
            if (!vis[it]) {
                dfs3(it, vis, adjT);
            }
        }
    }
public:
    //Function to find number of strongly connected components in the graph.
    int kosaraju(int V, vector<int> adj[])
    {
        vector<int> vis(V, 0);
        stack<int> st;
        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                dfs(i, vis, adj, st);
            }
        }

        vector<int> adjT[V];
        for (int i = 0; i < V; i++) {
            vis[i] = 0;
            for (auto it : adj[i]) {
                // i -> it
                // it -> i
                adjT[it].push_back(i);
            }
        }
        int scc = 0;
        while (!st.empty()) {
            int node = st.top();
            st.pop();
            if (!vis[node]) {
                scc++;
                dfs3(node, vis, adjT);
            }
        }
        return scc;
    }
};

int main() {

    int n = 5;
    int edges[5][2] = {
        {1, 0}, {0, 2},
        {2, 1}, {0, 3},
        {3, 4}
    };
    vector<int> adj[n];
    for (int i = 0; i < n; i++) {
        adj[edges[i][0]].push_back(edges[i][1]);
    }
    Solution obj;
    int ans = obj.kosaraju(n, adj);
    cout << "The number of strongly connected components is: " << ans << endl;
    return 0;
}

--------------------------------------------------------------------------------
/*
3.1) tarjans algorithm:strongly connected components:techdose
timecomplexity: o(v+e)
*/
#include<bits/stdc++.h>
using namespace std;
#define V 7
#define pb push_back

unordered_map<int,vector<int>> adj;

void DFS(int u,vector<int>& disc,vector<int>& low,stack<int>& mystack,vector<bool>& presentInStack)
{
	static int time = 0;
	disc[u] = low[u] = time;
	time+=1;
	mystack.push(u);
	presentInStack[u] = true;

	for(int v: adj[u])
	{
		if(disc[v]==-1)	//If v is not visited
		{
			DFS(v,disc,low,mystack,presentInStack);
			low[u] = min(low[u],low[v]);
		}
		//Differentiate back-edge and cross-edge
		else if(presentInStack[v])	//Back-edge case
			low[u] = min(low[u],disc[v]);
	}

	if(low[u]==disc[u])	//If u is head node of SCC
	{
		cout<<"SCC is: ";
		while(mystack.top()!=u)
		{
			cout<<mystack.top()<<" ";
			presentInStack[mystack.top()] = false;
			mystack.pop();
		}
		cout<<mystack.top()<<"\n";
		presentInStack[mystack.top()] = false;
		mystack.pop();
	}
}

void findSCCs_Tarjan()
{
	vector<int> disc(V,-1),low(V,-1);
	vector<bool> presentInStack(V,false);	//Avoids cross-edge
	stack<int> mystack;

	for(int i=0;i<V;++i)
		if(disc[i]==-1)
			DFS(i,disc,low,mystack,presentInStack);
}

int main()
{
	adj[0].pb(1);
	adj[1].pb(2);
	adj[1].pb(3);
	adj[3].pb(4);
	adj[4].pb(0);
	adj[4].pb(5);
	adj[4].pb(6);
	adj[5].pb(6);
	adj[6].pb(5);

	findSCCs_Tarjan();
	return 0;
}
