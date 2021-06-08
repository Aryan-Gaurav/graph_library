#include "graph_library.h"
#include <iostream>
#include <vector>
#include <string>

class node
{
private:
	std::string s;
	int i;
public:
	node()
	{
		s="-1";
		i=-1;
	}
	void set_data(std::string name,int index)
	{
		s = name;
		i = index;
	}
	void print()
	{
		std::cout<< s <<std::endl;
		std::cout<< i <<std::endl<<std::endl;
	}
};

int main()
{
	Base<node,int> a, b, c;
	std::vector<node> v(5);
	node n1,n2,n3;
	for(size_t i=0;i<5;i++)
	{
		v[i].set_data("Name is" + std::to_string(i), i);
	}
	a.add_node(v);
	std::cout<< a.size() <<std::endl;
	a.add_node(n1);
	std::cout<< a.size() <<std::endl;
	a.add_node(n1);	//try adding the same node twice
	std::cout<< a.size() <<std::endl;

	for(size_t i=0;i<5;i++)
	{
		b.add_node(v[i]);
	}
	std::cout<< b.size() <<std::endl;
	b.add_node(n1);
	std::cout<< a.size() <<std::endl;
	a.add_node(n1);	//try adding the same node twice
	std::cout<< a.size() <<std::endl;
	v.push_back(n1);
	c.add_node(v);
	std::cout<< c.size() <<std::endl;
}