/*****************************************
** File:    graph.h
** Project: CSCE 221 Lab 7
** Author:  Naimur S. M. Rahman & Uchenna Akahara
** Date:    04/22/2022
** Section: 511
** E-mails:  naimurrah01@tamu.edu & akaharauchenna@tamu.edu
** Description: Main logic of the Graph ADT.
******************************************/

#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#include <iostream>
#include <queue>

#include <vector>
class Graph
{
private:
    struct Vertex
    {
        size_t id;
        size_t index; // spot in vertices

        // prim and dijkstra traversal
        double distance;
        bool visited;

        int previous; // index of previous vertex in vertices, -1 by default

        // normal constructor
        Vertex(size_t id, size_t index, double distance, bool visited) : id(id), index(index), distance(distance), visited(visited), previous(-1) {}
        // constructor with default values
        Vertex(size_t id, size_t index) : id(id), index(index)
        {
            distance = INFINITY;
            visited = false;
            previous = -1;
        }
        // copy constructor - for push_back
        Vertex(const Vertex &other) : id(other.id), index(other.index), distance(other.distance), visited(other.visited)
        {
            previous = other.previous;
        }
    };

    std::vector<std::vector<double>> weights; // adjacency matrix of edges
    std::vector<Vertex> vertices; // list of all the vertices

    size_t v_count; // vertex count
    size_t e_count; // edge count

    int source_prim; // the index of the vertex prim is used on
    // helpers

    //-------------------------------------------------------
    // Name: find_vertex_index(size_t id) const
    // PreCondition:  Accepts a value of type size_t, id.
    // PostCondition: Retruns the index of specified vertex in the vector vertices. Returns v_count+1 if vertex is not in the vector
    //---------------------------------------------------------
    size_t find_vertex_index(size_t id) const
    {
        size_t i = 0;
        for (Vertex v : vertices)
        {
            if (v.id == id)
            {
                return i;
            }
            i++;
        }
        // if not in vertices = give number greater than the amount of total vertices
        return vertices.size() + 1;
    }

    //-------------------------------------------------------
    // Name: reset_vertices()
    // PreCondition: At least one vertex is present in graph.
    // PostCondition: Sets the private fields for al vertex in vertices (distance, visited, and previous) to inifity, false and -1 respectively.
    //---------------------------------------------------------
    void reset_vertices()
    {
        for (size_t i = 0; i < v_count; i++)
        {
            vertices[i].distance = INFINITY;
            vertices[i].visited = false;
            vertices[i].previous = -1;
        }
    }

    //-------------------------------------------------------
    // Name: count_edge(size_t id)
    // PreCondition: Accepts a value of type size_t, the id of a vertex.
    // PostCondition: Counts the number of edeges associated with the specified vertex and returns its value.
    //---------------------------------------------------------

    size_t count_edge(size_t id)
    {
        size_t src_id = find_vertex_index(id);
        size_t num = 0;
        for (size_t i = 0; i < v_count; i++)
        {
            if (weights[src_id][i] != 0)
            {
                num++;
            }
            if (weights[i][src_id] != 0)
            {
                num++;
            }
        }

        return num;
    }

    //-------------------------------------------------------
    // Name: min_weight() const
    // PreCondition: At least one vertex is present in graph.
    // PostCondition: Returns the index of vertex in vertices that has the smallest distance val. Used during traversal for Prim's Algo.
    //---------------------------------------------------------
    size_t min_weight() const
    {
        double min = INFINITY;
        size_t min_index = 0;
        for (size_t i = 0; i < v_count; i++)
        {
            if (vertices.at(i).visited == false && vertices.at(i).distance < min)
            {
                min = vertices[i].distance;
                min_index = i;
            }
        }
        return min_index;
    }

    //-------------------------------------------------------
    // Name: any_unvisited()
    // PreCondition: At least one vertex is present in the graph.
    // PostCondition:Checks all vertices to confirm if there is an unvisited vertex present. If so, returns true, false otherwise.
    //---------------------------------------------------------
    bool any_unvisited()
    {
        for (Vertex v : vertices)
        {
            if (!v.visited)
            {
                return true;
            }
        }
        return false;
    }

