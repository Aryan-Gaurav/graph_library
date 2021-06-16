#include "../source/graph_library.h"
#include <string>
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

void test_case_2()  //this is to test SCC on a bigger graph
{
    graph<int,true> G;

    assert(G.count_node() == 0);
    assert(G.count_edge() == 0);

    std::vector<int> v(12);

    for(size_t i=0; i< 12 ; i++)
    {
        v[i] = i;
    }

    G.add_node(v);

    assert(G.count_node() == 12);
    assert(G.count_edge() == 0);

    G.add_edge(v[0],v[1]);
    assert(G.count_node() == 12);
    assert(G.count_edge() == 1);

    G.add_edge(v[1],v[2]);
    G.add_edge(v[1],v[3]);
    G.add_edge(v[1],v[4]);
    assert(G.count_node() == 12);
    assert(G.count_edge() == 4);

    G.add_edge(v[2],v[5]);
    assert(G.count_node() == 12);
    assert(G.count_edge() == 5);

    G.add_edge(v[4],v[1]);
    G.add_edge(v[4],v[5]);
    G.add_edge(v[4],v[6]);
    assert(G.count_node() == 12);
    assert(G.count_edge() == 8);

    G.add_edge(v[5],v[7]);
    G.add_edge(v[5],v[2]);
    assert(G.count_node() == 12);
    assert(G.count_edge() == 10);

    G.add_edge(v[6],v[7]);
    G.add_edge(v[6],v[9]);
    assert(G.count_node() == 12);
    assert(G.count_edge() == 12);

    G.add_edge(v[7],v[10]);
    assert(G.count_node() == 12);
    assert(G.count_edge() == 13);

    G.add_edge(v[8],v[6]);
    assert(G.count_node() == 12);
    assert(G.count_edge() == 14);

    G.add_edge(v[9],v[8]);
    assert(G.count_node() == 12);
    assert(G.count_edge() == 15);

    G.add_edge(v[10],v[11]);
    assert(G.count_node() == 12);
    assert(G.count_edge() == 16);

    G.add_edge(v[11],v[9]);
    assert(G.count_node() == 12);
    assert(G.count_edge() == 17);

    assert(G.is_dag() == false);

    auto topo = G.topo_sort();

    assert(topo.empty() == true);

    auto scc = G.scc();

    assert(scc.size() == 5);

    sort_for_checking(scc);

    assert(scc[0].size() == 1);
    assert(scc[0][0] == 0);

    assert(scc[1].size() == 1);
    assert(scc[1][0] == 3);

    assert(scc[2].size() == 2);
    assert(scc[2][0] == 1);
    assert(scc[2][1] == 4);

    assert(scc[3].size() == 2);
    assert(scc[3][0] == 2);
    assert(scc[3][1] == 5);

    assert(scc[4].size() == 6);
    assert(scc[4][0] == 6);
    assert(scc[4][1] == 7);
    assert(scc[4][2] == 8);
    assert(scc[4][3] == 9);
    assert(scc[4][4] == 10);
    assert(scc[4][5] == 11);


}


void test_case_3()  //Example from Introduction to Algorithms by Cormen
{
    class custom_node
    {
        private:
            std::string s;
        public:
            custom_node ( std::string temp ) 
            {
                s = temp;
            }
            custom_node() = default;
            std::string get_value()
            {
                return s;
            }
    };

    std::vector< custom_node > v;

    v.emplace_back( custom_node("shirt") );
    v.emplace_back( custom_node("tie") );
    v.emplace_back( custom_node("jacket") );
    v.emplace_back( custom_node("belt") );
    v.emplace_back( custom_node("watch") );
    v.emplace_back( custom_node("undershorts") );
    v.emplace_back( custom_node("pants") );
    v.emplace_back( custom_node("shoes") );
    v.emplace_back( custom_node("socks") );

    assert( v.size() == 9 );

    graph<custom_node, true > G(9); //using to 9 to reserve the space for incoming nodes

    assert(G.count_node() == 0);
    assert(G.count_edge() == 0);

    G.add_node(v);

    assert(G.count_node() == 9);
    assert(G.count_edge() == 0);

    G.add_edge(v[0], v[3]);
    G.add_edge(v[0], v[1]);
    assert(G.count_node() == 9);
    assert(G.count_edge() == 2);

    G.add_edge(v[1], v[2]);
    assert(G.count_node() == 9);
    assert(G.count_edge() == 3);

    G.add_edge(v[3], v[2]);
    assert(G.count_node() == 9);
    assert(G.count_edge() == 4);

    G.add_edge(v[5], v[7]);
    G.add_edge(v[5], v[6]);
    assert(G.count_node() == 9);
    assert(G.count_edge() == 6);

    G.add_edge(v[6], v[3]);
    G.add_edge(v[6], v[7]);
    assert(G.count_node() == 9);
    assert(G.count_edge() == 8);

    G.add_edge(v[8], v[7]);
    assert(G.count_node() == 9);
    assert(G.count_edge() == 9);

    assert(G.is_dag() == true);

    auto topo = G.topo_sort();

    /*
        Uncomment to see the results

        for(auto &x:topo)
        {
            std::cout<<x.get_value()<<std::endl;
        }
    */

    /*
        Output for above example is :-

        socks
        undershorts
        pants
        shoes
        watch
        shirt
        belt
        tie
        jacket

        which is correct
    */

}

void run_test()
{
    test_case_1();
    test_case_2();
    test_case_3();
}

int main()
{
    run_test();

    return 0;
}