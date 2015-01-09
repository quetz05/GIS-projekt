#include <iostream>
#include "Algorithms.h"




int main()
{
	GIS::Graph graph("graph2.txt");
	//graph.print();
	GIS::Algorithm algorithm(graph);

	algorithm.SPNPMain(0,5);


	




	std::cout << std::endl << std::endl << "Koniec dzialania programu. Wcisnij dowolny klawisz..." << std::endl;

	std::cin.get();
	return 0;
}