    //-------------------------------------------------------
    // Name: min_weight_d() const
    // PreCondition: At least one vertex is present in graph.
    // PostCondition: Returns the index of vertex in vertices that has the smallest distance val. Used during traversal for Dijkstra's Algo.
    //---------------------------------------------------------
    size_t min_weight_d() const
    {
        double min = INFINITY;
        size_t min_index = 0;
        for (size_t i = 0; i < v_count; i++)
        {
            if (vertices.at(i).visited == false && vertices.at(i).distance <= min)
            {
                min = vertices[i].distance;
                min_index = i;
            }
        }
        return min_index;
    }
public:
    // Task 1
    //-------------------------------------------------------
    // Name: Graph()
    // PreCondition:
    // PostCondition: Makes an empty graph.
    //---------------------------------------------------------
    Graph() : v_count(0), e_count(0), source_prim(0) {}

    //-------------------------------------------------------
    // Name: Graph(const Graph&)
    // PreCondition: Accetps a Graph object.
    // PostCondition: constructs a deep copy of a graph.
    //---------------------------------------------------------
    Graph(const Graph &other) : v_count(other.v_count), e_count(other.e_count), source_prim(other.source_prim)
    {
        weights = other.weights;
        vertices = other.vertices;
    }

    //-------------------------------------------------------
    // Name: Graph& operator=(const Graph&)
    // PreCondition: Accetps a Graph object.
    // PostCondition: constructs a deep copy of a graph.
    //---------------------------------------------------------
    Graph &operator=(const Graph &other)
    {
        if (this != &other)
        {
            vertices = other.vertices;
            weights = other.weights;
            v_count = other.v_count;
            e_count = other.e_count;
            source_prim = other.source_prim;
        }
        return *this;
    }

    //-------------------------------------------------------
    // Name: ~Graph()
    // PreCondition: Graph object is present.
    // PostCondition: destructs a graph (frees all dynamically allocated memory).
    //---------------------------------------------------------
    ~Graph()
    {
        reset_vertices();

        vertices.clear();
        weights.clear();
        e_count = 0;
        v_count = 0;
        source_prim = 0;
    }

    //-------------------------------------------------------
    // Name: vertex_count() const
    // PreCondition: Graph object is present.
    // PostCondition: Returns the number of vertices in the graph.
    //---------------------------------------------------------
    size_t vertex_count() const
    {
        return v_count;
    }

    //-------------------------------------------------------
    // Name: edge_count() const
    // PreCondition: Graph object is present.
    // PostCondition: Returns the number of edges in the graph.

    //---------------------------------------------------------
    size_t edge_count() const
    {
        return e_count;
    }

    //-------------------------------------------------------
    // Name: contains_vertex(size_t id) const
    // PreCondition: Accepts a value of type size_t, i.e. the specified vertex id value.
    // PostCondition: Return true if the graph contains a vertex with the specified identifier, false otherwise.
    //---------------------------------------------------------
    bool contains_vertex(size_t id) const
    {
        for (Vertex v : vertices) 
        {
            if (v.id == id)
            {
                return true; // vertex in vertices
            }
        }
        return false;
    }

    //-------------------------------------------------------
    // Name: contains_edge(size_t src, size_t dest) const
    // PreCondition: Accepts 2 values of type size_t, the IDs of specified start and end vertices.
    // PostCondition: Return true if the graph contains an edge with the specified members (as identifiers), false otherwise.
    //---------------------------------------------------------
    bool contains_edge(size_t src, size_t dest) const
    {
        // getting indices of the ids
        size_t src_i = find_vertex_index(src);
        size_t dest_i = find_vertex_index(dest);

        // checking if indices are valid - meaning if they are in the graph
        if (src_i >= vertices.size() || dest_i >= vertices.size())
        {
            return false;
        }

        return weights[src_i][dest_i] != 0;
    }

