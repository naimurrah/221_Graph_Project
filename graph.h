#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#include <iostream>
#include <queue>

class Graph
{
private:
    // TODO(student): implement graph
    // struct Edge;

    struct Vertex
    {
        /*
        each verte holds a value
        a vertex knows its neighbours, to do this, use a vector<Vertex>
        a vertex also has an edge, and an edge is simple a source and a destination
        */
        size_t id;

        size_t index;
        std::vector<size_t> neigh_index; // indices of the neigh_index;
        // std::vector<Edge> edges;

        // pretty sure these are used during traversal.
        bool visited;
        int distance;
        Vertex *previous;
        // &Edge find edge(Vertex destination) // returns an edge with this being point a and destination point b

        // vertex constructor
        Vertex(size_t i, size_t in, size_t d = std::numeric_limits<int>::max(), bool v = false) : id(i), index(in), neigh_index(), visited(v), distance(d), previous(nullptr) {}
        // Vertex(Vertex &other) : id(other.id), index(other.index), neigh_index(other.neigh_index), visited(other.visited), distance(other.distance), previous(other.previous) {}

        // Vertex &operator=(const Vertex &other)
        // {
        //     if (this != &other)
        //     {
        //         id = other.id;
        //         index = other.index;
        //         neigh_index = other.neigh_index;
        //         visited = other.visited;
        //         distance = other.distance;
        //         previous = nullptr; // look  at this later
        //     }
        //     return *this;
        // }

        ~Vertex()
        {
            previous = nullptr;
            neigh_index.clear();
        }
    };

    // Struct for an edge
    /*
    An edge contains its start and end points and the weight of the edge as well.

    */
    /*
    struct Edge
    {
        Vertex start;
        Vertex end;
        size_t weight;
        Edge(Vertex s, Vertex e, size_t w) : start(s), end(e), weight(w) {}
    };
    */

    // unordered set to keep count of vertices presenent
    std::unordered_set<size_t> id_set{}; // using this so when using contains we could easly check if its in the set. Each id will be unique
    // List of some sort to hold the vertices in the graph
    std::vector<Vertex *> vertices{};

    // Maybe add -
    std::vector<std::vector<size_t>> weights{};
    /*0
    0 0
    */
    size_t v_count; // vertex count
    size_t e_count; // edge count

    size_t find_vertex_index(size_t id) const
    {
        for (Vertex *v : vertices)
        {
            if (v->id == id)
            {
                return v->index;
            }
        }
        return 10000000;
    }

public:
    // Task 1
    // start
    Graph() : v_count(0), e_count(0){};
    Graph(const Graph &other) : id_set(other.id_set), vertices(other.vertices), weights(other.weights), v_count(other.v_count), e_count(other.e_count){};
    Graph &operator=(const Graph &other)
    {
        if (this != &other)
        {
            this->id_set = other.id_set;
            this->vertices = other.vertices;
            this->weights = other.weights;
            this->v_count = other.v_count;
            this->e_count = other.e_count;
        }
        return *this;
    };
    ~Graph()
    {
        id_set.clear();
        vertices.clear();
        weights.clear();
        v_count = 0;
        e_count = 0;
    };

    size_t vertex_count() const
    {
        return v_count;
    };
    size_t edge_count() const
    {
        return e_count;
    };

    bool contains_vertex(size_t id) const
    {
        return !(id_set.find(id) == id_set.end());
    }

    bool contains_edge(size_t src, size_t dest) const
    {
        size_t src_i = find_vertex_index(src);
        size_t dest_i = find_vertex_index(dest);

        return weights[src_i][dest_i] != 0;
    }

    double cost(size_t src, size_t dest) const
    {
        if (weights[src][dest] == 0)
            return std::numeric_limits<int>::max();
        return weights[src][dest];
    };

    /*0 1
    0 0 0
    1 2 0
    */
    bool add_vertex(size_t id)
    {

        if (contains_vertex(id))
        {
            return false;
        }

        Vertex *new_vertex = new Vertex(id, v_count);
        vertices.emplace_back(new_vertex);
        std::vector<size_t> newRow(v_count + 1);
        weights.emplace_back(newRow);
        id_set.insert(id);

        for (size_t i = 0; i < weights.size() - 1; i++)
        {
            weights[i].resize(v_count + 1);
        }

        v_count++;
        return true;
    }

    bool add_edge(size_t src, size_t dest, double weight = 1)
    {
        if (contains_edge(src, dest))
        {
            return false;
        }
        size_t src_i = find_vertex_index(src);
        size_t dest_i = find_vertex_index(src);
        weights[src_i][dest_i] = weight;
        // add neighbhor to both vertices

        return true;
    }

    bool remove_vertex(size_t id)
    {
        if (!contains_vertex(id))
        {
            return false;
        }
        size_t index = find_vertex_index(id);
        id_set.erase(id_set.find(id));

        Vertex *del = std::move(vertices[index]);
        delete del;

        for (size_t i = index; i < vertices.size() - 1; i++)
        {
            vertices[i] = std::move(vertices[i + 1]);
            vertices[i]->index = vertices[i]->index - 1;
            // remove neighbor if exists
        }
        vertices.pop_back();
        weights.pop_back();

        for (size_t i = 0; i < weights.size(); i++)
        {
            auto remove = weights[i].begin() + index;
            weights[i].erase(remove);
        }

        v_count--;
        return true;
    }

    bool remove_edge(size_t src, size_t dest)
    {
        if (!contains_edge(src, dest))
        {
            return false;
        }
        size_t src_i = find_vertex_index(src);
        size_t dest_i = find_vertex_index(dest);

        weights[src_i][dest_i] = 0;
        e_count--;
        return true;
    };

    // Task 2
    void prim(size_t source_id);
    bool is_path(size_t id) const;
    void print_path(size_t dest_id, std::ostream &os = std::cout) const;

    // Task 3
    void dijkstra(size_t source_id);
    double distance(size_t id) const;
    void print_shortest_path(size_t dest_id, std::ostream &os = std::cout) const;
};

#endif // GRAPH_H
