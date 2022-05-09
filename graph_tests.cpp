/*****************************************
** File:    graph_tests.cpp
** Project: CSCE 221 Lab 7
** Author:  Naimur S. M. Rahman & Uchenna Akahara
** Date:    04/22/2022
** Section: 511
** E-mails:  naimurrah01@tamu.edu & akaharauchenna@tamu.edu
** Description: Contains testing for the Graph ADT.
******************************************/

#include <iostream>
#include <sstream>
#include "graph.h"

using std::cout, std::endl;

int main()
{
    std::cout << "make an empty digraph" << std::endl;
    Graph G;

    std::cout << "add vertices" << std::endl;
    for (size_t n = 1; n <= 7; n++)
    {
        std::cout << "Count: " << G.vertex_count() << std::endl;
        G.add_vertex(n);
    }

    std::cout << "add directed edges" << std::endl;
    G.add_edge(1, 2, 5); // 1 ->{5} 2; (edge from 1 to 2 with weight 5)
    G.add_edge(1, 3, 3);
    G.add_edge(2, 3, 2);
    G.add_edge(2, 5, 3);
    G.add_edge(2, 7, 1);
    G.add_edge(3, 4, 7);
    G.add_edge(3, 5, 7);
    G.add_edge(4, 1, 2);
    G.add_edge(4, 6, 6);
    G.add_edge(5, 4, 2);
    G.add_edge(5, 6, 1);
    G.add_edge(7, 5, 1);
    
    
    std::cout << "G has " << G.vertex_count() << " vertices" << std::endl;
    std::cout << "G has " << G.edge_count() << " edges" << std::endl;

    std::cout << "Contains Edge? " << G.contains_edge(1, 2) << std::endl;
    std::cout << "Contains Edge? " << G.contains_edge(3, 1) << std::endl;

    std::cout << std::endl;

    std::cout << "compute mst path from 2" << std::endl;
    G.prim(2);

    std::cout << "print minimum spanning paths" << std::endl;
    for (size_t n = 1; n <= 7; n++)
    {
        std::cout << "minimum spanning path from 2 to " << n << std::endl;
        std::cout << "  ";
        G.print_path(n);
    }
    std::cout << std::endl;

    std::cout << "compute shortest path from 2" << std::endl;
    G.dijkstra(2);

    std::cout << "print shortest paths" << std::endl;
    for (size_t n = 1; n <= 7; n++)
    {
        std::cout << "shortest path from 2 to " << n << std::endl;
        std::cout << "  ";
        G.print_shortest_path(n);
    }

    // futher tests
    G.print_tree();
    G.remove_vertex(1);
    std::cout << "Contains Edge? " << G.contains_edge(1, 2) << std::endl;
    G.remove_vertex(6);
    G.print_tree();

    // copy constructor
    Graph G2(G);
    G2.add_vertex(1);
    G.print_tree();

    G2.print_tree();
    std::cout << "Contains 1? " << G2.contains_vertex(1);
    std::cout << "Contains 2? " << G2.contains_vertex(2);
    std::cout << "Contains 6? " << G2.contains_vertex(6) << std::endl;
    G.print_tree();
    G.remove_vertex(2);
    Graph G3 = G2;
    G3.print_tree();

    // assignment operator
    Graph G4 = G3;
    std::cout << "Contains Really high number? " << G4.contains_vertex(112349712347) << std::endl;
    G4.add_vertex(55);
    G4.contains_vertex(12);
    G4.dijkstra(3);
    G4.print_path(3); // does not exist

    std::cout << "Contains Vertex 1002? " << G.contains_vertex(1002) << std::endl;
    std::cout << "Contains Vertex in G4 3? " << G.contains_vertex(3) << std::endl;

    G4 = G;
    G.print_tree();
    G4.print_tree();

    // printing  and testing costs/edges
    std::cout << "Contains edge 2 to 3 (should be 1)? " << G4.contains_edge(2, 3) << endl;
    std::cout << "Cost edge 2 to 3 " << G4.cost(2, 3) << endl;

    std::cout << "Contains edge 100 to 3 (should be 0)? " << G4.contains_edge(100, 3) << endl;
    std::cout << "Cost edge 100 to 3: " << G4.cost(2, 3) << endl;

    std::cout << "Contains edge 2 to 100 (should be 0)? " << G4.contains_edge(2, 100) << endl;
    std::cout << "Cost edge 2 to 100: " << G4.cost(2, 100) << endl;

    std::cout << "Contains edge 3000 to 100 (should be 0)? " << G4.contains_edge(3000, 100) << endl;
    std::cout << "Cost edge 3000 to 100: " << G4.cost(3000, 100) << endl;

    std::cout << "Contains edge 3 to 4 (should be 1)? " << G4.contains_edge(3, 4) << endl;
    std::cout << "Cost edge 3 to 4: " << G4.cost(3, 4) << endl;

    std::cout << "Contains edge 3 to 7 (should be 1)? " << G4.contains_edge(3, 7) << endl;
    std::cout << "Cost edge 3 to 7: " << G4.cost(3, 7) << endl;

    // testing auxiliary functions of prim and dijkstra before doing it
    Graph Gnew;
    for (size_t n = 1; n <= 7; n++)
    {
        std::cout << "Count: " << G.vertex_count() << std::endl;
        Gnew.add_vertex(n);
    }

    Gnew.print_tree();
    Gnew.print_path(3);
    Gnew.print_shortest_path(3);
    std::cout << "is path at 3? " << Gnew.is_path(3) << std::endl;
    std::cout << "distance at 3? " << Gnew.distance(3) << std::endl;

    // dijkstra and prim on an edgeless graph
    Gnew.prim(3);
    Gnew.print_path(1);
    Gnew.print_path(3);

    Gnew.dijkstra(3);
    Gnew.print_shortest_path(1);
    Gnew.print_shortest_path(3);
    // adding edge with nonexistent vertices
    std::cout << "Adding edge 100 to 134: " << Gnew.add_edge(100, 134, 12.0) << std::endl;
    std::cout << "Adding edge 1 to 134: " << Gnew.add_edge(1, 134, 12.0) << std::endl;
    std::cout << "Adding edge 1 to 3: " << Gnew.add_edge(1, 3, 12.0) << std::endl;
    std::cout << "Adding edge 1 to 3 again: " << Gnew.add_edge(1, 3, 14.7) << std::endl;

    // prim and dijkstra where all nodes are not connected

    Gnew.prim(1);
    Gnew.print_path(1);
    Gnew.print_path(3);

    Gnew.print_path(6); // no path

    Gnew.dijkstra(1);
    Gnew.print_shortest_path(1);
    Gnew.print_shortest_path(3);

    Gnew.print_shortest_path(6); // path

    std::cout << "Removing edge 90 to 15: " << Gnew.remove_edge(90, 15) << std::endl; // does not exist 
    std::cout << "Removing edge 1 to 15: " << Gnew.remove_edge(1, 15) << std::endl; // does not exist 
    std::cout << "Removing edge 1 to 3: " << Gnew.remove_edge(1, 3) << std::endl;
    std::cout << "Removing edge 100 to 3: " << Gnew.remove_edge(100, 3) << std::endl; // does not exist
    
    // prim and dijkstra after removing the only edge -- only path should be just 1 to itself
    Gnew.prim(1);
    Gnew.print_path(1);
    Gnew.print_path(3);

    Gnew.print_path(6); // no path

    Gnew.dijkstra(1);
    Gnew.print_shortest_path(1);
    Gnew.print_shortest_path(3);

    Gnew.print_shortest_path(6); // path

    return 0;
}
