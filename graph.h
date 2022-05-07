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
    struct Edge;

    struct Vertex{
        /*
        each verte holds a value
        a vertex knows its neighbours, to do this, use a vector<Vertex>
        a vertex also has an edge, and an edge is simple a source and a destination
        */
        size_t id;
        std::list<Vertex> neighbors;
        std::list<Edge> edges;

        //pretty sure these are used during traversal.
        bool visited;
        size_t distance;
        Vertex* previous;       

        // vertex constructor
        Vertex(size_t i, std::list<Vertex> n, std::list<Edge> e, bool v, size_t d, Vertex* p = nullptr) : id(i), neighbors(n), edges(e), visited(v), distance(d), previous(p){}
    };

// Struct for an edge
/*
An edge contains its start and end points and the weight of the edge as well.

*/
    struct Edge{
        Vertex start;
        Vertex end;
        size_t weight;

        Edge(Vertex s, Vertex e, size_t w) : start(s), end(e), weight(w){}
    };

    // unordered set to keep count of vertices presenent
    std::unordered_set <size_t> id_set; // using this so when using contains we could easly check if its in the set. Each id will be unique
    // List of some sort to hold the vertices in the graph
    std::list<Vertex> vertices;
    size_t v_count; // vertex count
    size_t e_count; // edge count
public:
    // Task 1
    // start
    Graph(): v_count(0), e_count(0){};
    Graph(const Graph& other){
        if(other.vertices.size() == 0){
            this->v_count = 0;
            this->e_count = 0;
            return;
        }
        this->id_set = other.id_set;
        this->vertices = other.vertices;
        this->v_count = other.v_count;
        this->e_count = other.e_count;

      // need to think more but this is where   
        

    };
    Graph& operator=(const Graph& other);
    ~Graph();

    size_t vertex_count() const{
        return v_count;
    };
    size_t edge_count() const{
        return e_count;
    };

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
