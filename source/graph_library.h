
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
    std::map<std::pair<int,int>, bool> edg;   
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
    parent [x] = find_parent(parent [x] );  //try to implement using stack
    return parent[x];
}

const bool disjoint_set_union :: is_same(int x,int y)
{
    int px = find_parent(x) , py = find_parent(y);
    return px == py;
}

int disjoint_set_union :: find_size(int x)
{
    int px = find_parent(x);
    return size[px];
}

void disjoint_set_union :: do_union(int x,int y)
{
    int px = find_parent(x), py = find_parent(y);
    if (px == py)
        return;
    if (size[px] >= size[py])
    {
        size[px] += size[py];
        parent[y] = px;
        parent[py] = px;
    }
    else
    {
        do_union(y,x);
    }
    
}

#include "gmap.inc"
#include "struct_traversal.inc"
#include "Base.inc"
#include "Directed_Graph.inc"


#endif