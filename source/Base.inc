#include <queue>    //for breadth_first_search (bfs)
#include <stack>    //for depth_first_search (dfs)

// Functions of Base Class

template<typename N,typename E>
size_t Base<N, E> :: count_node()
{
    return n;
}

template<typename N,typename E>
size_t Base<N, E> :: count_edge()
{
    return e;
}

template<typename N, typename E>
void Base<N, E> :: add_node( N &temp)
{
	if(idx.ispresent(temp) == false)
	{
        idx[temp] = n;
        node[n] = temp;
        adj.push_back({});  //increase the size by 1
        n++;
	}
}

template<typename N, typename E>
void Base<N, E> :: add_node( std::vector<N> &v)
{
	for(auto &x : v)
	{
        add_node(x);
	}
}

//Implementation of Breadth First Search


template<typename N, typename E>
std::vector<traversal<N,int> > Base<N, E> :: bfs( N &source_node, int depth)
{
    int src = idx[source_node];
    bool vis[n] = { 0 };
    int dis[n];
    std::queue <int> que;
    std::vector<traversal<N, int> > ans;
    ans.push_back(traversal<N,int>{source_node, source_node , 0});
    que.push(src);
    vis[src]=1;
    dis[src]=0;
    while(!que.empty())
    {
        int t = que.front();
        que.pop();
        for(auto &[x,y]:adj[t])
        {
            if(! vis[x] && dis[x] < depth-1)
            {
                vis[x] = 1;
                dis[x] = dis[t] + 1;
                ans.push_back( traversal <N,int> {node[x], node[t], dis[x] } );
                que.push(x);
            }
        }
    }
    return ans;
}

//Implementation of Depth First Search

template<typename N, typename E>
std::vector<traversal<N, int> > Base<N, E> ::dfs(N& source_node, int depth)
{
    int src = idx[source_node];
    bool vis[n] = { 0 };
    int dis[n];
    std::stack <int> stk;
    std::vector<traversal<N, int> > ans;
    ans.push_back(traversal<N,int> { source_node, source_node , 0 });
    stk.push(src);
    vis[src] = 1;
    dis[src] = 0;
    while (! stk.empty() )
    {
        int t = stk.top();
        stk.pop();
        for (auto& [x, y] : adj[t])
        {
            if (!vis[x] && dis[x] < depth - 1)
            {
                vis[x] = 1;
                dis[x] = dis[t] + 1;
                ans.push_back(traversal<N,int> { node[x], node[t], dis[x] });
                stk.push(x);
            }
        }
    }
    return ans;
}



