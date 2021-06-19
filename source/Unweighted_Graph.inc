#include <type_traits>
#include <vector>


// Function definations for Unweighted Graphs

template <typename N, typename E>
std::vector<traversal<N, int>> Unweighted_Graph<N, E>::single_source_shortest_path(N &source_node)
{
    return Base<N,E>::breadth_first_search_by_index(source_node,true);
}

template <typename N, typename E>
std::vector<node_pair<N, int>> Unweighted_Graph<N, E>::all_pair_shortest_path()
{
    std::vector<node_pair<N, int>> ans;
    for (int i = 0; i < n; i++)
    {
        auto temp = Base<N,E>::breadth_first_search_by_index(i, true); //protected member of superclass so acess by scope resolution
        for (auto &x : temp)
        {
            ans.push_back(node_pair<N, int>(node[i], x.node, x.distance));
        }
    }
    return ans;
}