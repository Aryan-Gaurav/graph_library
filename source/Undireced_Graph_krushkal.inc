#include <queue>
#include <array>
#include <type_traits> //for using std::is_integral<T>::value


template <typename N, typename E>
template <typename T>
auto Undirected_Graph<N, E>::krushkal_minimum_spanning_tree(std::function<T(E)> get_weight)
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

    using type = typename get_type<std::is_integral<T>::value>::type; //find which type of variable to use


    type total_weight = 0;

    std::priority_queue<std::pair<type, std::array<int, 2> > ,
                        std::vector<std::pair<type, std::array<int, 2> > > ,
                        std::greater<std::pair<type, std::array<int, 2> > > > pq; //declare a min priority queue

    for (size_t i = 0; i < n; i++)
    {
        for(auto &[x,y]:adj[i])
        {
            pq.push({ get_weight(y), { x, i } });
        }
    }
    disjoint_set_union DSU(n);

    std::vector<full_edge<N,E> > v;

    while (!pq.empty())
    {
        auto [weight_of_edge, index_of_nodes] = pq.top();
        pq.pop();
        if(DSU.is_same(index_of_nodes[0], index_of_nodes[1]) == false)
        {
            DSU.do_union(index_of_nodes[0], index_of_nodes[1]);
            total_weight += weight_of_edge;                                                       // |---> implement get_edge function or vector
            v.push_back(full_edge<N,E> {node[index_of_nodes[0]], node[index_of_nodes[1]], get_edge[{index_of_nodes[0],index_of_nodes[1]}]});
        }
    }
    return make_pair(total_weight,v) ;
}
