
#ifndef GRAPH_LIBRARY_H
#define GRAPH_LIBRARY_H

#include <map>
#include <vector>
#include <utility> //for using pairs
#include <cstdint> // for fixed sized integers
#include <functional> //for using std::function
#include <queue>    //for breadth_first_search (bfs)
#include <stack>    //for depth_first_search (dfs)
#include <iostream>

#define INF 4e18 //infinity for comparison purposes in Dijkstra and Bellman Ford


template<typename K,typename V> // <key, value> pair
class gmap
{
	private:
		std::map<K*, V> mp;
	public:
		V& operator[](K&);  //remember why (const K&) didn't work
		const bool ispresent(K&);
};

template<typename N, typename T>
struct traversal
{
    N node, parent;
    T distance;
    traversal();
    void set_value(N, N, T);
    void print();
};

template<typename N, typename T>
struct node_pair
{
        N from,to;
        T dis;
        node_pair();
        void set_value(N, N, T);
        void print();
};

template<typename N, typename E>
class Base
{
private:
    /*
        This is to ensure object of Base class can't be created.
        See more at https://stackoverflow.com/questions/13668336/how-to-prevent-construction-of-a-classs-object
        These delete can be put in public, private or protected doesn't matter
        1st is default constructor
        2nd is Copy Constructor
        3rd is Move
    */
	
    // Base() = delete;
    // Base(const Base&) = delete;
    // Base(Base&&) = delete;
    // ~Base() = delete;
    // Commented for checking purposes
protected:
    gmap<N, int> idx;
    std::map<int, N> node;
    int n = 0, e = 0;
    std::map<std::pair<int,int>, bool> edg;   
    std::vector<std::vector<std::pair<int, E> > > adj;
public:
    size_t count_node();
    size_t count_edge();
    void add_node( N& );
    void add_node( std::vector<N>& );
    std::vector<traversal<N,int32_t> > bfs(N&, int);
    std::vector<traversal<N,int32_t> > dfs(N&, int);
};

template<typename N, typename E>
class Directed_Graph :
    public virtual Base<N, E>
{
    public:
        bool is_dag();
        std::vector<std::vector<N> > scc();
        std::vector<N> topo_sort();
};

class disjoint_set_union    //required for krushkal algorithm
{
    private:
        std::vector<int> parent, size;
    public:
        disjoint_set_union(int);
        int find_parent(int);
        void do_union(int,int);
};

template<typename N, typename E>
class Undirected_Graph:
    public virtual Base<N, E>
{     
    public:
        template<T>
            auto  prims_mst(std::function <T(E)>);
        template<T>
            auto krushkal_mst(std::function <T(E)>);
};


template<typename N,typename E> //see about how to implement only typename N in this class so that if true is passed is_weighted then only take 4th argument otherwise no
class Unweighted_Graph:
    public virtual Base<N, E>
{
    public:
        void add_edge(N&, N&);

        std::vector <traversal<N,int> > single_source_shortest_path(N&);
        std::vector <node_pair<N,int> > all_pair_shortest_path();
};

template<typename N, typename E>
class Weighted_Graph:
    public virtual Base<N, E>
{
    private:
        template<typename T>
            auto Dijkstra(int, std::function< T (E)> );   //total 2 types of each for float and int
        template<typename T>
            auto Bellman_Ford(int, std::function< T (E)> );
    public:
        void add_edge(N&, N&, E&);   //distinction of function so no abuse of both add edge methods
        
        
        template<typename T>
            auto single_source_shortest_path( N&, std::function< T (E)> );
        template<typename T>
            auto all_pair_shortest_path( std::function< T (E)> );
        template<typename T>
            bool is_neg_cycle( std::function< T (E)> );

        
};

template<typename N=int, bool is_directed=0, bool is_weighted=0, typename E = int>
class graph:
    public virtual std::conditional<is_directed, Directed_Graph<N,E>, Undirected_Graph<N,E> >::type,
    public virtual std::conditional<is_weighted, Weighted_Graph<N,E>, Unweighted_Graph<N,E> >::type
{
    public:
        graph(int);
        graph();
        void remove_node(N&);
        void remove_edge(N&, N&);
};


//Functions definations for gmap class

template<typename K, typename V>
V& gmap<K, V>::operator[](K& key)
{
    return mp [ & key ];
}

template<typename K, typename V>
const bool gmap<K, V>::ispresent(K& key)
{
    return mp.find( & key ) != mp.end();
}

//Functions definations for struct traversal

template<typename N, typename T>
traversal<N, T> :: traversal()
{
    distance = T(2e9);  //typecast 2e9 ~ INT_MAX
}

template<typename N, typename T>
void traversal<N, T> :: set_value(N a, N b, T dis)
{
    node = a;
    parent = b;
    distance = dis;
}

