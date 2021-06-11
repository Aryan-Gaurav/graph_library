// Functions of Base Class

template<typename N,typename E>
size_t Base<N, E> :: count_node()
{
    return n;
}

template<typename N,typename E>
size_t Base<N, E> :: count_edge()
{
    return e;
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

template<typename N, typename E>
void Base<N, E> :: add_node( std::vector<N> &v)
{
	for(auto &x : v)
	{
        add_node(x);
	}
}
