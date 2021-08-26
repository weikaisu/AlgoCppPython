#include "leetcode.h"

class GraphNode
{
private:
    //int vertex, weight;
public:
    GraphNode(int v, int w) : vertex(v), weight(w) {};
    int vertex, weight;
};
class Graph
{
private:
    int vertex_num;
    list<int> *adj_list;
    list<GraphNode> *adj_list_GraphNode;
    vector<bool> visited;
public:
    Graph(int v) : vertex_num(v), visited(v) {
        adj_list=new list<int>[v];
        adj_list_GraphNode=new list<GraphNode>[v];
    }
    void addEdge(int u, int v);
    void addEdge(int u, int v, int w);
    void traverseBFS(int s);
    void traverseDFS(int s);
    void traverseDFS_disconnected(void);
    void topologicalSort(void);
    void topologicalSrot(int v, stack<int> &s);
    void longestPath(int s);
    int findMotherVertex(void);
    bool isRouteBetweenTwoNode(GraphNode sour, GraphNode dest);

    void Dijkstra_vector(int s);
    void Dijkstra_set(int s);
    void Dijkstra_priority_queue(int s);
    void BellmanFord(int s);
};
void Graph::addEdge(int u, int v)
{
    adj_list[u].push_back(v);
}
void Graph::addEdge(int u, int v, int w)
{
    GraphNode node(v, w);
    adj_list_GraphNode[u].push_back(node);
}
void Graph::traverseBFS(int v)
{
    queue<int> q;

    visited[v]=true;
    q.push(v);
    while(!q.empty()) {
        v=q.front();q.pop();
        cout<<v<<' ';
        for(list<int>::iterator i=adj_list[v].begin() ; i!= adj_list[v].end() ; i++)
            if (!visited[*i]) {
                visited[*i]=true;
                q.push(*i);
            }
    }
}
void Graph::traverseDFS(int v)
{
#if 0 //iterative with stack
    stack<int> s;

    visited[v]=true;
    s.push(v);
    while(!s.empty()) {
        v=s.top();s.pop();
        cout<<v<<' ';
        for(list<int>::iterator i=adj_list[v].begin() ; i!=adj_list[v].end() ; i++)
            if(!visited[*i]) {
                visited[*i]=true;
                s.push(*i);
            }
    }
#else
    visited[v]=true;
    cout<<v<<' ';

    for(list<int>::iterator i=adj_list[v].begin() ; i!=adj_list[v].end() ; i++)
        if(!visited[*i])
            traverseDFS(*i);
#endif // 1
}
void Graph::traverseDFS_disconnected()
{
    for (int i = 0; i<vertex_num; i++) {
        for(int j=0; j<vertex_num; j++)
            visited[j]=false;
        traverseDFS(i);
        cout<<endl;
    }
}
void Graph::topologicalSrot(int v, stack<int> &s)
{
    visited[v]=true;
#if 0
    for(list<int>::iterator i=adj_list[v].begin(); i!=adj_list[v].end() ; i++)
        if(!visited[*i])
            topologicalSrot(*i, s);
#else
    for(list<GraphNode>::iterator i=adj_list_GraphNode[v].begin(); i!=adj_list_GraphNode[v].end(); i++)
        if(!visited[i->vertex])
            topologicalSrot(i->vertex, s);
#endif // 0
    s.push(v);
}
void Graph::topologicalSort(void)
{
    stack<int> s;
    //DFS
    for(int i=0; i<vertex_num; i++)
        if(!visited[i])
            topologicalSrot(i, s);

    while(!s.empty())
        {cout<<s.top()<<' '; s.pop();}
}

