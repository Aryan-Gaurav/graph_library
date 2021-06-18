#include "../source/graph_library.h"
#include <cassert> //for using assert staements for checking
#include <vector>
#include <bits/stdc++.h>
using namespace std;

void test_case_1()
{
    graph<int,true,true,int> G;
    std::vector<int> v(10);
    for(int i=0;i<10;i++)
        v[i] = i;
    G.add_node(v);
    G.add_edge(v[0],v[1],2);
    G.add_edge(v[0],v[2],5);

    auto get_weight = [](int x)
    {
        return x;
    };

    


}

void run_test_case()
{
    test_case_1();
}

int main()
{
    run_test_case();

    return 0;
}