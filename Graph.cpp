#include <iostream>
#include <queue>
#include <vector>
#include <stack>


using namespace std;

vector<int> bfs(vector<int> adj[], int n)
{
    vector<int> bfs;
    vector<int> vis(n + 1, 0);

    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {

            ///BFS STARTS HERE
            queue<int> q;
            q.push(i);
            vis[i] = 1;
            while (!q.empty())
            {
                int node = q.front();
                q.pop();
                bfs.push_back(node);
                for (auto it : adj[node])
                {
                    if (!vis[it])
                    {
                        q.push(it);
                        vis[it] = 1;
                    }
                }
            }
        }
    }
    return bfs;
}

void dfs(vector<int> adj[], int node, vector<int> &is_vis, vector<int> &store_dfs)
{
    is_vis[node] = 1;
    store_dfs.push_back(node);
    for (const auto it : adj[node])
    {
        if (!is_vis[it])
        {
            dfs(adj, it, is_vis, store_dfs);
        }
    }
}

vector<int> dfs_of_graph(vector<int> adj[], int n)
{
    vector<int> store_dfs;
    vector<int> vis(n + 1, 0);

    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            dfs(adj, i, vis, store_dfs);
        }
    }
    return store_dfs;
}

int find_min_moves(int start, int end, int arr[], int n)
{
    vector<int> vis(end + 1, 0);
    vis[start] = 1;
    queue<pair<int, int>> q;
    q.push({start, 0});
    while (!q.empty())
    {

        int node = q.front().first;
        int steps = q.front().second;
        vis[node] = 1;
        q.pop();
        if (node == end)
        {
            return steps;
        }
        for (int i = 0; i < n; i++)
        {
            int dest = node * arr[i];
            if (!vis[dest] && dest <= end)
            {
                q.push({dest, steps + 1});
            }
        }
    }
    return -1;
}


// both in bfs and dfs check if the next node is already visited if already visited,check if adjacent node is  the parent of the node 
//if not then it was already visited and now again we reached to same node.so it is cyclic.
//because if the graph is not cyclic there is no way a adjacent node can be already visited unless it is parent.  
bool dfs_cycle(vector<int> adj[], int node, vector<int> &visited, int parent) 
{
    visited[node] = 1;
    for (int it : adj[node])
    {
        if (!visited[it])
        {

            if (dfs_cycle(adj, it, visited, node) == true)
            {
                return true;
            }
        }
        else if (visited[it] == 1 && it != parent)
        {
            return true;
        }
    }

    return false;
}

void detectcycle_using_dfs(vector<int> adj[], int n)
{

    vector<int> vis(n + 1, 0);
    bool flag = false;
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            if (dfs_cycle(adj, i, vis, 0) == true)
            {
                cout << "CYCLE DETECTED";
                return;
            }
        }
    }

    cout << "CYCLE NOT DETECTED";
}

bool bfs_cycle(vector<int> adj[], int i, vector<int> &vis, int parent)
{

    queue<pair<int, int>> q;
    q.push({i, parent});
    vis[i] = 1;
    while (!q.empty())
    {
        int node = q.front().first;
        int parent = q.front().second;

        for (int v : adj[node])
        {
            if (!vis[v])
            {
                q.push({v, parent});
                vis[v] = 1;
            }
            else if (vis[v] == true && v != parent)
            {
                return true;
            }
        }
    }
    return false;
}

void detectcycle_using_bfs(vector<int> adj[], int n)
{

    vector<int> vis(n + 1, 0);
    bool flag = false;
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            if (bfs_cycle(adj, i, vis, 0) == true)
            {
                cout << "CYCLE DETECTED";
                return;
            }
        }
    }

    cout << "CYCLE NOT DETECTED";
}

bool bfs_check(vector<int> adj[], int node, vector<int> &color)
{
    queue<int> q;
    q.push(node);
    color[node] = 1;
    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        for (int v : adj[node])
        {

            if (color[v] == -1)
            {
                color[v] = 1 - color[node];
                q.push(v);
            }
            else if (color[v] == color[node])
            {
                return false;
            }
        }
    }
    return true;
}



//bipartite graph is the graph which can be coloured by two colours and no two nodes that are next to each other have same colour,
//if the graph is not cyclic it is already bipartite,
//if the number of nodes in the cycle is odd then it will not be bipartite else if even it will be bipartite 
//so both in dfs and bfs we check if adjacent node is not coloured we colour with parent nodes next colour (1-colour[parent])
//else if it is coloured we check that if the colour of parent node and adjacent node matches if yes then it isnt bipartite 
void bfs_check_bipartite(vector<int> adj[], int n)
{

    vector<int> color(n + 1, -1);
    bool flag = false;
    for (int i = 1; i <= n; i++)
    {
        if (color[i] == -1)
        {
            if (bfs_check(adj, i, color))
            {
                cout << "BIPARTITE";
                return;
            }
            else
            {
                break;
            }
        }
    }
  cout << "NOT BIPARTITE";
}

