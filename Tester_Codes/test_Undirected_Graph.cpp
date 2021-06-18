#include "../source/graph_library.h"
#include <cassert> //for using assert staements for checking
#include <cmath> //for using fabs function to find absolute value
#include <vector>

#define EPS 1e-7 //the tolerance value in comparison of floating point values



int get_weight_1(int x)
{
	return x;
}

void test_case_1()  //Example from Introduction to Algorithms by Cormen
{
	graph<char, false, true, int> G;
	std::vector<char> v(9);

	assert(G.count_node() == 0);
	assert(G.count_edge() == 0);

	for (int i = 0; i < 9; i++)
	{
		v[i] = char(i + 'a');
	}

	G.add_node(v);
	assert(G.count_node() == 9);
	assert(G.count_edge() == 0);

	G.add_edge(v[0], v[1], 4);
	G.add_edge(v[0], v[7], 8);
	assert(G.count_node() == 9);
	assert(G.count_edge() == 2);

	G.add_edge(v[1], v[7], 11);
	G.add_edge(v[1], v[2], 8);
	assert(G.count_node() == 9);
	assert(G.count_edge() == 4);

	G.add_edge(v[2], v[3], 7);
	G.add_edge(v[2], v[5], 4);
	G.add_edge(v[2], v[8], 2);
	assert(G.count_node() == 9);
	assert(G.count_edge() == 7);

	G.add_edge(v[3], v[4], 9);
	G.add_edge(v[3], v[5], 14);
	assert(G.count_node() == 9);
	assert(G.count_edge() == 9);

	G.add_edge(v[4], v[5], 10);
	assert(G.count_node() == 9);
	assert(G.count_edge() == 10);

	G.add_edge(v[5], v[6], 2);
	assert(G.count_node() == 9);
	assert(G.count_edge() == 11);

	G.add_edge(v[6], v[7], 1);
	G.add_edge(v[6], v[8], 6);
	assert(G.count_node() == 9);
	assert(G.count_edge() == 13);

	G.add_edge(v[7], v[8], 7);
	assert(G.count_node() == 9);
	assert(G.count_edge() == 14);


	/*
		We need to specify the template argument T with the function name, here it is int.
	*/
	auto mst = G.krushkal_minimum_spanning_tree<int>(get_weight_1);	//call from a function defined outside

	assert(mst.first == 37);

	std::function<int(int)> get_weight_2 = [] (int x)
	{
		return x;
	};

	//No need to specify template parameter if using std::function

	mst = G.krushkal_minimum_spanning_tree(get_weight_2); //trying to call with defining std::function inside 

	assert(mst.first == 37);

	auto get_weight_3 = [] (int x)
	{
		return x;
	};

	mst = G.krushkal_minimum_spanning_tree<int>(get_weight_3);

	assert(mst.first == 37);

	

	/*
		Uncomment to see the output

		for(auto &x:mst.second)
		{
			std::cout<<x.u<<" "<<x.v<<" "<<x.edge<<std::endl;
		}
	*/
	

	/*
	The output for above code is :-
		g h 1
		c i 2
		f g 2
		a b 4
		c f 4
		c d 7
		a h 8
		d e 9

		which is same as in the book
	*/	

	mst = G.prims_minimum_spanning_tree<int>(get_weight_2);

	assert(mst.first == 37);



	/*
		Uncomment to see the output

		for(auto &x:mst.second)
		{
			std::cout<<x.u<<" "<<x.v<<" "<<x.edge<<std::endl;
		}
	*/

	/*
	The output for above code is :- 

	b a 4
	c b 8
	i c 2
	f c 4
	g f 2
	h g 1
	d c 7
	e d 9

	which is same as in book.
	
	*/

	
}

