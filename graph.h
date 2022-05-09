#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#include <iostream>
#include <queue>

#include <vector>
class Graph {
private:
    struct Vertex {
        size_t id;
        size_t index;

        double distance;
        bool visited;

        int previous;

        Vertex(size_t id, size_t index, double distance, bool visited) : id(id), index(index), distance(distance), visited(visited), previous(-1) {}
        Vertex(size_t id, size_t index): id(id), index(index) {
            distance = INFINITY;
            visited = false;
            previous = -1;
        }
        Vertex(const Vertex& other): id(other.id), index(other.index), distance(other.distance), visited(other.visited) {
            previous = other.previous;
        }
    };

    std::vector<std::vector<double>> weights;
    std::unordered_set<size_t> id_set{};
    std::vector<Vertex> vertices;

    size_t v_count; // vertex count
    size_t e_count;

    int source_prim;
    // helpers
    size_t find_vertex_index(size_t id) const {
        size_t i = 0;
        for (Vertex v: vertices) {
            if (v.id == id) {
                return i;
            }
            i++;
        }
        return vertices.size()+1;
    }

    void reset_vertices() {
        for (size_t i = 0; i < v_count; i++) {
            vertices[i].distance = INFINITY;
            vertices[i].visited = false;
            vertices[i].previous = -1;
        }
    }

    size_t count_edge(size_t id) {
        size_t src_id = find_vertex_index(id);
        size_t num = 0;
        for (size_t i = 0; i < v_count; i++) {
            if (weights[src_id][i] != 0) {
                num++;
            }
            if (weights[i][src_id] != 0) {
                num++;
            }
        }

        return num;
    }

    bool any_unvisited(){
        for(Vertex v : vertices){
            if(!v.visited){
                return true;
            }
        }
        return false;
    }
public:
    // Task 1
    Graph(): v_count(0), e_count(0) {}
    Graph(const Graph& other): v_count(other.v_count), e_count(other.e_count) {
        weights = other.weights;
        vertices = other.vertices;
    }

    Graph& operator=(const Graph& other) {
        if (this != &other) {
            id_set.clear();
            id_set = other.id_set;
            vertices = other.vertices;
            weights = other.weights;
            v_count = other.v_count;
            e_count = other.e_count;
        }
        return *this;
    }
    ~Graph() {
        reset_vertices();
        // std::cout <<"DELETE ";
        // print_tree();
        // for (size_t i = 0; i < v_count; i++) {
        //     vertices.erase(vertices.begin());
        // }

        vertices.clear();
        id_set.clear();
        weights.clear();
        e_count = 0;
        v_count = 0;
    }

    size_t vertex_count() const {
        return v_count;
    }
    size_t edge_count() const {
        return e_count;
    }

    bool contains_vertex(size_t id) const {
        return !(id_set.find(id) == id_set.end());
    }

    bool contains_edge(size_t src, size_t dest) const {
        size_t src_i = find_vertex_index(src);
        size_t dest_i = find_vertex_index(dest);

        if (src_i >= vertices.size() || dest_i >= vertices.size()) {
            return false;
        }

        return weights[src_i][dest_i] != 0;
    }

    double cost(size_t src, size_t dest) const {
        if (!contains_edge(src, dest)) {
            return INFINITY;
        }
        size_t src_i = find_vertex_index(src);
        size_t dest_i = find_vertex_index(dest);
        return weights[src_i][dest_i];
    }

    bool add_vertex(size_t id) {
        if (contains_vertex(id)) {
            return false;
        }
        
        vertices.push_back(Vertex(id, v_count));
        
        std::vector<double> newRow(v_count + 1);
        weights.push_back(newRow);
        id_set.insert(id);
        for (size_t i = 0; i < weights.size() - 1; i++) {
            weights[i].resize(v_count + 1);
        }
        v_count++;
        return true;
    }

    bool add_edge(size_t src, size_t dest, double weight=1) {
        if (contains_edge(src, dest)) {
            return false;
        }

        size_t src_i = find_vertex_index(src);
        size_t dest_i = find_vertex_index(dest);
        if (src_i >= v_count || dest_i >= v_count) {
            return false;
        }

        weights[src_i][dest_i] = weight;
        e_count++;

        return true;
    }

    bool remove_vertex(size_t id) {
        if (!contains_vertex(id)) {
            return false;
        }
        size_t num_e = count_edge(id);
        size_t index = find_vertex_index(id);
        id_set.erase(id_set.find(id));

        vertices.erase(vertices.begin()+index);
        

        for (size_t i = index; i < vertices.size(); i++) {
            vertices[i].index = i;
        }


        weights.erase(weights.begin()+index);
        for (size_t i = 0; i < weights.size(); i++) {
            auto remove = weights[i].begin() + index;
            weights[i].erase(remove);
        }

        v_count--;
        e_count -= num_e;
        
        return true;
    }