bool check_dfs(vector<int> adj[], int node, vector<int> &color)
{
    if (color[node] == -1)
    {
        color[node] = 1;
    }
    for (int i : adj[node])
    {

        if (color[i] == -1)
        {
            color[i] = 1 - color[node];
            if (check_dfs(adj, i, color) == false)
            {
                return false;
            }
        }
        else if (color[i] == color[node])
        {
            return false;
        }
    }
    return true;
}

void dfs_check_bipartite(vector<int> adj[], int n)
{
    vector<int> color(n + 1, -1);
    for (int i = 1; i <= n; i++)
    {
        if (color[i] == -1)
        {
            if (check_dfs(adj, i, color))
            {
                cout << "BIPARTITE";
                return;
            }
            else
            {
                break;
            }
        }
    }
    cout << "NOT BIPARTITE";
}



// which checking cycle in DG we use a dfs_vis array which stores the node that are visited in the current dfs run
//because it might happen that a node was visited in previous dfs run but is still marked visited in vis array so 
//when clearing the recursion stact we make the nodes value in dfs_vis 0,
//when adjacent nodes vis is 1 and also dfs_vis is 1 which means the node was already visited and also visited in the same dfs run 
//which indicated there is a cycle because there is no way that we caan reach the same node which is vidited in same dfs run

bool DG_dfs_cycle(vector<int> adj[], int node, vector<int> &vis, vector<int> &dfs_vis)
{
    vis[node] = 1;
    dfs_vis[node] = 1;
    for (int it : adj[node])
    {
        if (!vis[it])
        {
            if (DG_dfs_cycle(adj, it, vis, dfs_vis) == true)
            {
                return true;
            }
        }
        else if (dfs_vis[it])
        {
            return true;
        }
    }
    dfs_vis[node] = 0;
    return false;
}

void DG_check_cycle_dfs(vector<int> adj[], int n)
{
    vector<int> vis(n + 1, 0);
    vector<int> dfs_vis(n + 1, 0);
    bool flag = false;
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {

            if (DG_dfs_cycle(adj, i, vis, dfs_vis) == true)
            {
                cout << "CYCLE DETECTED";
                return;
            }
        }
    }

    cout << "CYCLE NOT DETECTED";
}

// it says if U->V then u must appear before v means all the adjacent nodes(V) must be printed later than U 
//we can start with any node
//the node which doesnot have any income edge will be at first as no node depend on that node so none of node will be before it 
// and the node with no outgong edge will be at last cause it doesnot depend on any node so it wont be before any node
// it is used when we need to sort something based on the dependency of nodes to one other (pepcoding )
// we run dfs,when we reach node that has no adj than we add in the stack while coming back in the recursion i.e we add in the postorder,
//when we add  a nodeee=U in stack it means all its adjacent nodes(V) have been added in stack so it means all the nodes that depended on that nodeee has been added in stack ,
// meaning they will be printed later than that nodeee so we can add that nodeee.which topological sort wants us to do 
// note when we are said to print, in which order work should be done when nodes (works) are dependent then we print stack in reverse (from bottom to end)
// why not directly print instead adding in stack?
// because we start printing when dfs ends postorder. so the last node in dfs means indicates it doesnot depend on anyone so it must be printed last
// but if we normally just print, the last element will be printed at first which is just opposite to topological sort
// so when asked  in which order work should be done we can just print instead of adding in stack

void dfs_topological_sort(vector<int> adj[], int node, vector<int> &vis, stack<int> &st)
{
    vis[node] = 1;
    for (int it : adj[node])
    {
        if (!vis[it])
        {
            dfs_topological_sort(adj, it, vis, st);
        }
    }

    st.push(node);
}

void topological_sort_using_dfs(vector<int> adj[], int n)
{
    vector<int> vis(n, 0);
    stack<int> st;
    for (int i = 0; i < n; i++)
    {

        if (vis[i] == 0)
        {

            dfs_topological_sort(adj, i, vis, st);
        }
    }

    while (!st.empty())
    {

        cout << ' ' << st.top();
        st.pop();
    }
}