//Given a Weighted Directed Acyclic Graph (DAG) and a source vertex s in it,
//find the longest distances from s to all other vertices in the given graph.
void Graph::longestPath(int s)
{   //time(N)
    stack<int> top_stack;
    vector<int> dist(vertex_num, INT_MIN);

    for(int i=0; i<vertex_num; i++)
        if(!visited[i])
            topologicalSrot(i, top_stack);

    //Once we have topological order (or linear representation), we one by one process all vertices in topological order.
    //For every vertex being processed, we update distances of its adjacent using distance of current vertex.
    dist[s]=0;
    while(!top_stack.empty()) { //the inner loop runs O(V+E) times
        int u=top_stack.top(); top_stack.pop();
        if(dist[u]!=INT_MIN) {
            for(list<GraphNode>::iterator i=adj_list_GraphNode[u].begin(); i!=adj_list_GraphNode[u].end(); i++)
                if(dist[i->vertex] < dist[u] + i->weight)
                    dist[i->vertex] = dist[u] + i->weight;
        }
    }

    for (int i = 0; i<vertex_num; i++)
        (dist[i] == INT_MIN)? cout << "INT_MIN " : cout << dist[i] << " ";
}
//A mother vertex in a graph G = (V,E) is a vertex v such that all
//other vertices in G can be reached by a path from v.
int Graph::findMotherVertex(void)
{
    int last_v=0; // last finished vertex

    //Do a DFS traversal and find the last finished vertex
    for(int i=0; i<vertex_num; i++) {
        if(!visited[i]) {
            traverseDFS(i);
            last_v=i;
        }
    }
    // If there exist mother vertex (or vetices) in given
    // graph, then v must be one (or one of them)
    // Now check if v is actually a mother vertex (or graph
    // has a mother vertex).  We basically check if every vertex
    // is reachable from v or not.
    // Reset all values in visited[] as false and do
    // DFS beginning from v to check if all vertices are
    // reachable from it or not.
    fill(visited.begin(), visited.end(), false);
    traverseDFS(last_v);
    //if(any_of(visited.begin(), visited.end(), [](bool v){return v==false;})) //lambda expression C++11
    if(any_of(visited.begin(), visited.end(), bind2nd(equal_to<bool>(),false)))
        return -1;
    else
        return last_v;
}
bool Graph::isRouteBetweenTwoNode(GraphNode sour, GraphNode dest)
{
    stack<GraphNode> s;
    //DFS
    visited[sour.vertex]=true;
    s.push(sour);

    while(!s.empty()) {
        sour=s.top(); s.pop();
        for(auto i=adj_list_GraphNode[sour.vertex].begin(); i!=adj_list_GraphNode[sour.vertex].end(); i++) {
            if(!visited[i->vertex]) {
                if(i->vertex==dest.vertex) return true;
                else {
                    visited[i->vertex]=true;
                    s.push(*i);
                }
            }
        }
    }
    return false;
}
void Graph::Dijkstra_vector(int u)
{
    // V^2
    vector<bool> dist_min(vertex_num, false);
    vector<int> dist_value(vertex_num, INT_MAX);
    int min_index;

    dist_min[u]=true;
    dist_value[u]=0;
    min_index=u;
    while(min_index!=-1) {
        dist_min[min_index]=true;
        u=min_index;
        for(auto i=adj_list_GraphNode[u].begin(); i!=adj_list_GraphNode[u].end(); i++) {
            int v=i->vertex, w=i->weight;
            if((!dist_min[v]) && (dist_value[v] > dist_value[u] + w))
                dist_value[v] = dist_value[u] + w;
        }

        min_index=-1;
        for(auto i=0, m=INT_MAX; i<vertex_num; i++)
            if(!dist_min[i]&&m>dist_value[i]) {
                min_index=i;
                m=dist_value[i];
            }
    }
    for_each(dist_value.begin(), dist_value.end(), [](int dist){cout<<dist<<' ';});
}
void Graph::Dijkstra_set(int u)
{
    // ElogV
    set<pair<int,int>>dist_min;
    vector<int> dist_value(vertex_num, INT_MAX);

    dist_min.insert(make_pair(0, u));
    dist_value[u] = 0;
    while(!dist_min.empty()) {
        //The first vertex in Set is the minimum distance vertex, extract it from set.
        u=(*dist_min.begin()).second; dist_min.erase(dist_min.begin());
        for(auto i=adj_list_GraphNode[u].begin(); i!=adj_list_GraphNode[u].end(); i++) {
            int v=i->vertex, w=i->weight;
            if(dist_value[v] > dist_value[u] + w) {
                dist_value[v] = dist_value[u] + w;
                dist_min.insert(make_pair(dist_value[v], v)); // the inserted item will be sorted in set
            }
        }
    }
    for_each(dist_value.begin(), dist_value.end(), [](int dist){cout<<dist<<' ';});
}
void Graph::Dijkstra_priority_queue(int u)
{
    // ElogV
    // do not update a key, but insert one more copy of it.
    // allow multiple instances of same vertex in priority queue.
    typedef pair<int,int> node;
    //greater<T> would cause the smallest element to appear as the top().
    priority_queue<node, vector<node>, greater<node>> dist_min; // Min Heap, typedef pair<int,int> node;
    vector<int> dist_value(vertex_num, INT_MAX);

    dist_min.push(make_pair(0, u));
    dist_value[u] = 0;
    while(!dist_min.empty()) {
        u=dist_min.top().second; dist_min.pop();
        for(auto i=adj_list_GraphNode[u].begin(); i!=adj_list_GraphNode[u].end(); i++) {
            int v=i->vertex, w=i->weight;
            if(dist_value[v] > dist_value[u] + w) {
                dist_value[v] = dist_value[u] + w;
                dist_min.push(make_pair(dist_value[v], v));
            }
        }
    }
    for_each(dist_value.begin(), dist_value.end(), [](int dist){cout<<dist<<' ';});
}
void Graph::BellmanFord(int u)
{
    // 1st, calculates the shortest distances which have at-most one edge in the path.
    // 2nd, calculates shortest paths with at-nost 2 edges, and so on.
    // ith, the shortest paths with at most i edges are calculated.
    // There can be maximum |V| ¡V 1 edges in any simple path, that is why the outer loop runs |v| ¡V 1 times.
    vector<int> dist_value(vertex_num, INT_MAX);

    dist_value[u] = 0;
    for(auto j=1; j<=vertex_num-1; j++) { // path of 1, 2, 3, ...|V|¡V1 edges
        for(auto u=0; u<vertex_num; u++) { // for each edge (u,v)
            for(auto i=adj_list_GraphNode[u].begin(); i!=adj_list_GraphNode[u].end(); i++) {
                int v=i->vertex, w=i->weight;
                if(dist_value[v] > dist_value[u] + w)
                    dist_value[v] = dist_value[u] + w;
            }
        }
    }

    // check for negative-weight cycles, if we can get a shorter path
    // path of |V| edges
    for(auto u=0; u<vertex_num; u++) { // for each edge (u,v)
        for(auto i=adj_list_GraphNode[u].begin(); i!=adj_list_GraphNode[u].end(); i++) {
            int v=i->vertex, w=i->weight;
            if(dist_value[v] > dist_value[u] + w)
                cout <<"Found negative-weight cycle!"<<endl;
        }
    }
    for_each(dist_value.begin(), dist_value.end(), [](int dist){cout<<dist<<' ';});
}

