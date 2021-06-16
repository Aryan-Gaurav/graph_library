#include "../source/graph_library.h"
#include <vector>
#include <cassert>
#include <algorithm>

void sort_for_checking(std::vector<std::vector<int> > &scc)
{
    for(auto &x: scc)
    {
        sort(x.begin(), x.end());
    }

    sort(scc.begin(), scc.end(), [&](const std::vector<int> &a, const std::vector<int> &b)
    {
        if(a.size() == b.size())
            return a[0] < b[0];
        return a.size() < b.size();
    });

}

void test_case_1() //Example from Gabow's Paper
{
    graph<int, true> G;
    std::vector<int> v(6);
    
    assert(G.count_node() == 0);
    assert(G.count_edge() == 0);

    for (int i = 0; i < 6; i++)
    {
        v[i] = i + 1;
    }

    G.add_node (v);
    assert(G.count_node() == 6);
    assert(G.count_edge() == 0);

    G.add_edge(v[0], v[1]);
    assert(G.count_node() == 6);
    assert(G.count_edge() == 1);

    G.add_edge(v[0], v[2]);
    assert(G.count_node() == 6);
    assert(G.count_edge() == 2);

    G.add_edge(v[1], v[2]);
    assert(G.count_node() == 6);
    assert(G.count_edge() == 3);

    G.add_edge(v[1], v[3]);
    assert(G.count_node() == 6);
    assert(G.count_edge() == 4);

    G.add_edge(v[3], v[2]);
    assert(G.count_node() == 6);
    assert(G.count_edge() == 5);

    G.add_edge(v[3], v[4]);
    assert(G.count_node() == 6);
    assert(G.count_edge() == 6);

    G.add_edge(v[4], v[1]);
    assert(G.count_node() == 6);
    assert(G.count_edge() == 7);

    G.add_edge(v[4], v[5]);
    assert(G.count_node() == 6);
    assert(G.count_edge() == 8);

    G.add_edge(v[5], v[3]);
    assert(G.count_node() == 6);
    assert(G.count_edge() == 9);

    G.add_edge(v[5], v[2]);
    assert(G.count_node() == 6);
    assert(G.count_edge() == 10);

    assert(G.is_dag() == false);

    auto topo = G.topo_sort();

    assert(topo.empty() == true);

    auto scc = G.scc();

    assert(scc.size() == 3);

    sort_for_checking( scc );

    assert(scc[0].size() == 1);
    assert(scc[0][0] == 1);

    assert(scc[1].size() == 1);
    assert(scc[1][0] == 3);

    assert(scc[2].size() == 4);
    assert(scc[2][0] == 2);
    assert(scc[2][1] == 4);
    assert(scc[2][2] == 5);
    assert(scc[2][3] == 6);

}

void test_case_2()
{
    graph<int,true> G;

    assert(G.count_node() == 0);
    assert(G.count_edge() == 0);

    std::vector<int> v(12);

    for(size_t i=0; i< 12 ; i++)
    {
        
    }

}

void run_test()
{
    test_case_1();
    test_case_2();
}

int main()
{
    run_test();

    return 0;
}