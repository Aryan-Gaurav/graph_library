#include "../source/graph_library.h"
#include <cassert> //for using assert staements for checking
#include <vector>
#include <algorithm>

void test_case_1() //Example of non-negative Weight Edges from Introduction to Algorithms by Cormen , Fig 24.6
{
    graph<char, true, true, int> G;
    std::vector<char> v(5);

    assert(G.count_node() == 0);
    assert(G.count_edge() == 0);

    v[0] = 's';
    v[1] = 't';
    v[2] = 'x';
    v[3] = 'z';
    v[4] = 'y';

    G.add_node(v);

    assert(G.count_node() == 5);
    assert(G.count_edge() == 0);

    G.add_edge(v[0], v[1], 10);
    G.add_edge(v[0], v[4], 5);
    assert(G.count_node() == 5);
    assert(G.count_edge() == 2);

    G.add_edge(v[1], v[2], 1);
    G.add_edge(v[1], v[4], 2);
    assert(G.count_node() == 5);
    assert(G.count_edge() == 4);

    G.add_edge(v[2], v[3], 4);
    assert(G.count_node() == 5);
    assert(G.count_edge() == 5);

    G.add_edge(v[3], v[2], 6);
    G.add_edge(v[3], v[0], 7);
    assert(G.count_node() == 5);
    assert(G.count_edge() == 7);

    G.add_edge(v[4], v[2], 9);
    G.add_edge(v[4], v[3], 2);
    G.add_edge(v[4], v[1], 3);
    assert(G.count_node() == 5);
    assert(G.count_edge() == 10);

    auto get_weight_1 = [](int x)
    {
        return x;
    };

    assert(G.is_negative_weight_cycle<int>(v[0], get_weight_1) == false);

    auto sssp = G.single_source_shortest_path<int>(v[0], get_weight_1);

    assert(sssp.size() == 5);

    sort(sssp.begin(), sssp.end(), [&](traversal<char, int64_t> &a, traversal<char, int64_t> &b) // for checking the path and parent nodes
         { return a.node < b.node; });

    assert(sssp[0].node == 's');
    assert(sssp[0].parent == 's');
    assert(sssp[0].distance == 0);

    assert(sssp[1].node == 't');
    assert(sssp[1].parent == 'y');
    assert(sssp[1].distance == 8);

    assert(sssp[2].node == 'x');
    assert(sssp[2].parent == 't');
    assert(sssp[2].distance == 9);

    assert(sssp[3].node == 'y');
    assert(sssp[3].parent == 's');
    assert(sssp[3].distance == 5);

    assert(sssp[4].node == 'z');
    assert(sssp[4].parent == 'y');
    assert(sssp[4].distance == 7);
}

void test_case_2() //Example of Negative Weight Edges from Introduction to Algorithms by Cormen , Fig 24.4
{
    graph<char, true, true, int> G;
    std::vector<char> v(5);

    assert(G.count_node() == 0);
    assert(G.count_edge() == 0);

    v[0] = 's';
    v[1] = 't';
    v[2] = 'x';
    v[3] = 'z';
    v[4] = 'y';

    G.add_node(v);

    assert(G.count_node() == 5);
    assert(G.count_edge() == 0);

    G.add_edge(v[0], v[4], 7);
    G.add_edge(v[0], v[1], 6);
    assert(G.count_node() == 5);
    assert(G.count_edge() == 2);

    G.add_edge(v[1], v[2], 5);
    G.add_edge(v[1], v[3], -4);
    G.add_edge(v[1], v[4], 8);
    assert(G.count_node() == 5);
    assert(G.count_edge() == 5);

    G.add_edge(v[2], v[1], -2);
    assert(G.count_node() == 5);
    assert(G.count_edge() == 6);

    G.add_edge(v[3], v[2], 7);
    G.add_edge(v[3], v[0], 2);
    assert(G.count_node() == 5);
    assert(G.count_edge() == 8);

    G.add_edge(v[4], v[3], 9);
    G.add_edge(v[4], v[2], -3);
    assert(G.count_node() == 5);
    assert(G.count_edge() == 10);

    auto get_weight_2 = [](int x)
    {
        return x;
    };

    assert(G.is_negative_weight_cycle<int>(v[0], get_weight_2) == false);

    auto sssp = G.single_source_shortest_path<int>(v[0], get_weight_2);

    assert(sssp.size() == 5);

    sort(sssp.begin(), sssp.end(), [&](traversal<char, int64_t> &a, traversal<char, int64_t> &b) // for checking the path and parent nodes
         { return a.node < b.node; });

    assert(sssp[0].node == 's');
    assert(sssp[0].parent == 's');
    assert(sssp[0].distance == 0);

    assert(sssp[1].node == 't');
    assert(sssp[1].parent == 'x');
    assert(sssp[1].distance == 2);

    assert(sssp[2].node == 'x');
    assert(sssp[2].parent == 'y');
    assert(sssp[2].distance == 4);

    assert(sssp[3].node == 'y');
    assert(sssp[3].parent == 's');
    assert(sssp[3].distance == 7);

    assert(sssp[4].node == 'z');
    assert(sssp[4].parent == 't');
    assert(sssp[4].distance == -2);
}

