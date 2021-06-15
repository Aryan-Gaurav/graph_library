#include <vector>


//Function definations of Directed_Graph

template<typename N, typename E>
bool Directed_Graph<N, E> ::is_dag()    //TODO same implementation using stack i.e. without the recursive function
{
    //temprorary soution
    // auto n = Base<N,E> :: n;
    // auto adj = Base<N,E> ::adj;


    int vis[n] = { 0 };


    /*
        Recursive lambdas are not possible without removing auto with std::function
        Read more at http://pedromelendez.com/blog/2015/07/16/recursive-lambdas-in-c14/
        https://stackoverflow.com/questions/2067988/recursive-lambda-functions-in-c11
    */

    auto detect = [&](int y)->bool
    {
        auto lambda = [&](int src, const auto& func)->bool
        {
            vis[src] = 1; //color the node as gray
            bool isok = true;

            for (auto& [x, y] : adj[src])
            {
                if (vis[x] == 0)
                {
                    isok = isok && func(x, func);
                }
                else if (vis[x] == 1)
                {
                    return false;
                }
            }
            vis[src] = 2;   //color the node as black
            return isok;
        };
        return lambda(y, lambda);
    };

    
    for (size_t i = 0; i < n; i++)
    {
        if (vis[i] == 0)
        {
            if (detect(i) == false)
                return true;
        }
    }
    return false;
}


template<typename N, typename E>
std::vector<N> Directed_Graph<N, E> ::topo_sort()
{
    bool vis[n] = { 0 };
    int current_time = 0;
    int in_time[n], out_time[n];
    auto detect = [&](int y)->bool              //One possible improvement is to replace these lambda functions by a private function in the class itself
    {
        auto lambda = [&](int src, const auto& func)->bool
        {
            current_time += 1;
            in_time[src] = current_time;
            vis[src] = 1; //color the node as gray
            bool isok = true;

            for (auto& [x, y] : adj[src])
            {
                if (vis[x] == 0)
                {
                    isok = isok && func(x, func);
                }
                else if (vis[x] == 1)
                {
                    return false;
                }
            }
            current_time += 1;
            out_time[src] = current_time;
            vis[src] = 2;   //color the node as black
            return isok;
        };
        return lambda(y, lambda);
    };

    for (size_t i = 0; i < n; i++)
    {
        if (vis[i] == 0)
        {
            if (detect(i) == false)
            {
                return {};
            }
        }
    }

    std::vector<int> v(n);
    for (size_t i = 0; i < n; i++)
    {
        v[i] = i;
    }
    /*
    Sort the nodes by decreasing out times for topological sort. For more details refer Introduction to Algorithms by Cormen
    */
    sort(v.begin(), v.end(), [&](int i, int j) 
        {
            return out_time[i] > out_time[j];
        });

    std::vector<N> ans(n);
    for (size_t i = 0; i < n; i++)
    {
        ans[i] = node[v[i]];
    }

    return ans;
}


template<typename N, typename E>
std::vector<std::vector<N> >  Directed_Graph<N, E> ::scc() //TODO with Gobow Algorithm 
{
    //To read more about this Gabow algo go to :- https://www.cs.princeton.edu/courses/archive/spr09/cos423/Lectures/bi-gabow.pdf
    /*
        First write the recursive version of Gobow as it is easy to write.
        But if the DFS goes too deep it can cause STACKOVERFLOW so implement it iteratively.
        Remember before implementing iterative version, write the recursive version and then transform it
    */

   /*

        RECURSIVE IMPLEMENTATION

        vector<vector<int>> scc;
        void dfs(int v)
        {
            visit part
        	index [v] = stk.size();		
        	stk.push(v);	//current path stack
        	boundaries.push(index[v]);	//stack to store boundaries
            edge_visit part
        	for(auto [w,ed]:adj[x])
        	{
        		if(index[w] == -1)	//intialise each index as -1 as 0 can't be used
        		{
        			dfs(w);
        		}
        		else if(identified.count(w) == 0)
        		{
        			while(index[w] < boundaries.top())
        				boundaries.pop();
        		}
        	}
            post_visit_part
        	if(boundaries.top() == index[v])
        	{
        		boundaries.pop();
        		vector<int> temp;
        		while(stk.size() > index[v])
        		{
        			auto t = stk.top();
        			stk.pop();
        			temp.push_back(t);
        			identified.insert(t); // a set to identify if vertex is identified or not
        		}
        		scc.push_back(temp);
        	}
        }

        */

    std::stack<int> stk, boundaries;
    std::vector<int> index(n, -1); //intialise all to 0 in paper but here indexing starts from 0 so put -1
    bool is_identified[n] = { 0 }; //for checking if current node is included in any Strongly Connected Component (SCC)
	std::vector<std::vector<N> > scc;

	for (int i = 0 ; i < n ; i++)
	{
		if (index[i] == -1)
		{
			std::stack< pair<int, string> > recursion_stack; //for simulating the dfs function in paper iteratively
			recursion_stack.push({ i, "VISIT" });
			while ( recursion_stack.empty() == false )
			{
				auto [v, op] = recursion_stack.top();
				recursion_stack.pop();
                if (op == "VISIT")
                {
                    index[v] = stk.size();
                    stk.push(v);
                    boundaries.push(index[v]);
                    recursion_stack.push({v, "POST_VISIT"});
                    for (auto [w, ed] : adj[v])
                    {
                        recursion_stack.push({w, "EDGE_VISIT"});
                    }
                }
                else if (op == "EDGE_VISIT")
                {
                    if (index[v] == -1)
                    {
                        recursion_stack.push({v, "VISIT"});
                    }
                    else if (is_identified[v] == false)
                    {
                        while (index[v] < boundaries.top())
                        {
                            boundaries.pop();
                        }
                    }
                }
                else
                {
                    if (boundaries.top() == index[v])
                    {
                        boundaries.pop();
                        std::vector<N> temp;
                        while (stk.size() > index[v])
                        {
                            int t = stk.top();
                            stk.pop();
                            temp.push_back(node[t]);
                            is_identified[t] = true; // a set to identify if vertex is identified or not
                        }
                        scc.push_back(temp);
                    }
                }
            }
		}
	}

	return scc;
}