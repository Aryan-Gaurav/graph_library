
#ifndef GRAPH_LIBRARY_H
#define GRAPH_LIBRARY_H

#include<map>
#include<vector>
#include<utility> //for using pairs
#include<iostream>

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