void test_case_2() //Floating point Example from Algorithms by Robert Sedgewick and Kevin Wayne
{
	graph<int, false, true, float> G;
	std::vector<int> v(7);

	assert(G.count_node() == 0);
	assert(G.count_edge() == 0);

	for (size_t i = 0; i < 7; i++)
	{
		v[i] = i;
	}

	G.add_node(v);

	assert(G.count_node() == 7);
	assert(G.count_edge() == 0);

	G.add_edge(v[0], v[2], 0.22);
	G.add_edge(v[0], v[4], 0.64);
	assert(G.count_node() == 7);
	assert(G.count_edge() == 2);

	G.add_edge(v[1], v[2], 0.50);
	G.add_edge(v[1], v[3], 0.97);
	G.add_edge(v[1], v[5], 0.02);
	G.add_edge(v[1], v[6], 0.90);
	assert(G.count_node() == 7);
	assert(G.count_edge() == 6);

	G.add_edge(v[2], v[6], 0.17);
	assert(G.count_node() == 7);
	assert(G.count_edge() == 7);

	G.add_edge(v[4], v[6], 0.62);
	assert(G.count_node() == 7);
	assert(G.count_edge() == 8);

	G.add_edge(v[5], v[6], 0.88);
	assert(G.count_node() == 7);
	assert(G.count_edge() == 9);

	std::function<float(float)> get_weight_4 = [](float x)
	{
		return x;
	};

	auto mst = G.prims_minimum_spanning_tree<float>(get_weight_4);

	assert(fabsl(mst.first - 2.5l) < EPS);

	/*

	Uncomment to see the results

	for(auto &x:mst.second)
	{
		std::cout<<x.u<<" "<<x.v<<" "<<x.edge<<std::endl;
	}

	*/

	/*
	The output for the above code is :-


	2 0 0.22
	6 2 0.17
	1 2 0.5
	5 1 0.02
	4 6 0.62
	3 1 0.97

	which is same as in book.
	
	*/

	mst = G.krushkal_minimum_spanning_tree<float>(get_weight_4);

	assert(fabsl(mst.first - 2.5l) < EPS);

	/*

	Uncomment the following to see the results

	for(auto &x:mst.second)
	{
		std::cout<<x.u<<" "<<x.v<<" "<<x.edge<<std::endl;
	}

	*/


	/*
	The output for the above code is :-

	1 5 0.02
	2 6 0.17
	0 2 0.22
	1 2 0.5
	4 6 0.62
	1 3 0.97

	which is same as in book.

	*/

}

void test_case_3() //Floating point and negative weight Example from Algorithms by Robert Sedgewick and Kevin Wayne
{
	graph<int, false, true, double> G;
	std::vector<int> v(7);

	assert(G.count_node() == 0);
	assert(G.count_edge() == 0);

	for (size_t i = 0; i < 7; i++)
	{
		v[i] = i;
	}

	G.add_node(v);

	assert(G.count_node() == 7);
	assert(G.count_edge() == 0);

	G.add_edge(v[0], v[2], 0.22);
	G.add_edge(v[0], v[4], -0.99);
	assert(G.count_node() == 7);
	assert(G.count_edge() == 2);

	G.add_edge(v[1], v[2], 0.50);
	G.add_edge(v[1], v[3], 0.97);
	G.add_edge(v[1], v[5], 0.02);
	G.add_edge(v[1], v[6], 0.0);
	assert(G.count_node() == 7);
	assert(G.count_edge() == 6);

	G.add_edge(v[2], v[6], 0.17);
	assert(G.count_node() == 7);
	assert(G.count_edge() == 7);

	G.add_edge(v[4], v[6], 0.62);
	assert(G.count_node() == 7);
	assert(G.count_edge() == 8);

	G.add_edge(v[5], v[6], 0.88);
	assert(G.count_node() == 7);
	assert(G.count_edge() == 9);

	auto get_weight_5 = [](double x)
	{
		return x;
	};

	auto mst = G.krushkal_minimum_spanning_tree<long double>(get_weight_5);

	assert(fabsl(mst.first - 0.39l) < EPS);

	/*

	Uncomment this to see the results

	for(auto &x:mst.second)
	{
		std::cout<<x.u<<" "<<x.v<<" "<<x.edge<<std::endl;
	}

	*/

	/*
	The output for the above code is :-

	0 4 -0.99
	1 6 0
	1 5 0.02
	2 6 0.17
	0 2 0.22
	1 3 0.97

	which is same as in book.

	*/

	mst = G.prims_minimum_spanning_tree<double>(get_weight_5);

	assert(fabsl(mst.first - 0.39l) < EPS);

	/*

	Uncomment this to see the results

	for(auto &x:mst.second)
	{
		std::cout<<x.u<<" "<<x.v<<" "<<x.edge<<std::endl;
	}

	*/

	/*
	The output for the above code is :-

	4 0 -0.99
	2 0 0.22
	6 2 0.17
	1 6 0
	5 1 0.02
	3 1 0.97

	which is same as in book.

	*/


}


void run_test_case()
{
	test_case_1();
	test_case_2();
	test_case_3();
}

int main()
{
	run_test_case();

	return 0;
}