#include <boost/graph/use_mpi.hpp>
#include <boost/graph/distributed/mpi_process_group.hpp>
#include <boost/graph/distributed/adjacency_list.hpp>
#include <boost/graph/erdos_renyi_generator.hpp>
#include <boost/random/linear_congruential.hpp>

using boost::graph::distributed::mpi_process_group;

struct TNode {
	TNode(){}
	TNode(const std::string& name) : name(name) {}

	std::string name;

	// Serialization support is required!
	template<typename Archiver>
	void serialize(Archiver& ar, const unsigned int /*version*/) {
		ar & name;
	}
};


namespace boost { namespace graph {

template<>
struct internal_vertex_name<TNode>
{
  typedef multi_index::member<TNode, std::string, &TNode::name> type;
};

template<>
struct internal_vertex_constructor<TNode>
{
  typedef vertex_from_name<TNode> type;
};

} }

typedef boost::adjacency_list<boost::vecS, boost::distributedS<
		mpi_process_group, boost::vecS>, 
		boost::directedS,  TNode,
		boost::property<boost::edge_weight_t, int> > Graph;

int main(int argc, char* argv[]) {

  boost::mpi::environment env(argc, argv);

  typedef boost::sorted_erdos_renyi_iterator<boost::minstd_rand, Graph> ERIter;
  boost::minstd_rand gen;
  unsigned long n = 1000000; // 1M vertices
  Graph g(ERIter(gen, n, 0.00005), ERIter(), n);
  
  return 0;

}