//KAHN ALGORITHM
//the node which doesnot have any income edge will be at first as no node depend on that node so none of node will be before it 
// and the node with no outgong edge will be at last cause it doesnot depend on any node so it wont be before any node
//  we use indegree array which stores the indegree of all the nodes,indegree means the no of edges pointed to a node
//since we need a node with zero indeg which means no node depend on it,  means that all the node will come after that node,so we add all such nodes with indeg 0 in queue
//  then we apply normal bfs and we decrease the indeg of each adjacent nodes ,since the node will be printed already so,
// then if a adjacent nodes indeg becomes 0 we add it in the queue 
void topological_sort_using_bfs(vector<int> adj[], int n)
{
    queue<int> q;
    vector<int> indeg(n+1, 0);
   
    for (int i = 1; i <= n; i++)
    {
        for (int v : adj[i])
        {
            indeg[v]++;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if(indeg[i]==0)
        {
            q.push(i);
        }
    }
    while(!q.empty())
    {
        int node=q.front();
        q.pop();
        cout<<node<<" ";
        for(int it:adj[node])
        {
            indeg[it]--;
            if(indeg[it]==0)
            {
                q.push(it);
            }
        }
    }

}

void DG_cycle_detection_BFS(vector<int> adj[],int n)
{
    
    queue<int> q;
    vector<int> indeg(n+1, 0);
    int cnt=0;
    for (int i = 1; i <= n; i++)
    {
        
        for (int v : adj[i])
        {
            indeg[v]++;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (indeg[i] == 0)
        {
            q.push(i);
        }
    }
    while (!q.empty())
    {
        int node = q.front();
        q.pop();
       
        cnt++;
        for (int it : adj[node])
        {
            indeg[it]--;
            if (indeg[it] == 0)
            {
                q.push(it);
            }
        }
    }
    if(cnt==n)
    {
        cout<<"CYCLE NOT DETECTED";
    }
    else
    {
        cout << "CYCLE  DETECTED";
    }
}

//using bfs we do this 
//we take a dis array and mark all elemnts value with a highest value 
//in which we store the distanc eof each indices from the src and at end we have all the distance between src to any dest
// we add src in the queue  and mark dist of src to 0 as dist from src to src  is oviousl;y zero 
// we check if the nodes dist +1 (+1 because it is ug graph and consider distance between each node as 1)
// is less than the value it already has in this way we get the shortest value .
// the idea is for the node coming out we have its distance from src so for its adj nodes distance from src we need to add 1 
// but after adding distance 1 ,if the value may be greater or equal to the adj nodes dist in the dist array than it means already 
//a shortest distance has been found for that adj node 
void bfs_shortest_distance_UG(vector<int> adj[],int n,int src)
{
    vector<int> dis(n,INT32_MAX);
    queue<int> q;
    dis[src]=0;
    q.push(src);
while(!q.empty())
{
    int node=q.front();
    q.pop();
    for(int it:adj[node])
    {
        if(dis[node]+1<dis[it])
        {
            dis[it] = dis[node] + 1;
            q.push(it);
        }

    }
}

for(int it:dis)
{
    cout<<it<<" ";
}
}

// daik-stra 

// we take a priority queue
// we take a source node and add it in the pq ,now we visit its adj nodes and if their distance is greater thatn we update the adj nodes distance and add in the queue
// after pushing all the adj nodes now we again move to next node which has the smallest dis of all the nodes in pq,so priority queue returns automatically nodes with min dist
//  we keep on goin throught the smallest dis nodes and keep updating
//  we make distance of source initially zero as dis from source to source is 0 always
//  distance of nextnode currently> dist of the parent node from source + wt of next node (which is the dis from parent node to the adj node)
//  if above is true than we update nodes distance with dis of partent node +wt of adj node
// in our way we take the min node update the distance of all its adj nodes if they are greater and keep on doing it
//  suppose node 3 is connected to 1 and 2 now at first node 3's dis will be inf but later it will be updated to its wt+dis of parent node.ie.1 and then  3 will be pushed 
//  but when 2s adj nodes are being added if the wt + dis of 2 is less that its dist from 1 (prev dist) than we uupdate the dist and again add it in the queue


void dijkstraAlgo(vector<pair<int, int>> adj[],int n,vector<int> &dis,int src)
{
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    dis[src]=0;
    pq.push( {0,src});
    while(!pq.empty())
    {
        int node=pq.top().second;
        int dist=pq.top().first;
        pq.pop();
        for(pair<int,int> p:adj[node])
        {
            int adj_node=p.first;
            int adj_node_wt=p.second;
            if (dis[adj_node] > dis[node] + adj_node_wt)
            {
                dis[adj_node] = dis[node] + adj_node_wt;
                pq.push({dis[adj_node], adj_node});
            }
        }
    }
}




// in prims algo we make a tree with nodes and edges of minimum value;
//we take three arrays MST(for telling if a node has been added to the tree )
//parent array which stores the info about the node and its parent of the spanning tree
//dis array we store the current dis of the node 
// we take the pq as in dikstra because we want to get the least weight edge from all the adj nodes 
// so we add the first node as src in pq with its dis as 0

// in mst we need n nodes and n-1 edges so we run a loop till n-1
//now we update the distance of each adj nodes and add in the pq ,while adding in the queue we dont push than node in the tree,,,,
//we push the adj nodes in the queue to get the minim weighted node
//and we take out the node with shortest dis and then add in the tree by doing mst[node]=true;
// suppose node 3 is connected to 1 and 2 now at first node 3's dis will be inf but later it will be updated to its wt from 1 and then parent of 3 will be 1 
// but when 2s adj nodes are being added if the wt of 3 from 2 is less that its dist from 1 (prev dist) than we uupdate the dist and update its parent to be 2 
// so at first inj the tree 3 was connected to 1 but later it got ocnnected to 2

void prims_Algo(vector<pair<int, int>> adj[],int n)
{
    bool MST[n];
   int  parent[n];
   int dis[n];
   for(int i=0;i<n;i++)
   {
       MST[i]=false;
       parent[i]=-1;
       dis[i]=INT32_MAX;
   }
    dis[0]=0;
   
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0,0});
    for(int i=0;i<n-1;i++)
    {
        int node=pq.top().second;
        pq.pop();
        MST[node]=true;
        for(pair<int,int> it:adj[node])
        {
            int adj_dis=it.second;
            int adj_node=it.first;
          
            if(MST[adj_node]!=true && adj_dis<dis[adj_node])
            {
                pq.push({adj_dis,adj_node});
                parent[adj_node]=node;
                dis[adj_node]=adj_dis;
            }
            
        }

    }
    for(int i: parent)
    {
        cout<<i<<" ";
    }
}

    void min_time_take_by_each_job(vector<int> adj[], int n)
{
    queue<pair<int,int>> q;
    vector<int> indeg(n + 1, 0);

    for (int i = 1; i <= n; i++)
    {
        for (int v : adj[i])
        {
            indeg[v]++;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (indeg[i] == 0)
        {
            q.push({i,1});
        }
    }
    while (!q.empty())
    {
        int node = q.front().first;
        int time=q.front().second;
        q.pop();
        cout << time << " ";
        for (int it : adj[node])
        {
            indeg[it]--;
            if (indeg[it] == 0)
            {
                q.push({it,time+1});
            }
        }
    }
}
struct Node{
int u,v,w;
Node(int _u,int _v,int _w)
{
    u=_u;v=_v;w=_w;
}

};

//bellman ford TC(o(N-1)*(e))
//work for directed for both +ve and -ve edges but no negative cycles 
//work for undirected but no -ve edges
//if undirected we need to convert graph to directed
//we need to draverse each edge for totalnode-1 times and relax each node
//after n-1 times the shorted distance value in dis array  can be more reduces but if it furether reduces when doing one more 
//cycle than there is negative cycle
void BellmanFordAlgorithm(int n,vector<Node> &edges)
{

    int inf = 10000000;
    vector<int> dist(n, inf);

    dist[0] = 0;

    for (int i = 1; i <= n - 1; i++)
    {
        for (auto it : edges)
        {
            if (dist[it.u] + it.w < dist[it.v])
            {
                dist[it.v] = dist[it.u] + it.w;
            }
        }
    }

    int fl = 0;
    for (auto it : edges)
    {
        if (dist[it.u] + it.w < dist[it.v])
        {
            cout << "Negative Cycle";
            fl = 1;
            break;
        }
    }

    if (!fl)
    {
        for (int i = 0; i < n; i++)
        {
            cout << i << " " << dist[i] << endl;
        }
    }
}

    int main()
{

    // int arr[3] = {2, 5, 10};
    // cout << find_min_moves(2, 100, arr, 3);

    int n, m;

    cout << "enter the nodes and edges: ";
    cin >> n >> m;
    // int adj[n + 1][n + 1]={0};
    vector<Node> adj;

    for (int i = 0; i < m; i++)
    {
       
        int u, v,w;
        cin >> u >> v>>w;
        adj.push_back(Node(u,v,w));
       
        }
    BellmanFordAlgorithm(n,adj);

   
    // for(int i:dist)
    // {
    //     cout<<i<<" ";
    // }

    //     vector<int> dfs_vec = dfs_of_graph(adj, n);
    //     for (int i : dfs_vec)
    //     {
    //         cout << i;
    //     }
    // cout<<"\n";
    //     vector<int> bfs_vec = bfs(adj, n);
    //     for (int i : bfs_vec)
    //     {
    //         cout << i;
    //     }

    // for (vector<int> i : adj)
    // {
    //     for (int s : i)
    //     {
    //         cout << s;
    //     }

    //     cout << "\n";
    // }
}

