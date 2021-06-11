//Implementation of Disjoint Set Union data structure

disjoint_set_union :: disjoint_set_union(int n)
{
    parent.resize(n+1);
    size.resize(n+1);
    for(size_t i=0;i<n;i++)
    {
        parent[i] = i;
        size[i] = 1;
    }
}

int disjoint_set_union :: find_parent(int x)    //Path Compression
{
    if(parent[x] == x)
        return x;
    parent [x] = find_parent(parent [x] );  //try to implement using stack
    return parent[x];
}

const bool disjoint_set_union :: is_same(int x,int y)
{
    int px = find_parent(x) , py = find_parent(y);
    return px == py;
}

int disjoint_set_union :: find_size(int x)
{
    int px = find_parent(x);
    return size[px];
}

void disjoint_set_union :: do_union(int x,int y)
{
    int px = find_parent(x), py = find_parent(y);
    if (px == py)
        return;
    if (size[px] >= size[py])       //Union by Rank
    {
        size[px] += size[py];
        parent[y] = px;
        parent[py] = px;
    }
    else
    {
        do_union(y,x);
    }
    
}