
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

template<bool is_integral> struct get_data_type; //for getting which data type to be used for calculations in edge weights

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

template<typename N, typename T>
struct traversal
{
    N node, parent;
    T distance;
    traversal();
    traversal(N, N, T);
    void set_value(N, N, T);
};


template<typename N, typename T>
struct node_pair
{
        N from,to;
        T distance;
        node_pair();
        node_pair(N,N,T);
        void set_value(N, N, T);
};


template<typename N,typename E>
struct full_edge
{
    N u,v;
    E edge;
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
    int n, e;
    std::map<std::pair<int,int>, E> get_edge;   
    std::vector<std::vector<std::pair<int, E> > > adj;
    bool is_weighted, is_directed;  //will get value from main graph class from template arguments
    std::vector<traversal<N,int32_t> > breadth_first_search_by_index(int, bool is_for_sssp, int depth = INT32_MAX);
public:
    size_t count_node();
    size_t count_edge();
    void add_node( N& );
    void add_node( std::vector<N>& );
    /*
        This 1 has been added to ensure that in case of unweighted graph and user tries to insert using (N&, N&) it works.
        Remember that it works only when user donot specify a specific data type for Edges.
    */
    void add_edge(N&, N&, E = 1 );
    // void remove_node(N&);
    // void remove_edge(N&, N&);
    std::vector<traversal<N,int> > bfs(N&, int depth = INT32_MAX);
    std::vector<traversal<N,int> > dfs(N&, int depth = INT32_MAX);
    /*
        Read more about default arguments in functions
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
    public virtual Base<N, E>   //try to write different algo for single source shortest path for a DAG
{
    protected:                  //changed the scope of using. Earlier was in public, so was exposed to the user and can be misused
        using Base<N, E> :: node;
        using Base<N, E> :: n;
        using Base<N, E> :: adj;
        using Base<N, E> :: is_weighted;
        using Base<N, E> :: is_directed;

    public:
        
        // bool detect_cycle(int, int, std::vector<bool>, std::vector<int>, std::vector<int>);  //some error check once
        bool is_dag();
        std::vector<std::vector<N> > scc();
        std::vector<N> topo_sort();
};



template<typename N, typename E>
class Undirected_Graph:
    public virtual Base<N, E>
{   
     protected:                  //changed the scope of using. Earlier was in public, so was exposed to the user and can be misused
        using Base<N, E> :: idx;
        using Base<N, E> :: node;
        using Base<N, E> :: n;
        using Base<N, E> :: e;
        using Base<N, E> :: adj;
        using Base<N, E> :: get_edge;
        using Base<N, E> :: is_weighted;
        using Base<N, E> :: is_directed;
      
    public:
        /*
            For more on how to return different types based on tepmplate read at
            https://stackoverflow.com/questions/48199813/how-to-use-condition-to-check-if-typename-t-is-integer-type-of-float-type-in-c
            https://stackoverflow.com/questions/44864576/returning-different-type-from-a-function-template-depending-on-a-condition
        */
        template<typename T>
            auto  prims_minimum_spanning_tree(const std::function <T(E)>&);    //both algorithms works fine with negative edge weights also
        template<typename T>
            auto krushkal_minimum_spanning_tree(const std::function <T(E)>&);
};


template<typename N,typename E>
class Unweighted_Graph:
    public virtual Base<N, E>
{
     protected:                  //changed the scope of using. Earlier was in public, so was exposed to the user and can be misused
        
        using Base<N, E> :: idx;
        using Base<N, E> :: node;
        using Base<N, E> :: n;
        using Base<N, E> :: e;
        using Base<N, E> :: adj;
        using Base<N, E> :: get_edge;
        using Base<N, E> :: is_weighted;
        using Base<N, E> :: is_directed;

    public:

        std::vector <traversal<N,int> > single_source_shortest_path(N&);
        std::vector <node_pair<N,int> > all_pair_shortest_path();
};

template<typename N, typename E>
class Weighted_Graph:
    public virtual Base<N, E>
{
    private:
        template<typename T>
            auto dijkstra(int, const std::function <T(E)>& );   //total 2 types of each for float and int
        template<typename T>
            auto shortest_path_faster_algorithm(int, bool&, const std::function <T(E)>& );
    protected:                  //changed the scope of using. Earlier was in public, so was exposed to the user and can be misused
        using Base<N, E> :: idx;
        using Base<N, E> :: node;
        using Base<N, E> :: n;
        using Base<N, E> :: e;
        using Base<N, E> :: adj;
        using Base<N, E> :: get_edge;
        using Base<N, E> :: is_weighted;
        using Base<N, E> :: is_directed;

    public:
        
        // void add_edge(N&, N&, E&);   //distinction of function so no abuse of both add edge methods
        
        
        template<typename T>
            auto single_source_shortest_path( N&, const std::function <T(E)>& );
        template<typename T>
            auto all_pair_shortest_path( const std::function <T(E)>& );
        template<typename T>
            bool is_negative_weight_cycle( N&, const std::function <T(E)>& );

        
};

template<typename N = int, bool is_directed = 0, bool is_weighted = 0, typename E = int>
class graph:
    public virtual std::conditional<is_directed, Directed_Graph<N,E>, Undirected_Graph<N,E> >::type,
    public virtual std::conditional<is_weighted, Weighted_Graph<N,E>, Unweighted_Graph<N,E> >::type
{
    protected:
        using Base<N, E> :: idx;
        using Base<N, E> :: node;
        using Base<N, E> :: n;
        using Base<N, E> :: e;
        using Base<N, E> :: adj;
        using Base<N, E> :: get_edge;

    public:
        graph(int); //Remember to update the superclass base variables
        graph();
        
};








#include "gmap.inc"
#include "struct_traversal.inc"
#include "struct_node_pair.inc"
#include "disjoint_set_union.inc"
#include "get_data_type.inc"
#include "Base.inc"
#include "Directed_Graph.inc"
#include "Undirected_Graph.inc"
#include "Unweighted_Graph.inc"
#include "Weighted_Graph.inc"
#include "graph.inc"

#endif