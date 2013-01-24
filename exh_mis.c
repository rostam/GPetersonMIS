#include <igraph.h>

int main(void)
{
     igraph_integer_t diameter;
     igraph_t graph;
     igraph_integer_t v; 
     igraph_vector_t edges;
     igraph_vector_init(&edges,100);
     int i,j;

     int n=30,k=14;
     for(i=0;i<n;i++)
     {
         igraph_vector_push_back(&edges, i);
	 igraph_vector_push_back(&edges, (i+1)%n);
 
	 igraph_vector_push_back(&edges, i);
	 igraph_vector_push_back(&edges, i+n);

	 igraph_vector_push_back(&edges, n+i);
	 igraph_vector_push_back(&edges, n+(i+k)%n);
     }

     
     igraph_create(&graph, &edges, 0, 0);
     
     //igraph_vector_ptr_init(&v, 100);
     //igraph_erdos_renyi_game(&graph, IGRAPH_ERDOS_RENYI_GNP, 100, 5.0/1000,
     //                        IGRAPH_UNDIRECTED, IGRAPH_NO_LOOPS);
     //igraph_diameter(&graph, &diameter, 0, 0, 0, IGRAPH_UNDIRECTED, 1);
     //maximal.independent.vertex.sets(graph)
     igraph_independence_number(&graph, &v);
     
     printf("MIS of a random graph with average degree 5: %i\n",
             v);
     igraph_destroy(&graph);
     return 0;
}
