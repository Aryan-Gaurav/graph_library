

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
    //Kosaraju algorithm
    // std::stack<int> stk;
    // bool vis[n] = { 0 };
    return {};
}