//implementation of graph class

template<class N, bool is_directed, bool is_weighted , class E > 
graph<N, is_directed, is_weighted, E>::graph(int size)
{
    n = 0;
     e = 0;
    adj.resize( size );
    Base<N,E> :: is_directed = is_directed;
    Base<N,E> :: is_weighted = is_weighted;
   
}

template<class N , bool is_directed , bool is_weighted, class E > 
graph<N, is_directed, is_weighted, E>::graph()
{
    n = 0;
    e = 0;
    Base<N,E> :: is_directed = is_directed;
    Base<N,E> :: is_weighted = is_weighted;
}

template<class N, bool is_directed, bool is_weighted, class E> 
void graph<N, is_directed, is_weighted, E> :: add_edge(N &u, N &v, E ed)
{
    if(idx.ispresent(u) == false || idx.ispresent(v) == false) //trying to add an edge whose node is not in Graph
    {
        std::cout<<"Either one or both nodes are not present in the Graph. Please add them and try again." << std::endl;
        return;
    }
    int i = idx[u] , j = idx[v];
    if(get_edge.find({i,j}) != get_edge.end())
    {
        std::cout<<"The edge has already been added in the Graph between these two nodes."<<std::endl;
        return; 
    }
    adj[i].push_back({j,ed});
    get_edge[{ i, j }] = ed;
    e += 1; //increase the count of edges
    if(is_directed == false)
    {
        adj[j].push_back({i,ed});
        get_edge[{j, i}] = ed;
    }

}