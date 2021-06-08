#include "graph_library.h"
#include <iostream>
#include <map>

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

    std::cout << mp[a] << std::endl;
    std::cout << mp[b] << std::endl;
	 bool ans = mp.ispresent(a);
     cout<<ans<<endl;
     auto c = a;
    std::cout<< mp.ispresent(c) << std::endl;
    return 0;
}