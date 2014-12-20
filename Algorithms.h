#pragma once
#include "Graph.h"

namespace GIS
{

	 void Dijkstra(const Graph &graph, int firstNode, int lastNode);
	 void DijkstraModified(const Graph &graph, int firstNode, int lastNode);
	 void SPNP(const Graph &graph, int firstNode, int lastNode);

};