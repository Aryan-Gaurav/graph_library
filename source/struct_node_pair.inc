//Definations for struct for node pairwise distance

template<typename N, typename T>
node_pair<N, T> :: node_pair()
{
    distance = T(INF);
}

template<typename N, typename T>
node_pair<N, T> :: node_pair(N a, N b, T dis)
{
    from = a;
    to = b;
    distance = dis;
}

template<typename N, typename T>
void node_pair<N, T> :: set_value(N a, N b, T dis)
{
    from = a;
    to = b;
    distance = dis;
}