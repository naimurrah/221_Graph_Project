#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#include <iostream>
#include <queue>

class Graph {
private:
    // TODO(student): implement graph

public:
    // Task 1
    Graph();
    Graph(const Graph& other);
    Graph& operator=(const Graph& other);
    ~Graph();

    size_t vertex_count() const;
    size_t edge_count() const;

    bool contains_vertex(size_t id) const;
    bool contains_edge(size_t src, size_t dest) const;
    double cost(size_t src, size_t dest) const;

    bool add_vertex(size_t id);
    bool add_edge(size_t src, size_t dest, double weight=1);
    bool remove_vertex(size_t id);
    bool remove_edge(size_t src, size_t dest);

    // Task 2
    void prim(size_t source_id);
    bool is_path(size_t id) const;
    void print_path(size_t dest_id, std::ostream& os=std::cout) const;

    // Task 3
    void dijkstra(size_t source_id);
    double distance(size_t id) const;
    void print_shortest_path(size_t dest_id, std::ostream& os=std::cout) const;
};

#endif  // GRAPH_H
