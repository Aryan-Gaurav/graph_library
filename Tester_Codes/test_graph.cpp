#include "../source/graph_library.h"
#include <iostream>
#include <cassert>
#include <vector>

void test_case_1()
{
    graph G(5);
    std::vector<int> v(5);

    for(size_t i = 0; i<5; i++)
    {
        v[i] = i;
    }
    
    assert(G.count_edge() == 0);
    assert(G.count_node() == 0);

    G.add_node(v);

    assert(G.count_edge() == 0);
    assert(G.count_node() == 5);

    for(size_t i = 1; i<5; i++)
    {
        assert( G.count_edge() == i-1 );
        assert( G.count_node() == 5 );

        G.add_edge(v[0], v[i]);

        assert( G.count_edge() == i );
        assert( G.count_node() == 5 );
    }

    assert( G.count_edge() == 4);

    auto bfs_res = G.bfs(v[0]);

    for(auto &x: bfs_res)
    {
        assert(x.parent == 0);
    }

    auto dfs_res = G.dfs(v[1]);

    dfs_res = G.dfs(v[0]);

    for(auto &x: dfs_res)
    {
        assert(x.parent == 0);
    }

    // std::cout<< G.is_dag() << std::endl; //throws an error

    
}


void run_test()
{
    test_case_1();
}

int main()
{

    run_test();

    return 0;
}