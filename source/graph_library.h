
#ifndef GRAPH_LIBRARY_H
#define GRAPH_LIBRARY_H

#include <map>
#include <vector>
#include <utility> //for using pairs
#include <cstdint> // for fixed sized integers
#include <functional> //for using std::function



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
    std::map<std::pair<int,int>, E> get_edge;   
    std::vector<std::vector<std::pair<int, E> > > adj;
public:
    size_t count_node();
    size_t count_edge();
    void add_node( N& );
    void add_node( std::vector<N>& );
    std::vector<traversal<N,int32_t> > bfs(N&, int depth = INT32_MAX);
    std::vector<traversal<N,int32_t> > dfs(N&, int depth = INT32_MAX);
    /*
        Read more about default arguments in fucntions
        https://stackoverflow.com/questions/32105975/why-cant-i-have-template-and-default-arguments
    */
};

/*
    How to access superclass member variables
    https://stackoverflow.com/questions/4643074/why-do-i-have-to-access-template-base-class-members-through-the-this-pointer
    https://stackoverflow.com/questions/4010281/accessing-protected-members-of-superclass-in-c-with-templates
*/

template<typename N, typename E>
class Directed_Graph :
    public virtual Base<N, E>
{
    public:
        using Base<N, E> :: idx;
        using Base<N, E> :: node;
        using Base<N, E> :: n;
        using Base<N, E> :: e;
        using Base<N, E> :: adj;
        

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
        const bool is_same(int,int);
        int find_size(int);
        int find_parent(int);
        void do_union(int,int);
};

template<typename N, typename E>
class Undirected_Graph:
    public virtual Base<N, E>
{     
    public:
        using Base<N, E> :: idx;
        using Base<N, E> :: node;
        using Base<N, E> :: n;
        using Base<N, E> :: e;
        using Base<N, E> :: adj;

        /*
            For more on how to return different types based on tepmplate read at
            https://stackoverflow.com/questions/48199813/how-to-use-condition-to-check-if-typename-t-is-integer-type-of-float-type-in-c
            https://stackoverflow.com/questions/44864576/returning-different-type-from-a-function-template-depending-on-a-condition
        */
        template<typename T>
            auto  prims_mst(std::function <T(E)>);
        template<typename T>
            auto krushkal_mst(std::function <T(E)>);
};


template<typename N,typename E> //see about how to implement only typename N in this class so that if true is passed is_weighted then only take 4th argument otherwise no
class Unweighted_Graph:
    public virtual Base<N, E>
{
    public:
        using Base<N, E> :: idx;
        using Base<N, E> :: node;
        using Base<N, E> :: n;
        using Base<N, E> :: e;
        using Base<N, E> :: adj;


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
            auto dijkstra(int, std::function< T (E)> );   //total 2 types of each for float and int
        template<typename T>
            auto bellman_ford(int, std::function< T (E)> );
    public:
        using Base<N, E> :: idx;
        using Base<N, E> :: node;
        using Base<N, E> :: n;
        using Base<N, E> :: e;
        using Base<N, E> :: adj;


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

template<typename N,typename E>
struct full_edge
{
    N u,v;
    E edge;
};



template<bool is_integral> struct get_data_type; //for getting which data type to be used for calculations in edge weights



#include <queue>
#include <array>
#include <type_traits>


template <typename N, typename E>
template <typename T>
auto Undirected_Graph<N, E>::krushkal_mst(std::function<T(E)> get_weight)
{
    /*
        Read more about is_integral<T>::value and is_integral_v<T> at
        https://en.cppreference.com/w/cpp/types/is_integral
    */
    
    if constexpr (std::is_integral_v<T>) // constexpr only necessary on first statement
    {
        using type = typename int64_t;
    }
    else if (std::is_floating_point_v<T>) // automatically constexpr
    {
        using type = typename long double;
    }
    else
    {
        /*
            Donot use assert false beacuse it can be overrideen by -DNDEBUG flag
            Read more at https://stackoverflow.com/questions/57908992/better-alternatives-to-assertfalse-in-c-c
        */
        //assert(false)
        std :: cout<< "You didnot pass a valid function" << std :: endl;
        std :: abort();
    }
    // else throw error; //see how to throw an error
    type total_weight = 0;
    std::priority_queue<std::pair<type, std::array<int, 2> > ,
                        std::vector<std::pair<type, std::array<int, 2> > > ,
                        std::greater<std::pair<type, std::array<int, 2> > > > pq;

    for (size_t i = 0; i < n; i++)
    {
        for(auto &[x,y]:adj[i])
        {
            pq.push({get_weight(y),{x,i}});
        }
    }
    disjoint_set_union DSU(n);

    std::vector<full_edge<N,E> > v;

    while(!pq.empty())
    {
        auto [weight_of_edge, index_of_nodes] = pq.top();
        pq.pop();
        if(DSU.is_same(index_of_nodes[0],index_of_nodes[1]) == false)
        {
            DSU.do_union(index_of_nodes[0],index_of_nodes[1]);
            total_weight += weight_of_edge;                                                       // |---> implement get_edge function or vector
            v.push_back(full_edge<N,E> {node[index_of_nodes[0]], node[index_of_nodes[1]], get_edge[{index_of_nodes[0],index_of_nodes[1]}]});
        }
    }
    return make_pair(total_weight,v) ;
}

#include "gmap.inc"
#include "struct_traversal.inc"
#include "Base.inc"
#include "Directed_Graph.inc"
#include "disjoint_set_union.inc"
#include "get_data_type.inc"

#endif