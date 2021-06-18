#include <queue>
#include <array>
#include <cstring> //for using memeset to set values 0 and -1 in arrays
#include <type_traits> //for using std::is_integral<T>::value

template<class N, class E> 
template<class T> 
auto Undirected_Graph<N, E> :: prims_minimum_spanning_tree (const std::function<T (E)> &get_weight)
{
    if(std::is_integral<T>::value == false && std::is_floating_point<T>::value == false) //this means the return type is neither integral nor floating point
    {
        /*
            Donot use assert false beacuse it can be overrideen by -DNDEBUG flag
            Read more at https://stackoverflow.com/questions/57908992/better-alternatives-to-assertfalse-in-c-c
        */
        //assert(false)
        std :: cout<< "You did not pass a valid function in Prims Minimum Spanning Tree. Please provide a valid function." << std :: endl;
        std :: cout<< "Now the program will abort" <<std :: endl;
        std :: abort();
    }

    using type = typename get_data_type<std::is_integral<T>::value>::type; //find which type of variable to use

    type total_weight = 0;
    std::vector<full_edge<N,E> > v;

    std::vector<type> distance(n,INF);
    bool in_mst[n] = { false };
    int parent[n];
    memset(parent,-1,sizeof(parent));

    std::priority_queue<std::pair<type, int> ,
                        std::vector<std::pair<type, int> > ,
                        std::greater<std::pair<type, int> > > min_heap;

    min_heap.push({ 0, 0 });
    distance[0] = 0;
    while ( min_heap.empty() == false)
    {
        auto [weight, current_node] = min_heap.top();
        min_heap.pop();
        if(in_mst[current_node] == false)
        {
            in_mst [ current_node ] = true;
            total_weight += weight;
            if(parent[current_node] != -1)                                                      // |------>Remember to implement it
                v.push_back(full_edge<N,E> { node[current_node], node[parent[current_node]], get_edge[{ current_node, parent[current_node] }] } );
            for (auto &[ adjacent_node, edge ]: adj[ current_node ])
            {
                if(in_mst[adjacent_node] == false)
                {
                    if(auto new_weight = get_weight(edge); distance[adjacent_node] > new_weight)
                    {
                        distance[adjacent_node] = new_weight;
                        parent[adjacent_node] = current_node;
                        min_heap.push({new_weight, adjacent_node});
                    }
                }
            }
        }
    }


    return make_pair(total_weight, v);
}




template <typename N, typename E>
template <typename T>
auto Undirected_Graph<N, E>::krushkal_minimum_spanning_tree(const std::function<T(E)> &get_weight)
{
    /*
        Read more about is_integral<T>::value and is_integral_v<T> at
        https://en.cppreference.com/w/cpp/types/is_integral
    */
    
    if(std::is_integral<T>::value == false && std::is_floating_point<T>::value == false) //this means the return type is neither integral nor floating point
    {
        /*
            Donot use assert false beacuse it can be overrideen by -DNDEBUG flag
            Read more at https://stackoverflow.com/questions/57908992/better-alternatives-to-assertfalse-in-c-c
        */
        //assert(false)
        std :: cout<< "You did not pass a valid function in Krushkal Minimum Spanning Tree" << std :: endl;
        std :: cout<< "Now the program will abort" <<std :: endl;
        std :: abort();
    }

    using type = typename get_data_type<std::is_integral<T>::value>::type; //find which type of variable to use


    type total_weight = 0;
    std::vector<full_edge<N,E> > v;

    std::priority_queue<std::pair<type, std::array<int, 2> > ,
                        std::vector<std::pair<type, std::array<int, 2> > > ,
                        std::greater<std::pair<type, std::array<int, 2> > > > min_heap; //declare a min priority queue

    for (size_t i = 0; i < n; i++)
    {
        for(auto &[x,y]:adj[i])
        {
            min_heap.push({ get_weight(y), { x, i } });
        }
    }

    disjoint_set_union DSU(n);

    while (min_heap.empty() == false)
    {
        auto [weight_of_edge, index_of_nodes] = min_heap.top();
        min_heap.pop();
        if(DSU.is_same(index_of_nodes[0], index_of_nodes[1]) == false)
        {
            DSU.do_union(index_of_nodes[0], index_of_nodes[1]);
            total_weight += weight_of_edge;                                                       // |---> implement get_edge function or vector
            v.push_back(full_edge<N,E> {node[index_of_nodes[0]], node[index_of_nodes[1]], get_edge[{index_of_nodes[0],index_of_nodes[1]}]});
        }
    }
    return make_pair(total_weight,v) ;
}
