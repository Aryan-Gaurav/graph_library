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
            for (auto &[adjacent_node, edge] : adj[current_node])
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
auto Weighted_Graph<N, E>::shortest_path_faster_algorithm(int source_node, bool &is_negative_cycle, const std::function <T(E)> &get_weight) 
{
    /*
    
    The Shortest Path Faster Algorithm (SPFA) is an improvement of the Bellman–​Ford algorithm for finding single source shortest path in a weighted graph.
    Read more at https://cp-algorithms.com/graph/bellman_ford.htmlhttps://cp-algorithms.com/graph/bellman_ford.html
    https://en.wikipedia.org/wiki/Shortest_Path_Faster_Algorithm

    */

    using type = typename get_data_type<std::is_integral<T>::value>::type; //find which type of variable to use

    std::vector<int> parent(n, -1), number_of_relaxation(n, 0);
    std::vector<type> distance(n, INF);
    bool inqueue[n] = {false};
    std::queue<int> Queue;

    Queue.push(source_node);
    distance[source_node] = 0;
    inqueue[source_node] = true;
    number_of_relaxation[source_node] = 1;

    while (Queue.empty() == false && is_negative_cycle == false)
    {
        auto current_node = Queue.front();
        Queue.pop();
        inqueue[current_node] = false;
        for (auto &[adjacent_node, edge] : adj[current_node])
        {
            if (auto new_weight = distance[current_node] + get_weight(edge); new_weight < distance[adjacent_node])
            {
                distance[adjacent_node] = new_weight;
                parent[adjacent_node] = current_node;
                if (inqueue[adjacent_node] == false)
                {
                    Queue.push(adjacent_node);
                    inqueue[adjacent_node] = true;
                    number_of_relaxation[adjacent_node] += 1;
                    if (number_of_relaxation[adjacent_node] > n) //if a node is used to relax more than n time then there must be a negtive cycle
                    {
                        is_negative_cycle = true;
                        break;
                    }
                }
            }
        }
    }
    std::vector<traversal<N,type> > ans(n);
    for (size_t i = 0; i < n; i++)
    {
        if (is_negative_cycle == true)
        {
            ans[i].set_value(node[i], node[i], -INF);
        }
        else // no negative cycle is present
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

    if (is_negative_weight == false)
    {
        return dijkstra(idx[src], get_weight);
    }
    else
    {
        bool is_negative_cycle = false;
        return shortest_path_faster_algorithm(idx[src], is_negative_cycle, get_weight);
    }
}

template<typename N, typename E> 
template<typename T> 
auto Weighted_Graph<N, E>::all_pair_shortest_path(const std::function<T(E)> &get_weight) //Floyd Warshall Algorithm, Runtime O(V^3)
{
    if (std::is_integral<T>::value == false && std::is_floating_point<T>::value == false) //this means the return type is neither integral nor floating point
    {
        /*
            Donot use assert false beacuse it can be overrideen by -DNDEBUG flag
            Read more at https://stackoverflow.com/questions/57908992/better-alternatives-to-assertfalse-in-c-c
        */
        //assert(false)
        std ::cout << "You did not pass a valid function in All Pair Shortest Path. Please provide a valid function." << std ::endl;
        std ::cout << "Now the program will abort" << std ::endl;
        std ::abort();
    }

    using type = typename get_data_type<std::is_integral<T>::value>::type; //find which type of variable to use

    type distance[n][n];

    for (size_t from = 0; from < n; from++) //filling the distance matric
    {
        for (size_t to = 0; to < n; to++)
        {
            if (from == to)
            {
                distance[from][from] = 0;
            }
            else
            {
                distance[from][to] = INF;
            }
        }
    }

    for (size_t from = 0; from < n; from++)
    {
        for (auto &[to, edge] : adj[from])
        {
            distance[from][to] =  get_weight(edge);
        }
    }

    for (size_t intermediate = 0; intermediate < n; intermediate++)
    {
        for (size_t from = 0; from < n; from++)
        {
            for (size_t to = 0; to < n; to++)
            {
                distance[from][to] = std::min(distance[from][to], distance[from][intermediate] + distance[intermediate][to]);
            }
        }
    }
    std::vector<node_pair<N, type> > ans(n*n);

    for (size_t from = 0; from < n; from++)
    {
        for (size_t to = 0; to < n; to++)
        {
            ans[from * n + to].set_value(node[from], node[to], distance[from][to]);
        }
    }

    return ans;
}


template<typename N, typename E> 
template<typename T> 
bool Weighted_Graph<N, E>::is_negative_weight_cycle(N &src, const std::function <T(E)> &get_weight)
{
    if (std::is_integral<T>::value == false && std::is_floating_point<T>::value == false) //this means the return type is neither integral nor floating point
    {
        /*
            Donot use assert false beacuse it can be overrideen by -DNDEBUG flag
            Read more at https://stackoverflow.com/questions/57908992/better-alternatives-to-assertfalse-in-c-c
        */
        //assert(false)
        std ::cout << "You did not pass a valid function in Negative Cycle Detection. Please provide a valid function." << std ::endl;
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

    if (is_negative_weight == false)
    {
        return false;
    }
    else
    {
        bool checker = false;
        shortest_path_faster_algorithm(idx[src], checker, get_weight);
        return checker;
    }
}