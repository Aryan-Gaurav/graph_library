#include "../source/graph_library.h"
#include <cassert>

void test_case_1()
{
    const int n = 10;
    disjoint_set_union DSU(n);
    for(size_t i=0;i<n;i++)
    {
        assert(DSU.find_size(i) == 1);
        assert(DSU.find_parent(i) == i);
    }

    DSU.do_union(1,8);

    assert(DSU.is_same(1,8) == true);
    assert(DSU.find_size(1) == 2);
    assert(DSU.find_size(8) == 2);


    for(size_t i=0;i<n;i++)
    {
        if(i!=1 && i!=8)
        {
            assert(DSU.find_size(i) == 1);
            assert(DSU.find_parent(i) == i);
            assert(DSU.is_same(i,1) == false);
        }
    }

    DSU.do_union(4,5);

    assert(DSU.is_same(4,5) == true);
    assert(DSU.is_same(0,4) == false);
    assert(DSU.find_size(4) == 2);
    assert(DSU.find_size(5) == 2);

    for(size_t i=0;i<n;i++)
    {
        if(i!=4 && i!=5 && i!=1 && i!=8)
        {
            assert(DSU.find_size(i) == 1);
            assert(DSU.find_parent(i) == i);
            assert(DSU.is_same(i,4) == false);
            assert(DSU.is_same(i,5) == false);
        }
    }

    DSU.do_union(0,9);

    assert(DSU.is_same(0,9) == true);
    assert(DSU.is_same(4,9) == false);
    assert(DSU.is_same(4,5) == true);
    assert(DSU.find_size(0) == 2);

    DSU.do_union(0,2);

    assert(DSU.is_same(0,2) == true);
    assert(DSU.is_same(2,9) == true);
    assert(DSU.is_same(0,1) == false);
    assert(DSU.find_size(9) == DSU.find_size(2));
    assert(DSU.find_size(0) == 3);
    assert(DSU.find_parent(6) == 6);

    DSU.do_union(2,3);

    assert(DSU.is_same(3,9) == true);
    assert(DSU.is_same(0,3) == true);
    assert(DSU.is_same(3,0) == true); 
    assert(DSU.find_parent(3) == DSU.find_parent(9));
    assert(DSU.is_same(6,0) == false);
    assert(DSU.find_parent(7) != DSU.find_parent(1));
    assert(DSU.find_size(3) == 4);
    assert(DSU.find_parent(7) == 7);

    DSU.do_union(1,7);

    assert(DSU.is_same(1,7) == true);
    assert(DSU.is_same(7,8) == true);
    assert(DSU.find_size(1) == 3);
    assert(DSU.find_size(8) == DSU.find_size(7));
    assert(DSU.is_same(7,0) == false);

    DSU.do_union(9,3); //already in the same set

    assert(DSU.is_same(9,3) == true);
    assert(DSU.is_same(3,0) == true);
    assert(DSU.find_size(0) == 4);
    assert(DSU.find_size(3) == 4);
    assert(DSU.find_parent(6) == 6);
    
    DSU.do_union(8,4);

    assert(DSU.is_same(1,5) == true);
    assert(DSU.is_same(7,4) == true);
    assert(DSU.find_size(7) > DSU.find_size(0)); //5 > 4
    assert(DSU.find_size(8) == 5);
    assert(DSU.find_size(6) == 1);
    assert(DSU.is_same(1,6) == false);

    DSU.do_union(1,6);

    assert(DSU.is_same(4,6) == true);
    assert(DSU.is_same(7,6) == true);
    assert(DSU.is_same(1,6) == true);
    assert(DSU.find_size(6) == 6);
    assert(DSU.find_size(0) == 4);
    assert(DSU.is_same(0,8) == false);

}

void test_case_2()
{
    const int n = 1<<22; //2^22 = approx 4e6
    disjoint_set_union DSU(n);
    for (size_t j=1; j<n; j*=2)
    {
        for(size_t i=0;i<n;i+=2*j)
        {
            assert(DSU.find_size(i) == j);
            assert(DSU.is_same(i,i+j) == false);
            DSU.do_union(i,i+j);
            assert(DSU.is_same(i,i+j) == true);
            assert(DSU.find_size(i) == 2*j);
        }
    }

}


void test_case_3()
{
    const int n = 1e7;
    disjoint_set_union DSU(n);
    size_t count = 1;
    for(size_t i=2;i<n;i+=2)
    {
        assert(DSU.find_size(i) == 1);
        assert(DSU.find_parent(i) == i);
        assert(DSU.is_same(0,i) == false);
        DSU.do_union(i,0);
        count += 1;
        assert(DSU.is_same(0,i) == true);
        assert(DSU.find_size(i) == count);
    }

    assert(DSU.find_size(0) == (n+1)/2);

    count = 1;
    for(size_t i=3;i<n;i+=2)
    {
        assert(DSU.find_size(i) == 1);
        assert(DSU.find_parent(i) == i);
        assert(DSU.is_same(1,i) == false);
        DSU.do_union(i,1);
        count += 1;
        assert(DSU.find_size(i) == count);
        assert(DSU.is_same(1,i) == true);
        assert(DSU.is_same(i,i-1) == false);
    }

    assert(DSU.is_same(5,10) == false);

    DSU.do_union(5,10);

    for (size_t i=1; i<n ; i+=2)
    {
        assert(DSU.is_same(i-1,i) == true);
    }

    assert(DSU.find_size(9) == n);
    
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