template<typename N, typename T>
void traversal<N, T> :: print()
{
    node.print();
    std::cout << "<--";
    parent.print();
    std::cout << distance << std::endl;
}


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

template<typename N, typename E>
std::vector<traversal<N,int> > Base<N, E> :: bfs( N &source_node, int depth = INT32_MAX)
{
    int src = idx[source_node];
    bool vis[n] = { 0 };
    int dis[n];
    std::queue <int> que;
    std::vector<traversal<N, int> > ans;
    ans.push_back(traversal{source_node, source_node , 0});
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
                ans.push_back( traversal {node[x], node[t], dis[x] } );
                que.push(x);
            }
        }
    }
    return ans;
}

template<typename N, typename E>
std::vector<traversal<N, int> > Base<N, E> ::dfs(N& source_node, int depth = INT32_MAX)
{
    int src = idx[source_node];
    bool vis[n] = { 0 };
    int dis[n];
    std::stack <int> stk;
    std::vector<traversal<N, int> > ans;
    ans.push_back(traversal{ source_node, source_node , 0 });
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
                ans.push_back(traversal{ node[x], node[t], dis[x] });
                stk.push(x);
            }
        }
    }
    return ans;
}


//function definations of Directed_Graph
template<typename N, typename E>
bool Directed_Graph<N, E> ::is_dag()    //TODO same implementation using stack i.e. without the recursive function
{
    int vis[n] = { 0 };


    /*
        Recursive lambdas are not possible without removing auto with std::function
        Read more at http://pedromelendez.com/blog/2015/07/16/recursive-lambdas-in-c14/
        https://stackoverflow.com/questions/2067988/recursive-lambda-functions-in-c11
    */

    auto detect = [&](int y)->bool
    {
        auto lambda = [&](int src, const auto& func)->bool
        {
            vis[src] = 1; //color the node as gray
            bool isok = true;

            for (auto& [x, y] : adj[src])
            {
                if (vis[x] == 0)
                {
                    isok = isok && func(x, func);
                }
                else if (vis[x] == 1)
                {
                    return false;
                }
            }
            vis[src] = 2;   //color the node as black
            return isok;
        };
        return lambda(src, lambda);
    };

    
    for (size_t i = 0; i < n; i++)
    {
        if (vis[i] == 0)
        {
            if (detect(i) == false)
                return true;
        }
    }
    return false;
}

template<typename N, typename E>
std::vector<std::vector<N> >  Directed_Graph<N, E> ::scc()
{
    //Kosaraju algorithm
    std::stack<int> stk;
    bool vis[n] = { 0 };

}

template<typename N, typename E>
std::vector<N> Directed_Graph<N, E> ::topo_sort()
{
    bool vis[n] = { 0 };
    int current_time = 0;
    int in_time[n], out_time[n];
    auto detect = [&](int y)->bool              //One possible improvement is to replace these lambda functions by a private function in the class itself
    {
        auto lambda = [&](int src, const auto& func)->bool
        {
            current_time += 1;
            in_time[src] = current_time;
            vis[src] = 1; //color the node as gray
            bool isok = true;

            for (auto& [x, y] : adj[src])
            {
                if (vis[x] == 0)
                {
                    isok = isok && func(x, func);
                }
                else if (vis[x] == 1)
                {
                    return false;
                }
            }
            current_time += 1;
            out_time[src] = current_time;
            vis[src] = 2;   //color the node as black
            return isok;
        };
        return lambda(src, lambda);
    };

    for (size_t i = 0; i < n; i++)
    {
        if (vis[i] == 0)
        {
            if (detect(i) == false)
            {
                return {};
            }
        }
    }
    std::vector<int> v(n);
    for (size_t i = 0; i < n; i++)
    {
        v[i] = i;
    }
    sort(v.begin(), v.end(), [&](int i, int j)  //sort the nodes by decreasing out times for topological sort. For more details refer Introduction to Algorithms by Cormen
        {
            return out_time[i] > out_time[j];
        });

    std::vector<N> ans(n);
    for (size_t i = 0; i < n; i++)
    {
        ans[i] = node[v[i]];
    }

    return ans;
}


//Implementation of Disjoint Set Union data structure

disjoint_set_union :: disjoint_set_union(int n)
{
    parent.resize(n+1);
    size.resize(n+1);
    for(size_t i=0;i<n;i++)
    {
        parent[i] = i;
        size[i] = 1;
    }
}

int disjoint_set_union :: find_parent(int x)
{
    if(parent[x] == x)
        return x;
    parent [x] = find_parent(parent [x] );  //try to implemtnt using stack
    return parent[x];
}

void disjoint_set_union :: do_union(int x,int y)
{
    int px = find_parent(x), py = find_parent(y);
    if(px == py)
        return;
    if(size[px] < size[py])
    {
        do_union(y,x);
        return;
    }
    size[px] += size[py];
    parent[py] = px;
}

#endif