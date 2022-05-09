#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#include <iostream>
#include <queue>

#include <sstream>
class Graph
{
private:

    struct Vertex
    {
        /*
        each verte holds a value
        a vertex knows its neighbours, to do this, use a vector<Vertex>
        a vertex also has an edge, and an edge is simple a source and a destination
        */
        size_t id;
        size_t index;

        bool visited;
        size_t distance;

        Vertex *previous;

        // vertex constructor
        Vertex(size_t i, size_t in, size_t d = std::numeric_limits<int>::max(), bool v = false) : id(i), index(in), visited(v), distance(d), previous(nullptr) {}
        Vertex(const Vertex& other) : id(other.id), index(other.id), visited(other.visited), distance(other.distance), previous(other.previous) {}
        ~Vertex() {
            previous = nullptr;
            delete this;
        }
    };


    // unordered set to keep count of vertices presenent
    std::unordered_set<size_t> id_set{}; // using this so when using contains we could easly check if its in the set. Each id will be unique
    // List of some sort to hold the vertices in the graph
    std::vector<Vertex*> vertices{};

    // Maybe add -
    std::vector<std::vector<size_t>> weights{};
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
        throw std::invalid_argument("id not in vertices (find_vertex_index)");
    }

    void reset_vertices() {
        for (size_t i = 0; i < v_count; i++) {
            vertices[i]->distance = std::numeric_limits<int>::max();
            vertices[i]->visited = false;
            vertices[i]->previous = nullptr;
        }
    }

