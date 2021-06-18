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

