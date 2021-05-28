#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"
#include "graph.h"

int main(){

	Graph graph = createGraph();

	addGraphVertex(&graph);
	addGraphVertex(&graph);
	addGraphVertex(&graph);
	addGraphVertex(&graph);
	addGraphVertex(&graph);
	addGraphVertex(&graph);
	addGraphVertex(&graph);
	addGraphVertex(&graph);

	addEdge(graph.gVertexes[0], graph.gVertexes[1]);
	addEdge(graph.gVertexes[0], graph.gVertexes[4]);
	addEdge(graph.gVertexes[2], graph.gVertexes[1]);
	addEdge(graph.gVertexes[2], graph.gVertexes[3]);
	addEdge(graph.gVertexes[2], graph.gVertexes[6]);
	addEdge(graph.gVertexes[3], graph.gVertexes[7]);
	addEdge(graph.gVertexes[4], graph.gVertexes[5]);
	addEdge(graph.gVertexes[5], graph.gVertexes[1]);
	addEdge(graph.gVertexes[5], graph.gVertexes[2]);
	addEdge(graph.gVertexes[6], graph.gVertexes[5]);
	addEdge(graph.gVertexes[7], graph.gVertexes[2]);
	
	printf("%d\n",depthSearch(&graph, graph.gVertexes[0], graph.gVertexes[7]));

};
