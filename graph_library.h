
#ifndef GRAPH_LIBRARY_H
#define GRAPH_LIBRARY_H

#include <map>
#include <vector>
#include <utility> //for using pairs
#include <cstdint> // for fixed sized integers
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
    int n = 0;
    std::vector<std::vector<std::pair<int, E> > > adj;
public:
    size_t size();
    void add_node( N& );
    void add_node( std::vector<N>& );
    std::vector<traversal<N,int64_t> > bfs(N&, int);
    std::vector<traversal<N,int64_t> > dfs(N&, int);
};

template<typename N, typename E>
class Directed_Graph :
    public virtual Base<N, E>
{
    public:
        bool is_DAG();
        std::vector<vector<N> > SCC();
        std::vector<N> Topo_Sort();
};

template<typename N, typename E>
class Undirected_Graph:
    public virtual Base<N, E>
{
    public:
        std::pair <int64_t, std::vector<E> > Prims_MST();
        std::pair <int64_t, std::vector<E> > Krushkal_MST();
};


template<typename N, typename E>
class Unweighted_Graph:
    public virtual Base<N, E>
{
    public:
        void add_edge(N&, N&, E&);

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

template<typename N=int, typename E=int, bool is_directed=0, bool is_weighted=0>
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
size_t Base<N, E> :: size()
{
    return n;
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

template<typename N,typename E>
void Base<N, E> :: add_node( std::vector<N> &v)
{
	for(auto &x : v)
	{
        add_node(x);
	}
}



#endif