#include "../source/graph_library.h"
#include <iostream>
#include <cassert>
#include <vector>

void test_case_1()
{
    graph G(5);
    std::vector<int> v(5,-1);
    
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