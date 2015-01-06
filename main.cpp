#include <iostream>
#include "Algorithms.h"




int main()
{
	GIS::Graph graph("graph0.txt");
	//graph.print();
	GIS::Algorithm algorithm(graph);

	algorithm.SPNPMain(0,3);


	






	std::cin.get();
	return 0;
}