//Redundant Connection II
class lc685 { //Hard
public:
    vector<int> RedundantConnectionDirected(vector<vector<int>>& edges) {

    }
};

//Redundant Connection
//Return an edge that can be removed so that the resulting graph is a tree of N nodes.
class lc684 { //Medium
private:
    //time(N^2), DFS
    unordered_map<int, vector<int>> graph;
    unordered_set<int> visited;
    bool _dfs(int src, int dst) {
        if(src==dst) return true;
        visited.insert(src);
        if(!graph.count(src)||!graph.count(dst)) return false;
        for(auto next:graph.at(src)) {
            if(visited.count(next)) continue;
            if(_dfs(next,dst)) return true;
        }
        return false;
    }
    class UnionFind {
    private:
        vector<int> parent;
        vector<int> set_sz;
    public:
        UnionFind(int n) {
            parent=vector<int>(n+1,0);
            set_sz=vector<int>(n+1,0);
            iota(parent.begin(),parent.end(),0);
        }
        // Merge sets that contains u and v.
        // Return true if merged, false if u and v are already in one set.
        bool Union(int u, int v) {
            int pu=Find(u); int pv=Find(v);
            if(pu==pv) return false;
            // Meger low set_sz tree into high set_sz
            if(set_sz[pv]>set_sz[pu]) parent[pu]=pv;
            else if(set_sz[pu]>set_sz[pv]) parent[pv]=pu;
            else {
                parent[pv]=pu;
                set_sz[pv]++;
            }
            return true;
        }
        // Get the root of u
        int Find(int u) {
            // compare the path during travesal
            if(parent[u]!=u) parent[u]=Find(parent[u]);
            return parent[u];
        }
    };
public:
    vector<int> RedundantConnectionUndirected(vector<vector<int>>& edges) {
        //time(N^2), DFS
        for(auto edge:edges) {
            int src=edge[0]; int dst=edge[1];
            if(_dfs(src,dst)) return edge;
            graph[src].push_back(dst);
            graph[dst].push_back(src);
        }
        return {};

        //time(N), Union/Find
        UnionFind s(edges.size());
        for(auto edge:edges)
            if(!s.Union(edge[0],edge[1])) return edge;
        return {};
    }
};

