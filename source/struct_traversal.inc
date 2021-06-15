#include <iostream>

//Functions definations for struct traversal

template<typename N, typename T>
traversal<N, T> :: traversal()
{
    distance = T(2e9);  //typecast 2e9 ~ INT_MAX
}

template<typename N, typename T>
traversal<N, T> :: traversal(N a, N b, T dis)
{
    node = a;
    parent = b;
    distance = dis;
}

template<typename N, typename T>
void traversal<N, T> :: set_value(N a, N b, T dis)
{
    node = a;
    parent = b;
    distance = dis;
}