void test_case_3() //Example of all pair shortest path from Introduction to Algorithms by Cormen, Fig 25.1
{
    graph<int, true, true, int> G;

    std::vector<int> v(5);

    for (size_t i = 0; i < 5; i++)
    {
        v[i] = i + 1;
    }

    assert(G.count_node() == 0);
    assert(G.count_edge() == 0);

    G.add_node(v);

    assert(G.count_node() == 5);
    assert(G.count_edge() == 0);

    G.add_edge(v[0], v[1], 3);
    G.add_edge(v[0], v[2], 8);
    G.add_edge(v[0], v[4], -4);
    assert(G.count_node() == 5);
    assert(G.count_edge() == 3);

    G.add_edge(v[1], v[3], 1);
    G.add_edge(v[1], v[4], 7);
    assert(G.count_node() == 5);
    assert(G.count_edge() == 5);

    G.add_edge(v[2], v[1], 4);
    assert(G.count_node() == 5);
    assert(G.count_edge() == 6);

    G.add_edge(v[3], v[2], -5);
    G.add_edge(v[3], v[0], 2);
    assert(G.count_node() == 5);
    assert(G.count_edge() == 8);

    G.add_edge(v[4], v[3], 6);
    assert(G.count_node() == 5);
    assert(G.count_edge() == 9);

    auto get_weight_3 = [](int x)
    {
        return long(x);
    };

    auto apsp = G.all_pair_shortest_path<long>(get_weight_3);

    assert(apsp.size() == 25);

    sort(apsp.begin(), apsp.end(), [&](node_pair<int, int64_t> &a, node_pair<int, int64_t> &b)
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
        {0, 1, -3, 2, -4},
        {3, 0, -4, 1, -1},
        {7, 4, 0, 5, 3},
        {2, -1, -5, 0, -2},
        {8, 5, 1, 6, 0}};

    for (size_t from = 1; from <= 5; from++)
    {
        for (size_t to = 1; to <= 5; to++)
        {
            int index = (from - 1) * 5 + (to - 1);
            int i = index / 5;
            int j = index % 5;
            assert(apsp[index].from == from);
            assert(apsp[index].to == to);
            assert(apsp[index].distance == distance[i][j]);
        }
    }
}

void test_case_4() // Example from Algorithms by Robert Sedgewick and Kevin Wayne, Page No. 678
{
    graph<int, true, true, double> G;

    std::vector<int> v(8);

    for (size_t i = 0; i < 8; i++)
    {
        v[i] = i;
    }

    assert(G.count_node() == 0);
    assert(G.count_edge() == 0);

    G.add_node(v);

    assert(G.count_node() == 8);
    assert(G.count_edge() == 0);

    G.add_edge(v[0], v[4], 0.38);
    G.add_edge(v[0], v[2], 0.26);
    assert(G.count_node() == 8);
    assert(G.count_edge() == 2);

    G.add_edge(v[1], v[3], 0.29);
    assert(G.count_node() == 8);
    assert(G.count_edge() == 3);

    G.add_edge(v[2], v[7], 0.34);
    assert(G.count_node() == 8);
    assert(G.count_edge() == 4);

    G.add_edge(v[3],  v[6], 0.52);
    assert(G.count_node() == 8);
    assert(G.count_edge() == 5);

    G.add_edge(v[4], v[5], 0.35);
    G.add_edge(v[4], v[7], 0.37);
    assert(G.count_node() == 8);
    assert(G.count_edge() == 7);

    G.add_edge(v[5], v[4], -0.66);
    G.add_edge(v[5], v[7], 0.28);
    G.add_edge(v[5], v[1], 0.32);
    assert(G.count_node() == 8);
    assert(G.count_edge() == 10);

    G.add_edge(v[6], v[2], 0.40);
    G.add_edge(v[6], v[0],  0.58);
    G.add_edge(v[6], v[4 ], 0.93);
    assert(G.count_node() == 8);
    assert(G.count_edge() == 13);

    G.add_edge(v[7], v[5], 0.28);
    G.add_edge(v[7], v[3], 0.39);
    assert(G.count_node() == 8);
    assert(G.count_edge() == 15);

    auto get_weight_4 = [](double x)
    {
        return x;
    };
    
    assert(G.is_negative_weight_cycle<double>(v[0],get_weight_4) == true);

}

void run_test_case()
{
    test_case_1();
    test_case_2();
    test_case_3();
    test_case_4();
}

int main()
{
    run_test_case();

    return 0;
}