//Network Delay Time
class lc743 { //Medium
public:
    int NetworkDelayTime(vector<vector<int>>& times, int N, int K) {
        constexpr int MAX_TIME = 101 * 100;

        //Dijkstra time(N^2->NlogN+E) space(N+E)

        //Bellman-Ford time(NE) space(N)
        vector<int> dist(N, MAX_TIME);
        dist[K - 1] = 0;
        for (int i = 0; i < N; ++i)
            for (const auto& time : times) {
                int u = time[0] - 1, v = time[1] - 1, w = time[2];
                dist[v] = min(dist[v], dist[u] + w);
            }
        int max_dist = *max_element(dist.begin(), dist.end());
        return max_dist == MAX_TIME ? -1 : max_dist;

        //Floyd-Warshall (all pairs) time(N^3) space(N^2)
        vector<vector<int>> d(N, vector<int>(N, MAX_TIME));

        for (auto time : times)
            d[time[0] - 1][time[1] - 1] = time[2];

        for (int i = 0; i < N; ++i)
            d[i][i] = 0;

        for (int k = 0; k < N; ++k)
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

        int max_time = *max_element(d[K - 1].begin(), d[K - 1].end());
        return max_time >= MAX_TIME ? - 1 : max_time;
    }
};

//Closest Leaf in a Binary Tree
//Given a binary tree where every node has a unique value, and a target key k, find
//the value of the closest leaf node to target k in the tree.
class lc742 { //Medium
private:
    unordered_map<TreeNode*,vector<TreeNode*>> graph;
    TreeNode* start;
    int target;
    void _dfs(TreeNode* node, TreeNode* par_node)
    {
        if(!node) return;
        if(node->val==target) start=node;
        if(par_node) {
            graph[node].push_back(par_node);
            graph[par_node].push_back(node);
        }
        _dfs(node->left, node);
        _dfs(node->right, node);
    }
public:
    int ClosestLeafInBinaryTree(TreeNode* root, int k) {
        //time(N) space(N)

        //use DFS to construct the undirected graph and find the start node. O(N)
        //Each node has most 3 edges (left/right/parent)
        target=k;
        _dfs(root, nullptr);

        //Use BFS to search the graph from start node to any leaf node (shortest path). O(N)
        unordered_set<TreeNode*> visited;
        queue<TreeNode*> q; int queue_size=0; q.push(start);
        while(queue_size=q.size()) {
            while(queue_size--) {
                TreeNode* curr=q.front(); q.pop();
                visited.insert(curr);
                if(!curr->left&&!curr->right) return curr->val;
                for(auto node:graph[curr])
                    if(!visited.count(node)) q.push(node);
            }
        }
        return 0;
    }
};

//Evaluate Division
class lc399 { //Medium
public:
    vector<double> EvaluateDivision(vector<pair<string, string>> equations,
                                    vector<double>& values,
                                    vector<pair<string, string>> queries) {
    }
    // dfs
    // union/find
};

//Reconstruct Itinerary
//Given a list of airline tickets represented by pairs of departure and arrival
//airports [from, to], reconstruct the itinerary in order. All of the tickets
//belong to a man who departs from JFK.
class lc332 { //Medium
private:
    // src -> {dst1, dest2, ..., destn}
    // need to remove the 1th element, so use deque
    unordered_map<string,deque<string>> trips;
    vector<string> route;
    void _dfs(string src)
    {
        auto dsts=trips[src];
        while(dsts.size()) {
            auto dst=dsts.front(); dsts.pop_front(); // remove the visited tree edges
            _dfs(dst);
        }
        route.push_back(src);
    }
public:
    vector<string> ReconstructItinerary(vector<pair<string, string>> tickets) {
        for(auto pair:tickets)
            trips[pair.first].push_back(pair.second);
        for(auto pair:trips)
            sort(pair.second.begin(),pair.second.end()); //travel in lexical order
        //take the src as a tree's root, do dfs postorder and reverse the order
        _dfs("JFK");
        return vector<string>(route.crbegin(),route.crend());
    }
};