    //-------------------------------------------------------
    // Name: cost(size_t src, size_t dest) const
    // PreCondition: Accepts 2 values of type size_t, the IDs of specified start and end vertices.
    // PostCondition: Returns the weight of the edge between src and dest, or INFINITY if none exists.
    //---------------------------------------------------------
    double cost(size_t src, size_t dest) const
    {
        if (!contains_edge(src, dest))
        {   
            // no edge between the two vertices
            return INFINITY;
        }

        size_t src_i = find_vertex_index(src);
        size_t dest_i = find_vertex_index(dest);

        return weights[src_i][dest_i];
    }

    //-------------------------------------------------------
    // Name: add_vertex(size_t id)
    // PreCondition: Accepts a value of type size_t, i.e. the specified vertex id value.
    // PostCondition: Add a vertex with the specified identifier if it does not already exist, return true on success or false otherwise.
    //---------------------------------------------------------
    bool add_vertex(size_t id)
    {   
        // checking if vertex is in graph
        if (contains_vertex(id))
        {
            return false;
        }

        // adding vertex into vertices
        vertices.push_back(Vertex(id, v_count));

        // resizing adjacency matrix
        std::vector<double> newRow(v_count + 1); // adding new row
        weights.push_back(newRow);
        // increasing size of columns
        for (size_t i = 0; i < weights.size() - 1; i++)
        {
            weights[i].resize(v_count + 1);
        }

        v_count++; // increasing count of vertices since added
        return true;
    }

    //-------------------------------------------------------
    // Name: add_edge(size_t src, size_t dest, double weight = 1)
    // PreCondition: Accepts 2 values of type size_t, the IDs of specified start and end vertices. Accepts a double, weight.
    // PostCondition: add a directed edge from src to dest with the specified weight if there is no edge from src to dest, return true on success, false otherwise.
    //---------------------------------------------------------
    bool add_edge(size_t src, size_t dest, double weight = 1)
    {   
        // checking if edge already exists
        if (contains_edge(src, dest))
        {
            return false;
        }

        size_t src_i = find_vertex_index(src);
        size_t dest_i = find_vertex_index(dest);

        // checking if vertices are in graph
        if (src_i >= v_count || dest_i >= v_count)
        {
            return false;
        }
        // adding the edge
        weights[src_i][dest_i] = weight;
        e_count++; // counting num edge

        return true;
    }

    //-------------------------------------------------------
    // Name: remove_vertex(size_t id)
    // PreCondition: Accepts a value of type size_t, i.e. the specified vertex id value.
    // PostCondition: Remove the specified vertex from the graph, including all edges of which it is a member, return true on success, false otherwise.
    //---------------------------------------------------------
    bool remove_vertex(size_t id)
    {   
        // checking if vertex is not in graph
        if (!contains_vertex(id))
        {
            return false;
        }
        size_t num_e = count_edge(id); // counting the number of edges consisting of the vertex both as a source and destination
        size_t index = find_vertex_index(id); // index of vertex in vertices

        vertices.erase(vertices.begin() + index); // removing from vertices;

        // adjusting indexes for verticies affected
        for (size_t i = index; i < vertices.size(); i++)
        {
            vertices[i].index = i;
        }

        // resizing adjacency matrix
        weights.erase(weights.begin() + index); // removing row of vertex

        // removing column in each row
        for (size_t i = 0; i < weights.size(); i++)
        {
            auto remove = weights[i].begin() + index;
            weights[i].erase(remove);
        }

        v_count--; // since removed, decrementing
        e_count -= num_e; // accounting for all edges that are removed by removing vertex

        return true;
    }

