#include <type_traits>
#include <iostream>
#include <vector>
#include <queue>
#include <utility>


//Function definations for Weighted Graph class
template<typename N, typename E> 
template<typename T> 
auto Weighted_Graph<N, E>::dijkstra(int source_node, const std::function <T(E)> &get_weight)
{
    using type = typename get_data_type<std::is_integral<T>::value>::type; //find which type of variable to use

    bool is_visited[n] = {false};
    std::vector<int> parent(n, -1);
    std::vector<type> distance(n, INF);
    std::priority_queue< std::pair<type,int>, 
                        std::vector<std::pair<type,int> >, 
                        std::greater<std::pair<type,int> > > min_heap;
    
    std::vector<traversal<N,type> > ans(n);

    min_heap.push({0,source_node});

    while (min_heap.empty() == false)
    {
        auto [current_distance, current_node] = min_heap.top();
        min_heap.pop();
        if (is_visited[current_node] == false)
        {
            is_visited[current_node] = true;
            distance[current_node] = current_distance;
            for (auto [adjacent_node, edge] : adj[current_node])
            {
                if (is_visited[adjacent_node] == false)
                {
                    if (auto new_distance = current_distance + get_weight(edge); new_distance < distance[adjacent_node])
                    {
                        distance[adjacent_node] = new_distance;
                        parent[adjacent_node] = current_node;
                        min_heap.push({new_distance, adjacent_node});
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (parent[i] != -1)
        {
            ans[i].set_value(node[i], node[parent[i]], distance[i]);
        }
        else
        {
            ans[i].set_value(node[i], node[i], distance[i]);
        }
    }

    return ans;

}



template<typename N, typename E> 
template<typename T> 
auto Weighted_Graph<N, E>::single_source_shortest_path(N &src, const std::function <T(E)> &get_weight)
{
    if (std::is_integral<T>::value == false && std::is_floating_point<T>::value == false) //this means the return type is neither integral nor floating point
    {
        /*
            Donot use assert false beacuse it can be overrideen by -DNDEBUG flag
            Read more at https://stackoverflow.com/questions/57908992/better-alternatives-to-assertfalse-in-c-c
        */
        //assert(false)
        std ::cout << "You did not pass a valid function in Single Source Shortest Path. Please provide a valid function." << std ::endl;
        std ::cout << "Now the program will abort" << std ::endl;
        std ::abort();
    }

    bool is_negative_weight = false;
    for (size_t i = 0; i < n && is_negative_weight == false; i++)
    {
        for (auto &[w, edge] : adj[i])
        {
            if (get_weight(edge) < 0)
            {
                is_negative_weight = true;
                break;
            }
        }
    }

    // if (is_negative_weight == false)
    // {
        return dijkstra(idx[src], get_weight);
    // }
    // else
    // {
    //     return shortest_path_faster_algorithm(idx[src], get_weight);
    // }
}