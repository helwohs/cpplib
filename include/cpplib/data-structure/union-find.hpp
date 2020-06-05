#pragma once
#include <cpplib/stdinc.hpp>

class UnionFind
{
public:
    UnionFind(const size_t graph_size) :
        root(vector<size_t>(graph_size)), sz(vector<size_t>(graph_size, 1))
    {
        iota(all(root), 0);
    }

    UnionFind(const size_t graph_size, const vector<pair<size_t, size_t> > &edges) :
        UnionFind(graph_size)
    {
        for(const pair<size_t, size_t> &e : edges)
            merge(e.ff, e.ss);
    }

    size_t find(const size_t x)
    {
        return root[x] == x? x : root[x] = find(root[x]);
    }

    bool merge(size_t a, size_t b)
    {
        a = find(a);
        b = find(b);

        if(a == b)
            return false;

        if(sz[a] < sz[b])
            swap(a, b);

        root[b] = a;
        sz[a] += sz[b];
        return true;
    }

    bool same(const size_t a, const size_t b)
    {
        return find(a) == find(b);
    }

    size_t size(const size_t x)
    {
        return sz[find(x)];
    }

private:
    vector<size_t> root, sz;
};