    //-------------------------------------------------------
    // Name: remove_edge(size_t src, size_t dest)
    // PreCondition: Accepts 2 values of type size_t, the IDs of specified start and end vertices.
    // PostCondition: remove the specified edge from the graph, but do not remove the vertices, return true on success, false otherwise.
    //---------------------------------------------------------
    bool remove_edge(size_t src, size_t dest)
    {   
        // checking if edge exits in adjacency matrix
        if (!contains_edge(src, dest))
        {
            return false;
        }

        // getting vertices' index
        size_t src_i = find_vertex_index(src);
        size_t dest_i = find_vertex_index(dest);

        // checking if vertices exist in graph
        if (src_i >= vertices.size() || dest_i >= vertices.size())
        {
            return false;
        }

        // removing edge
        weights[src_i][dest_i] = 0;
        e_count--; // accounting for total amount

        return true;
    };

    // Task 2

    //-------------------------------------------------------
    // Name: prim(size_t source_id)
    // PreCondition: Accepts a value of type size_t, i.e. the specified vertex id value.
    // PostCondition: Computes the minimum spanning tree from the specified source vertex to all other vertices in the graph using Prim’s algorithm.
    //---------------------------------------------------------
    void prim(size_t source_id)
    {   
        // checking if source is in graph
        if (!contains_vertex(source_id))
        {
            return;
        }

        reset_vertices(); // resetting traversal values to default in each vertex

        size_t index_first = find_vertex_index(source_id); // index of source
        source_prim = index_first;

        vertices[index_first].distance = 0; // setting distance to 0

        for (size_t i = 0; i < v_count - 1; i++)
        {
            size_t ind_a = min_weight(); // index of vertex with the minimum distance at the moment and unvisited

            vertices[ind_a].visited = true;

            for (size_t ind_b = 0; ind_b < v_count; ind_b++)
            {   
                // looking for shortest path
                if (weights[ind_a][ind_b] > 0 && weights[ind_a][ind_b] < vertices[ind_b].distance && vertices[ind_b].visited == false)
                {
                    vertices[ind_b].previous = ind_a;
                    vertices[ind_b].distance = weights[ind_a][ind_b];
                }
            }
        }
    }

    //-------------------------------------------------------
    // Name: is_path(size_t id) const
    // PreCondition: Accepts a value of type size_t, i.e. the specified vertex id value.
    // PostCondition: Assumes Prim’s has been run, returns true if there is a path from the Prim-source vertex to the specified destination vertex.
    //---------------------------------------------------------
    bool is_path(size_t id) const
    {
        size_t index = find_vertex_index(id);

        // checking if vertex is in graph
        if (index >= vertices.size())
        {
            return false;
        }

        // if infinity - means there is no path
        if (vertices[index].distance == INFINITY)
        {
            return false;
        }

        // backtracking from vertex id and seeing if source_prim is the beginning of it;
        int curr = index;
        int check = -1;
        while (curr != -1)
        {
            check = curr;
            curr = vertices[curr].previous;
        }
        return check == source_prim;
    }

    //-------------------------------------------------------
    // Name: print_path(size_t dest_id, std::ostream &os = std::cout) const
    // PreCondition: Accepts a value of type size_t, dest_id, the specified traversal destination, and an output stream, os.
    // PostCondition: Assumes Prim’s has been run, pretty prints the minimum spanning path from the Prim source vertex to the specified destination vertex in a “ --> “- separated list from source to destination, or prints “<no path>\n” if the vertex is unreachable.
    //---------------------------------------------------------
    void print_path(size_t dest_id, std::ostream &os = std::cout) const
    {
        // checking if path exists
        if (!is_path(dest_id))
        {
            os << "<no path>\n";
            return;
        }

        size_t dest_id_index = find_vertex_index(dest_id);
        int curr = dest_id_index;
        std::vector<int> pathway; // holds indices that will be used to backtrack
        
        // backtracking the path
        while (curr != -1)
        {
            pathway.push_back(vertices[curr].id);
            curr = vertices[curr].previous;
        }

        // printing the apth
        for (size_t i = pathway.size() - 1; i > 0; i--)
        {
            os << pathway[i] << " --> ";
        }
        os << pathway[0] << std::endl;
    }

    // Task 3

