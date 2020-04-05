#pragma once
#include <cpplib/stdinc.hpp>
#include <cpplib/data-structures/trees/heap.hpp>

/**
 * Dijkstra.
 *
 * Computes the shortest path from a source
 * to all other vertices in a weighted
 * graph given its weighted vertex
 * adjacencies.
 *
 * Note: in orther to retrieve the shortest
 * path we can store the predecessor of
 * each vertex when a successful relaxation
 * occurs.
 *
 * Time Complexity: O(m*log(n)).
 * Space Complexity: O(n).
 * Where n is the size of the graph and m is the quantity of edges.
 */
vi dijkstra(const int s, const vvii &adj){
    vi dis(adj.size(), INF); dis[s] = 0; // distance from s to s is 0.
    min_heap<ii> pq; pq.push({dis[s], s});

    while(!pq.empty()){
        ii top = pq.top(); pq.pop();

        int d = top.ff, u = top.ss;
        if(d > dis[u])
            continue;

        for(ii p : adj[u]){
            int v = p.ff, w = p.ss;
            if(dis[u] + w < dis[v]){
                dis[v] = dis[u] + w;
                pq.push({dis[v], v});
            }
        }
    }
    return dis;
}