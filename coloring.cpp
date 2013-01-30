#include <boost/graph/use_mpi.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/graph/distributed/mpi_process_group.hpp>
#include <boost/graph/distributed/adjacency_list.hpp>
#include <vector>
#include <boost/graph/parallel/distribution.hpp>
#include <boost/config.hpp>
#include <iostream>
#include <boost/graph/distributed/boman_et_al_graph_coloring.hpp>
#include <mpi.h>
 
using namespace boost;
 
struct Vertex {
    Vertex() {}
    Vertex(const std::string& name) : name(name) {}
    std::string name;
    template<typename Archiver>
    void serialize(Archiver &ar, const unsigned int) {
        ar & name;
    }
};
 
// Enable named vertex support
namespace boost
{
    namespace graph
    {
        template<>
        struct internal_vertex_name<Vertex> {
            typedef multi_index::member<Vertex, std::string, &Vertex::name> type;
        };
        template<>
        struct internal_vertex_constructor<Vertex> {
            typedef vertex_from_name<Vertex> type;
        };
    }
}


typedef adjacency_list <vecS, distributedS<boost::graph::distributed::mpi_process_group, vecS>, undirectedS, Vertex> Graph;
typedef property_map<Graph, std::string Vertex::*>::type VertexNameMap;
typedef property_map<Graph, vertex_index_t>::const_type IndexMap;

typedef graph_traits<Graph>::vertex_descriptor vertex_descriptor;
typedef graph_traits<Graph>::vertices_size_type vertices_size_type;
typedef property_map<Graph, vertex_index_t>::const_type vertex_index_map;

//typedef Graph::vertex_descriptor Vertex;
//typedef Graph::edge_descriptor Edge;

int main (int argc, char *argv[])
{
    
    mpi::environment env(argc, argv);
    mpi::communicator world;
    Graph g;
    int i =0;
    //if (world.rank() == 0) {
      add_edge("1","2",g);
      add_edge("2","3",g);
      add_edge("3","1",g);
      
      add_edge("1","4",g);
      add_edge("2","4",g);
      add_edge("3","4",g);
    
      add_edge("5","1",g);
      add_edge("6","1",g);
      add_edge("7","1",g);
      
    //}
    std::vector<vertices_size_type> color_vec(num_vertices(g));
    iterator_property_map<vertices_size_type*, vertex_index_map>
    color(&color_vec.front(), get(vertex_index, g));
    
    i = boman_et_al_graph_coloring(g, color);

    if(world.rank() != 0)
    {
        MPI_Send(&value, 1, MPI_INT, 0, world.rank, MPI_COMM_WORLD);
    }
    else
    {
        MPI_RECV(&value,1,

int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag,
             MPI_Comm comm, MPI_Status *status)

        MPI_RECV
    }
    std::cout << i;
    std::cout << color_vec[0] << " " << color_vec[1] << " " << color_vec[2] << " " << color_vec[3] << " " << color_vec[4] << " " <<std::endl;
    
    /*mpi::environment env(argc, argv);
    mpi::communicator world;
    //synchronize(g.process_group());
    std::vector<vertices_size_type> color_vec(num_vertices(g));
    iterator_property_map<vertices_size_type*, vertex_index_map>
    color(&color_vec.front(), get(vertex_index, g));
    //vertex_index_map vm;
    //boost::property_map< Graph2, Vertex > apm(color_vec);
    
    //VertexNameMap vnm(&color_vec);
    
    i = boman_et_al_graph_coloring(g, color);
    std::cout <<i;
    std::cout << color_vec[0] << color_vec[1] << color_vec[2] <<std::endl;
    //std::vector<int> centralityS(num_vertices(g), 0);
    //CentralityMap centrality(centralityS.begin(), get(vertex_index, g));
    //brandes_betweenness_centrality(g, centrality);*/
    return 0;
}
