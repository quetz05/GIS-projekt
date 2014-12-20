#include <iostream>
#include "Algorithms.h"




int main()
{
	GIS::Graph graph("graph1.txt");
	GIS::Dijkstra(graph, 0, 1000);


	






	std::cin.get();
	return 0;
}