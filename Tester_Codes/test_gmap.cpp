#include "../source/graph_library.h"
#include <iostream>
#include <map>
#include <cassert>

class A
{
    public:
    int a;
};
int main()
{
	
    gmap<A,int> mp;
    A a,b;
    a.a=b.a=1;
    mp[a]=2;
    mp[b]=5;
    
    assert(mp[a] == 2);
    assert(mp[b] == 5);
    assert(mp.ispresent(a)== true);
     auto c = a;
    assert(mp.ispresent(c) == false);
    return 0;
}