public:
    // Task 1
    // start
    Graph() : v_count(0), e_count(0) {}

    Graph(const Graph &other) : id_set(other.id_set), weights(other.weights), v_count(other.v_count), e_count(other.e_count) {
        for (Vertex* v: other.vertices) {
            vertices.push_back(v);
        }
    }
    
    Graph &operator=(const Graph &other) {
        if (this != &other)
        {
            this->id_set = other.id_set;
            this->vertices.clear();
            for (Vertex* v: other.vertices) {
                vertices.push_back(v);
            }
            this->weights = other.weights;
            this->v_count = other.v_count;
            this->e_count = other.e_count;
        }
        return *this;
    }

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
        size_t src_i = find_vertex_index(src);
        size_t dest_i = find_vertex_index(dest);
        if (weights[src_i][dest_i] == 0)
            return std::numeric_limits<int>::max();
        return weights[src_i][dest_i];
    };

    /*0 1
    0 0 0
    1 2 0
    */
    bool add_vertex(size_t id)
    {

        if (contains_vertex(id)) {
            return false;
        }

        Vertex *new_vertex = new Vertex(id, v_count);
        vertices.emplace_back(new_vertex);

        std::vector<size_t> newRow(v_count + 1);
        weights.emplace_back(newRow);

        id_set.insert(id);

        for (size_t i = 0; i < weights.size() - 1; i++) {
            weights[i].resize(v_count + 1);
        }

        v_count++;
        return true;
    }

    bool add_edge(size_t src, size_t dest, double weight = 1) {
        if (contains_edge(src, dest)) {
            return false;
        }
        size_t src_i = find_vertex_index(src);
        size_t dest_i = find_vertex_index(dest);

        // std::cout << "add edge source index: " <<src_i << " add edge dest index: " << dest_i << std::endl;
        weights[src_i][dest_i] = weight;
<<<<<<< HEAD
        // add neighbhor to both vertices
=======
>>>>>>> 556f23d20586496bf00a47dcd80c1dfa3d157104
        e_count++;

        return true;
    }

    bool remove_vertex(size_t id) {
        if (!contains_vertex(id)) {
            return false;
        }
        size_t index = find_vertex_index(id);
        id_set.erase(id_set.find(id));
        
        //Vertex *del = std::move(vertices[index]);
        for (size_t i = index; i < vertices.size() - 1; i++) {
            vertices[i] = std::move(vertices[i + 1]);
            vertices[i]->index = vertices[i]->index - 1;
        }
        //std::cout << "Check1" <<std::endl;
        vertices.pop_back();
        weights.pop_back();

        for (size_t i = 0; i < weights.size(); i++) {
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

    // Task 2 - remember to set everything like distamce amdn visited to default value
    size_t minimum_weight() const {
        size_t minimum = std::numeric_limits<int>::max();
        size_t minimum_index = 0;
        for (size_t i = 0; i < v_count; i++) {
            if (vertices[i]->visited == false && vertices[i]->distance < minimum) {
                minimum = vertices[i]->distance;
                minimum_index = i;
            }
        }
        return minimum_index;
    }

    void prim(size_t source_id) {
        reset_vertices();
        size_t index_first = find_vertex_index(source_id);
        vertices[index_first]->distance = 0;

        for (size_t i = 0; i < v_count-1; i++) {
            size_t ind_a = minimum_weight();

            vertices[ind_a]->visited = true;

            for (size_t ind_b = 0; ind_b < v_count; ind_b++) {
                if (weights[ind_a][ind_b] > 0 && weights[ind_a][ind_b] < vertices[ind_b]->distance && vertices[ind_b]->visited == false ) {
                    vertices[ind_b]->previous = vertices[ind_a];
                    vertices[ind_b]->distance = weights[ind_a][ind_b];
                }
            }
        }
    }

    bool is_path(size_t id) const {
        size_t index = find_vertex_index(id);
        return vertices[index]->distance != std::numeric_limits<int>::max();
    }

    void print_path(size_t dest_id, std::ostream &os = std::cout) const {
        if (!is_path(dest_id)) {
            os << "<no path>\n";
            return;
        }

        size_t dest_id_index = find_vertex_index(dest_id);
        Vertex* curr = vertices[dest_id_index];
        size_t tot_dist = 0;
        std::vector<size_t> pathway;
        pathway.push_back(curr->index);
        curr = curr->previous;
        while (curr) {
            pathway.push_back(curr->index);
            curr = curr->previous;
        }

        for (size_t i = pathway.size()-1; i > 0; i--) {
            tot_dist += vertices[pathway[i]]->distance;
            os << vertices[pathway[i]]->id << " --> ";
        }
        tot_dist += vertices[pathway[0]]->distance;
        os << vertices[pathway[0]]->id << std::endl;
    }

    // Task 3
    size_t next_unvisited_index() {
        for (size_t i = 0; i < v_count; i++) {
            if (vertices[i]->visited == false) {
                return i;
            }
        }
        return std::numeric_limits<int>::max();
    }
    
    void dijkstra(size_t source_id) {
        reset_vertices();
        size_t src_i = find_vertex_index(source_id);
        Vertex* v = vertices[src_i];
        Vertex* w;
        v->distance = 0;
        while (v->visited == false) {
            v->visited = true;
            for (size_t i = 0; i < v_count; i++) {
                w = vertices[i];
                if (vertices[i]->visited == false && weights[v->index][i] > 0) {
                    size_t dist_vw = weights[v->index][i];
                    if (v->distance + dist_vw < w->distance) {
                        w->distance = v->distance + dist_vw;
                        w->previous = v;
                    }
                }
            }
            v = vertices[next_unvisited_index()];
        }

        
    }

    double distance(size_t id) const {
        if (!contains_vertex(id)) {
            return (double) std::numeric_limits<int>::max();
        }
        size_t index = find_vertex_index(id);
        Vertex* curr = vertices[index];
        double tot_dist = (double) curr->distance;
        return tot_dist;
    }

    void print_shortest_path(size_t dest_id, std::ostream &os = std::cout) const {
        if (distance(dest_id) == (double) std::numeric_limits<int>::max()) {
            os << "<no path>\n";
            return;
        }
        size_t index = find_vertex_index(dest_id);
        Vertex* curr = vertices[index];
        std::vector<size_t> pathway;
        while (curr) {
            pathway.push_back(curr->index);
            curr = curr->previous;
        }

        for (size_t i = pathway.size()-1; i > 0; i--) {
            os << vertices[pathway[i]]->id << " --> ";
        }
        os << vertices[pathway[0]]->id << " distance: " << vertices[pathway[0]]->distance << std::endl;
    }

    // helper
    void print_tree() {
        std::cout << "Vertices: ";
        for (size_t i = 0; i < vertices.size(); i++) {
            std::cout << vertices[i]->id << " ";
        }
        std::cout << std::endl;

        for (size_t i = 0; i < weights.size(); i++) {
            for (size_t j = 0; j < weights[i].size(); j++) {
                std::cout << weights[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

#endif // GRAPH_H
