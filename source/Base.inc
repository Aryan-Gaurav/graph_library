#include <queue> //for breadth_first_search (bfs)
#include <stack> //for depth_first_search (dfs)

// Functions of Base Class

template <typename N, typename E>
size_t Base<N, E>::count_node()
{
    return n;
}

template <typename N, typename E>
size_t Base<N, E>::count_edge()
{
    return e;
}

template <typename N, typename E>
void Base<N, E>::add_node(N &temp)
{
    if (idx.ispresent(temp) == false)
    {
        idx[temp] = n;
        node[n] = temp;
        adj.push_back({}); //increase the size by 1
        n += 1;
    }
}

template <typename N, typename E>
void Base<N, E>::add_node(std::vector<N> &v)
{
    for (auto &x : v)
    {
        add_node(x);
    }
}

template<typename N, typename E> 
void Base<N,E> :: add_edge(N &u, N &v, E ed)
{
    if(idx.ispresent(u) == false || idx.ispresent(v) == false) //trying to add an edge whose node is not in Graph
    {
        std::cout<<"Either one or both nodes are not present in the Graph. Please add them and try again." << std::endl;
        return;
    }
    int i = idx[u] , j = idx[v];
    if(get_edge.find({i,j}) != get_edge.end())
    {
        std::cout<<"The edge has already been added in the Graph between these two nodes."<<std::endl;
        return; 
    }
    adj[i].push_back({j,ed});
    get_edge[{ i, j }] = ed;
    e += 1; //increase the count of edges
    if(is_directed == false)
    {
        adj[j].push_back({i,ed});
        get_edge[{j, i}] = ed;
    }

}

//Implementation of Breadth First Search

template <typename N, typename E>
std::vector<traversal<N, int>> Base<N, E> :: breadth_first_search_by_index(int src, bool is_for_sssp, int depth)
{
    bool vis[n] = {0};
    int dis[n];
    std::queue<int> que;
    std::vector<traversal<N, int>> ans;
    ans.push_back(traversal<N, int>(node[src], node[src], 0));
    que.push(src);
    vis[src] = 1;
    dis[src] = 0;
    while (!que.empty())
    {
        int t = que.front();
        que.pop();
        for (auto &[x, y] : adj[t])
        {
            if (!vis[x] && dis[x] < depth - 1)
            {
                vis[x] = 1;
                dis[x] = dis[t] + 1;
                ans.push_back(traversal<N, int>(node[x], node[t], dis[x]));
                que.push(x);
            }
        }
    }
    if (is_for_sssp == true) //if this is called for Single Source Shortest Path, then add other nodes which are unreachable 
    {
        for (size_t i = 0; i < n; i++)
        {
            if (vis[i] == false)
            {
                ans.push_back(traversal<N, int>(node[i], node[i], 2e9));
            }
        }
    }
    return ans;
}

template <typename N, typename E>
std::vector<traversal<N, int>> Base<N, E>::bfs(N &source_node, int depth)
{
   int src = idx[source_node];
   return  breadth_first_search_by_index(src, false, depth);
}

//Implementation of Depth First Search

template <typename N, typename E>
std::vector<traversal<N, int>> Base<N, E>::dfs(N &source_node, int depth)
{
    int src = idx[source_node];
    bool vis[n] = { 0 };
    int dis[n];
    std::stack<int> stk;
    std::vector<traversal<N, int>> ans;
    ans.push_back(traversal<N, int>(source_node, source_node, 0));
    stk.push(src);
    vis[src] = 1;
    dis[src] = 0;
    while (!stk.empty())
    {
        int t = stk.top();
        stk.pop();
        for (auto &[x, y] : adj[t])
        {
            if (!vis[x] && dis[x] < depth - 1)
            {
                vis[x] = 1;
                dis[x] = dis[t] + 1;
                ans.push_back(traversal<N, int>(node[x], node[t], dis[x]));
                stk.push(x);
            }
        }
    }
    return ans;
}
