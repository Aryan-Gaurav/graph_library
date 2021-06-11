#include "../source/graph_library.h"
#include <iostream>
#include <vector>
#include <string>
#include <cassert>

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


void test_case_1()
{
	Base<node,int> a;
	std::vector<node> v(5);
	node n1,n2,n3;
	for(size_t i=0;i<5;i++)
	{
		v[i].set_data("Name is" + std::to_string(i), i);
	}
	assert(a.count_node() == 0);
	a.add_node(v);
	assert(a.count_node() == 5);
	a.add_node(n1);
	assert(a.count_node() == 6);
	a.add_node(n1);	//try adding the same node twice
	assert(a.count_node() == 6);
}


void test_case_2()
{
	Base<node,int> b;
	std::vector<node> v(5);
	node n1,n2,n3;
	for(size_t i=0;i<5;i++)
	{
		v[i].set_data("Name is" + std::to_string(i), i);
	}

	for(size_t i=0;i<5;i++)
	{
		assert(b.count_node() == i);
		b.add_node(v[i]);
		assert(b.count_node() == i+1);
	}
	assert(b.count_node() == 5);
	b.add_node(n1);
	assert(b.count_node() == 6);
	b.add_node(n1);	//try adding the same node twice
	assert(b.count_node() == 6);
}


void test_case_3()
{
	Base<node,int> c;
	std::vector<node> v(5);
	node n1,n2,n3;
	for(size_t i=0;i<5;i++)
	{
		v[i].set_data("Name is" + std::to_string(i), i);
	}
	assert(c.count_node() == 0);
	v.push_back(n1);
	c.add_node(v);
	assert(c.count_node() == 6);
	v.push_back(n2);
	c.add_node(v);
	assert( c.count_node() == 7);
	c.add_node(n3);
	assert( c.count_node() == 8);
	c.add_node(n3);
	assert( c.count_node() == 8);
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