    //-------------------------------------------------------
    // Name: dijkstra(size_t source_id)
    // PreCondition: Accepts a value of type size_t, i.e. the specified vertex id value.
    // PostCondition: destructs a graph (frees all dynamically allocated memory).
    //---------------------------------------------------------
    void dijkstra(size_t source_id)
    {   
        // checking if source is in graph
        if (!contains_vertex(source_id))
        {
            return;
        }

        reset_vertices(); // setting traversal values of all vertices to default
        size_t src_i = find_vertex_index(source_id);
        size_t v = src_i; // index of vertex v
        vertices[v].distance = 0; // setting distance to 0

        // will loop until all nodes are visited
        while (any_unvisited())
        {   
            vertices[v].visited = true;
            for (size_t i = 0; i < v_count; i++)
            {
                if (vertices[i].visited == false && weights[v][i] > 0)
                {
                    double dist_vw = weights[v][i]; // distance from v to vertex[i]
                    if (vertices[v].distance + dist_vw < vertices[i].distance)
                    {
                        vertices[i].distance = vertices[v].distance + dist_vw;
                        vertices[i].previous = v;
                    }
                }
            }

            v = min_weight_d(); // vertex v will now become the next vertex with the shortest distance from source

            // std::cout << "V: " << v << std::endl; // for debugging
        }
    }

    //-------------------------------------------------------
    // Name: distance(size_t id) const
    // PreCondition: Accepts a value of type size_t, i.e. the specified vertex id value.
    // PostCondition: assumes Dijkstra’s has been run, returns the cost of the shortest path from the Dijkstra-source vertex to the specified destination vertex, or INFINITY if the vertex or path does not exist.
    //---------------------------------------------------------
    double distance(size_t id) const
    {   
        // checking if vertex is in graph
        if (!contains_vertex(id))
        {
            return INFINITY;
        }

        size_t index = find_vertex_index(id);
        double tot_dist = vertices[index].distance;
        return tot_dist;
    }

    //-------------------------------------------------------
    // Name: print_shortest_path(size_t dest_id, std::ostream &os = std::cout) const
    // PreCondition: Accepts a value of type size_t, dest_id, the specified traversal destination, and an output stream, os.
    // PostCondition: Assumes Dijkstra’s has been run, pretty prints the shortest path from the Dijkstra source vertex to the specified destination vertex in a “ --> “- separated list with “ distance: #####” at the end, where <distance> is the minimum cost of a path from source to destination, or prints “<no path>\n” if the vertex is unreachable.
    //---------------------------------------------------------
    void print_shortest_path(size_t dest_id, std::ostream &os = std::cout) const
    {   
        // if distance is infinity, that means there is no path
        if (distance(dest_id) == INFINITY)
        {
            os << "<no path>\n";
            return;
        }

        size_t index = find_vertex_index(dest_id);
        int curr = index;
        std::vector<int> pathway; // gives indexes that will be used to backtrack
        
        // backtracking from dest_id
        while (curr != -1)
        {
            pathway.push_back(curr);
            curr = vertices[curr].previous;
        }

        // printing 
        for (size_t i = pathway.size() - 1; i > 0; i--)
        {
            os << vertices[pathway[i]].id << " --> ";
        }
        os << vertices[pathway[0]].id << " distance: " << vertices[pathway[0]].distance << std::endl;
    }

    // helper - for debugging and checking the edges

    //-------------------------------------------------------
    // Name: print_tree()
    // PreCondition: Graph object is present
    // PostCondition: Prints Matrix representation of vertices and their corresponding edge weights.
    //---------------------------------------------------------
    void print_tree()
    {
        // printing the ids in vertices
        std::cout << "Vertices: ";
        for (size_t i = 0; i < vertices.size(); i++)
        {
            std::cout << vertices[i].id << " ";
        }
        std::cout << std::endl;
        
        // printing the adjacency matrix
        for (size_t i = 0; i < weights.size(); i++)
        {
            for (size_t j = 0; j < weights[i].size(); j++)
            {
                std::cout << weights[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

#endif // GRAPH_H
