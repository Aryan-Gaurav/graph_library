#include "../source/graph_library.h"
#include <cassert> //for using assert staements for checking
#include <vector>
#include <algorithm>

void test_case_1()
{

    graph<int,false> G;
    std::vector<int> v(5);

    assert(G.count_node() == 0);
    assert(G.count_edge() == 0);
    
    for(size_t i = 0;i<5;i++)
    {
        v[i] = i;
    }

    G.add_node(v);

    assert(G.count_node() == 5);
    assert(G.count_edge() == 0);
    
    G.add_edge(v[0],v[1]);
    G.add_edge(v[0],v[2]);
    G.add_edge(v[0],v[3]);
    assert(G.count_node() == 5);
    assert(G.count_edge() == 3);

    G.add_edge(v[1],v[2]);
    G.add_edge(v[1],v[4]);
    assert(G.count_node() == 5);
    assert(G.count_edge() == 5);

    G.add_edge(v[3],v[4]);
    assert(G.count_node() == 5);
    assert(G.count_edge() == 6);

    auto sssp = G.single_source_shortest_path(v[0]);

    assert(sssp.size() == 5);

    sort(sssp.begin(),sssp.end(),[&](traversal<int,int32_t> &a,traversal<int,int32_t> &b)
    {
        return a.node < b.node;
    });

    assert(sssp[0].node == 0);
    assert(sssp[0].parent == 0);
    assert(sssp[0].distance == 0);

    assert(sssp[1].node == 1);
    assert(sssp[1].parent == 0);
    assert(sssp[1].distance == 1);

    assert(sssp[2].node == 2);
    assert(sssp[2].parent == 0);
    assert(sssp[2].distance == 1);

    assert(sssp[3].node == 3);
    assert(sssp[3].parent == 0);
    assert(sssp[3].distance == 1);

    assert(sssp[4].node == 4);
    assert(sssp[4].parent == 1 || sssp[4].parent == 3); //as parent is 1 or 3 depends upon order in which they are inserted
    assert(sssp[4].distance == 2);

    auto apsp = G.all_pair_shortest_path();

    assert(apsp.size() == 25);

    sort(apsp.begin(), apsp.end(), [&](node_pair<int, int> &a, node_pair<int, int> &b)
         {
             if (a.from != b.from)
             {
                 return a.from < b.from;
             }
             else
             {
                return a.to < b.to;
             }
         });
    
    int distance[5][5] = {
        {0,1,1,1,2},
        {1,0,1,2,1},
        {1,1,0,2,2},
        {1,2,2,0,1},
        {2,1,2,1,0}
    };

    for (size_t from = 0; from < 5; from++)
    {
        for (size_t to = 1; to < 5; to++)
        {
            int index = from * 5 + to;
            int i = index / 5;
            int j = index % 5;
            assert(apsp[index].from == from);
            assert(apsp[index].to == to);
            assert(apsp[index].distance == distance[i][j]);
        }
    }

}

void test_case_2()
{
    graph<int,true> G;
    std::vector<int> v(5);

    assert(G.count_node() == 0);
    assert(G.count_edge() == 0);
    
    for(size_t i = 0;i<5;i++)
    {
        v[i] = i;
    }

    G.add_node(v);

    assert(G.count_node() == 5);
    assert(G.count_edge() == 0);
    
    G.add_edge(v[0],v[1]);
    G.add_edge(v[0],v[3]);
    assert(G.count_node() == 5);
    assert(G.count_edge() == 2);

    G.add_edge(v[1],v[2]);
    G.add_edge(v[1],v[4]);
    assert(G.count_node() == 5);
    assert(G.count_edge() == 4);

    G.add_edge(v[2],v[0]);
    assert(G.count_node() == 5);
    assert(G.count_edge() == 5);

    G.add_edge(v[3],v[4]);
    assert(G.count_node() == 5);
    assert(G.count_edge() == 6);

    auto sssp = G.single_source_shortest_path(v[0]);

    assert(sssp.size() == 5);

    sort(sssp.begin(),sssp.end(),[&](traversal<int,int32_t> &a,traversal<int,int32_t> &b)
    {
        return a.node < b.node;
    });

    assert(sssp[0].node == 0);
    assert(sssp[0].parent == 0);
    assert(sssp[0].distance == 0);

    assert(sssp[1].node == 1);
    assert(sssp[1].parent == 0);
    assert(sssp[1].distance == 1);

    assert(sssp[2].node == 2);
    assert(sssp[2].parent == 1);
    assert(sssp[2].distance == 2);

    assert(sssp[3].node == 3);
    assert(sssp[3].parent == 0);
    assert(sssp[3].distance == 1);

    assert(sssp[4].node == 4);
    assert(sssp[4].parent == 3 || sssp[4].parent == 1);
    assert(sssp[4].distance == 2);

    auto apsp = G.all_pair_shortest_path();

    assert(apsp.size() == 25);

    sort(apsp.begin(), apsp.end(), [&](node_pair<int, int> &a, node_pair<int, int> &b)
         {
             if (a.from != b.from)
             {
                 return a.from < b.from;
             }
             else
             {
                return a.to < b.to;
             }
         });
    const int pos_inf = 2e9;
    int distance[5][5] = {
        {0,1,2,1,2},
        {2,0,1,3,1},
        {1,2,0,2,3},
        {pos_inf,pos_inf,pos_inf,0,1},
        {pos_inf,pos_inf,pos_inf,pos_inf,0}
    };

    for (size_t from = 0; from < 5; from++)
    {
        for (size_t to = 1; to < 5; to++)
        {
            int index = from * 5 + to;
            int i = index / 5;
            int j = index % 5;
            assert(apsp[index].from == from);
            assert(apsp[index].to == to);
            assert(apsp[index].distance == distance[i][j]);
        }
    }

    assert(G.is_dag() == false);

}

void run_test_case()
{
    test_case_1();
    test_case_2();
}

int main()
{
    run_test_case();

    return 0;
}