//Course Schedule II
class lc210 { //Medium
private:
    vector<vector<int>> graph;
    vector<int> visited; //0 = unkonwn, 1 == visiting, 2 = visited
    vector<int> res;
    bool _dfs(int node) {
        if(visited[node]==1) return 1; //visiting, detect a cycle
        if(visited[node]==2) return 0; //visited, do nothing
        visited[node]=1;
        for(auto nbor:graph[node])
            if(_dfs(nbor)) return 1; //visiting, detect a cycle
        visited[node]=2;
        res.push_back(node);
        return 0; //visited, push_back
    }
public:
    vector<int> CourseScheduleII(int numCourses, vector<pair<int, int>>& prerequisites) {
        graph=vector<vector<int>>(numCourses);
        visited=vector<int>(numCourses);
        //use dfs to do topological sort and reverse the order
        for(auto p:prerequisites)
            graph[p.second].push_back(p.first); //graph[from].push_back(to);
        for(int i=0;i<numCourses;i++)
            if(_dfs(i)==1) return {}; //detect a cycle
        reverse(res.begin(),res.end());
        return res;
    }
};

//Course Schedule
class lc207 { //Medium
private:
    vector<vector<int>> graph;
    vector<int> visited; //0 = unkonwn, 1 == visiting, 2 = visited
    bool _dfs(int node) {
        if(visited[node]==1) return 1; //visiting, detect a cycle
        if(visited[node]==2) return 0; //visited, do nothing
        visited[node]=1;
        for(auto nbor:graph[node])
            if(_dfs(nbor)==1) return 1; //visiting, detect a cycle
        visited[node]=2;
        return 0; //visited, do nothing
    }
public:
    bool CourseScheduleI(int numCourses, vector<pair<int, int>>& prerequisites) {
        graph=vector<vector<int>>(numCourses);
        visited=vector<int>(numCourses, 0);
        //take it as a graph problem and check if a cycle exists
        for(auto p:prerequisites)
            graph[p.second].push_back(p.first);
        for(int i=0;i<numCourses;i++)
            if(_dfs(i)==1) return false; //detect a cycle
        return true;
    }
};

//Island Perimeter
//The perimeter of the island
class lc463 { //Easy
public:
    int IslandPerimeter(vector<vector<int>>& grid) {
        // 一個格子4個邊，若這個格子有一個neighbor就減少一個邊
        int m,n,latt=0,nbor=0;

        if(grid.empty()) return 0;
        m=grid.size(); n=grid[0].size();
        for(auto y=0; y<m; y++)
            for(auto x=0; x<n; x++)
                if(grid[y][x]) {
                    latt++;
                    if((y>0  &&grid[y-1][x]) || // up nbor
                       (y<m-1&&grid[y+1][x]) || // down nbor
                       (x>0  &&grid[y][x-1]) || // left nbor
                       (x<n-1&&grid[y][x+1]))   // right nbor
                        nbor++;
                }
        return latt*4-nbor;
    }
};

#if 0
int main()
{
#if 0
    Graph g(4);
    g.addEdge(0,1);
    g.addEdge(0,2);
    g.addEdge(1,2);
    g.addEdge(2,0);
    g.addEdge(2,3);
    g.addEdge(3,3);
    //g.traverseBFS(2);
    //g.traverseDFS(2);
    //g.traverseDFS_disconnected();
#endif // 0
#if 0
    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);
    g.topologicalSort();
#endif // 1
#if 0
    Graph g(6);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 3, 6);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 4, 4);
    g.addEdge(2, 5, 2);
    g.addEdge(2, 3, 7);
    g.addEdge(3, 5, 1);
    g.addEdge(3, 4, -1);
    g.addEdge(4, 5, -2);
    g.longestPath(1);
#endif // 0
#if 0
    Graph g(7);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(4, 1);
    g.addEdge(6, 4);
    g.addEdge(5, 6);
    g.addEdge(5, 2);
    g.addEdge(6, 0);
    cout << endl << "A mother vertex is " << g.findMotherVertex();
#endif // 1
#if 1
    Graph g(9);
    g.addEdge(0, 1, 4);
    g.addEdge(1, 0, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(7, 0, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(2, 1, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(7, 1, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(3, 2, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(8, 2, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(5, 2, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(4, 3, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(5, 3, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 4, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 5, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(7, 6, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(8, 6, 6);
    g.addEdge(7, 8, 7);
    g.addEdge(8, 7, 7);
    g.Dijkstra_vector(0); cout<<endl;
    g.Dijkstra_set(0); cout<<endl;
    g.Dijkstra_priority_queue(0); cout<<endl;
    g.BellmanFord(0); cout<<endl;
#endif // 1

    cout<<endl<<"Hello";
    return 0;
}
#endif