    bool remove_edge(size_t src, size_t dest){
        if(!contains_edge(src, dest)){
            return false;
        }

        size_t src_i = find_vertex_index(src);
        size_t dest_i = find_vertex_index(dest);
        if (src_i >= vertices.size() || dest_i >= vertices.size())
        {
            return false;
        }

        weights[src_i][dest_i] = 0;
        e_count--;
        return true;
        
    };

    // Task 2

    size_t min_weight() const {
        double min = INFINITY;
        size_t min_index = 0;
        for(size_t i = 0; i < v_count; i++){
            if (vertices.at(i).visited == false && vertices.at(i).distance < min) {
                min = vertices[i].distance;
                min_index = i;
            }
        }
        return min_index;
    }

    void prim(size_t source_id) {
        if(!contains_vertex(source_id)){
            return;
        }
        reset_vertices();
        size_t index_first = find_vertex_index(source_id);
        source_prim = index_first;
        vertices[index_first].distance = 0;

        for (size_t i = 0; i < v_count-1; i++) {
            size_t ind_a = min_weight();

            vertices[ind_a].visited = true;

            for (size_t ind_b = 0; ind_b < v_count; ind_b++) {
                if (weights[ind_a][ind_b] > 0 && weights[ind_a][ind_b] < vertices[ind_b].distance && vertices[ind_b].visited == false ) {
                    vertices[ind_b].previous = ind_a;
                    vertices[ind_b].distance = weights[ind_a][ind_b];
                }
            }
        }
    }
    bool is_path(size_t id) const{
        size_t index = find_vertex_index(id);
        if (index >= vertices.size()) {
            return false;
        }
        if (vertices[index].distance == INFINITY) {
            return false;
        }
        int curr = index;
        int check = -1;
        while (curr != -1) {
            check = curr;
            curr = vertices[curr].previous;
        }
        return check == source_prim;

    }

    void print_path(size_t dest_id, std::ostream& os=std::cout) const {
        
        if (!is_path(dest_id)) {
            os << "<no path>\n";
            return;
        }
        
        size_t dest_id_index = find_vertex_index(dest_id);
        int curr = dest_id_index;
        std::vector<int> pathway;
        while (curr != -1) {
            pathway.push_back(vertices[curr].id);
            curr = vertices[curr].previous;
        }
        

        for (size_t i = pathway.size() -1; i > 0; i--) {
            os << pathway[i] << " --> ";
        }
        os << pathway[0] << std::endl;
    }

    // Task 3
    size_t min_weight_d() const {
        double min = INFINITY;
        size_t min_index = 0;
        for(size_t i = 0; i < v_count; i++){
            if (vertices.at(i).visited == false && vertices.at(i).distance <= min) {
                min = vertices[i].distance;
                min_index = i;
            }
        }
        return min_index;
    }

    void dijkstra(size_t source_id){
        if(!contains_vertex(source_id)){
            return;
        }

        reset_vertices();
        size_t src_i = find_vertex_index(source_id);
        size_t v = src_i;
        vertices[v].distance = 0;
        while (any_unvisited()) {
            vertices[v].visited = true;
            for (size_t i = 0; i < v_count; i++)
            {
                if (vertices[i].visited == false && weights[v][i] > 0)
                {
                    double dist_vw = weights[v][i];
                    if (vertices[v].distance + dist_vw < vertices[i].distance)
                    {
                        vertices[i].distance = vertices[v].distance + dist_vw;
                        vertices[i].previous = v;
                    }
                }
            }

            v = min_weight_d();
            std::cout << "V: " << v << std::endl;
        }
    }
    
    double distance(size_t id) const {
        if (!contains_vertex(id)) {
            return INFINITY;
        }
        size_t index = find_vertex_index(id);
        double tot_dist = vertices[index].distance;
        return tot_dist;
    }

    void print_shortest_path(size_t dest_id, std::ostream& os=std::cout) const {
        if (distance(dest_id) == INFINITY) {
            os << "<no path>\n";
            return;
        }

        size_t index = find_vertex_index(dest_id);
        int curr = index;
        std::vector<int> pathway;
        while (curr != -1) {
            pathway.push_back(curr);
            curr = vertices[curr].previous;
        }

        for (size_t i = pathway.size()-1; i > 0; i--) {
            os << vertices[pathway[i]].id << " --> ";
        }
        os << vertices[pathway[0]].id << " distance: " << vertices[pathway[0]].distance << std::endl;
    }
    
    // helper
    void print_tree() {

        std::cout << "Vertices: ";
        for (size_t i = 0; i < vertices.size(); i++) {
            std::cout << vertices[i].id << " ";
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

#endif  // GRAPH_H
