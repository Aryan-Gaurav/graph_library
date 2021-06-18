#include <type_traits>
#include <vector>


// Function definations for Unweighted Graphs

template<class N, class E> 
std::vector<traversal<N, int> > Unweighted_Graph<N, E>::single_source_shortest_path(N &source_node)
{
    return bfs(source_node);
}

template<class N, class E> 
std::vector <node_pair<N,int> > Unweighted_Graph<N, E>::all_pair_shortest_path()
{
    vector<node_pair<N,int>> ans;
    for(size_t i=0;i<n;i++)
    {
        auto temp = bfs(i);
        for(auto &x:temp)
        {
            ans.push_back(node_pair<N,int> {node[i],x.node,x.distance});
        }
    }
    return ans;
}