#include <boost/config.hpp>
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>

/**************

Branch and Bound

 **************/

size_t branchBound(int sommet, int borneInf, Graph g){

  //ACPM G − {x}
  remove_vertex(sommet, g);
  

  // relier x à ses deux voisins les plus proches en terme de coût

  //if valeur du cycle > borne inférieure then

  //if tous les sommets sont de degré 2 then

  //mettre à jour la solution courante

  //else

  //choisir un sommet y de degré ≥ 2

  //for chaque arête ei issue de y do

  //gbis := G − {ei }
  remove_edge(e, g);

  //BranchAndBound(y, borneInf, g )

  //retourner la plus petite des solutions acceptables



}


int main()
{
  using namespace boost;
  typedef adjacency_list < vecS, vecS, undirectedS,
    property<vertex_distance_t, int>, property < edge_weight_t, int > > Graph;
  typedef std::pair < int, int >E;
  const int num_nodes = 5;
  E edges[] = { E(0, 2), E(1, 3), E(1, 4), E(2, 1), E(2, 3),
    E(3, 4), E(4, 0)
  };
  int weights[] = { 1, 1, 2, 7, 3, 1, 1 };
#if defined(BOOST_MSVC) && BOOST_MSVC <= 1300
  Graph g(num_nodes);
  property_map<Graph, edge_weight_t>::type weightmap = get(edge_weight, g); 
  for (std::size_t j = 0; j < sizeof(edges) / sizeof(E); ++j) {
    graph_traits<Graph>::edge_descriptor e; bool inserted;
    boost::tie(e, inserted) = add_edge(edges[j].first, edges[j].second, g);
    weightmap[e] = weights[j];
  }
#else
  Graph g(edges, edges + sizeof(edges) / sizeof(E), weights, num_nodes);
  property_map<Graph, edge_weight_t>::type weightmap = get(edge_weight, g);
#endif
  std::vector < graph_traits < Graph >::vertex_descriptor >
    p(num_vertices(g));

#if defined(BOOST_MSVC) && BOOST_MSVC <= 1300
  property_map<Graph, vertex_distance_t>::type distance = get(vertex_distance, g);
  property_map<Graph, vertex_index_t>::type indexmap = get(vertex_index, g);
  prim_minimum_spanning_tree
    (g, *vertices(g).first, &p[0], distance, weightmap, indexmap, 
     default_dijkstra_visitor());
#else
  prim_minimum_spanning_tree(g, &p[0]);
#endif

  for (std::size_t i = 0; i != p.size(); ++i)
    if (p[i] != i)
      std::cout << "parent[" << i << "] = " << p[i] << std::endl;
    else
      std::cout << "parent[" << i << "] = no parent" << std::endl;

  return EXIT_SUCCESS;
}
