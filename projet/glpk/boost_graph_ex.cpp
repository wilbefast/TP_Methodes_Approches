//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#include <boost/config.hpp>
#include <iostream>                      // for std::cout
#include <fstream>                       // for ofstream
#include <utility>                       // for std::pair
#include <algorithm>                     // for std::for_each
#include <boost/utility.hpp>             // for boost::tie
#include <boost/graph/graph_traits.hpp>  // for boost::graph_traits
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

using namespace boost;

template <class Graph> struct exercise_vertex
{
  exercise_vertex(Graph& g_) : g(g_) { }
  typedef typename graph_traits<Graph>::vertex_descriptor Vertex;
  void operator()(const Vertex& v) const
  {
  }
  Graph& g;
};


int boost_graph_ex()
{
  // create a typedef for the Graph type
  typedef adjacency_list<vecS, vecS, bidirectionalS,
     no_property, property<edge_weight_t, float> > Graph;

  // Make convenient labels for the vertices
  enum { A, B, C, D, E, N };
  const int num_vertices = N;
  const char* name = "ABCDE";

  // writing out the edges in the graph
  typedef std::pair<int,int> Edge;
  Edge edge_array[] =
  {
    Edge(A,B), Edge(A,D), Edge(C,A), Edge(D,C),
    Edge(C,E), Edge(B,D), Edge(D,E),
  };
  const int num_edges = sizeof(edge_array)/sizeof(edge_array[0]);

  // average transmission delay (in milliseconds) for each connection
  float transmission_delay[] = { 1.2, 4.5, 2.6, 0.4, 5.2, 1.8, 3.3, 9.1 };

  // declare a graph object, adding the edges and edge properties
  Graph g(edge_array, edge_array + num_edges,
          transmission_delay, num_vertices);

  boost::property_map<Graph, vertex_index_t>::type
    vertex_id = get(vertex_index, g);
  boost::property_map<Graph, edge_weight_t>::type
    trans_delay = get(edge_weight, g);

  std::for_each(vertices(g).first, vertices(g).second,
                exercise_vertex<Graph>(g));

  std::map<std::string,std::string> graph_attr, vertex_attr, edge_attr;
  graph_attr["size"] = "3,3";
  graph_attr["rankdir"] = "LR";
  graph_attr["ratio"] = "fill";
  vertex_attr["shape"] = "circle";


  std::ofstream outfile("out.dot");
  boost::write_graphviz(outfile, g,
                      make_label_writer(name),
                      make_label_writer(trans_delay),
                      make_graph_attributes_writer(graph_attr, vertex_attr,
                                                   edge_attr));
  outfile.close();
  system ("dot -Tps out.dot -o out.ps");
  remove("out.dot");


  return EXIT_SUCCESS;
}
