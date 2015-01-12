#include <iostream>
#include "Algorithms.h"
#include <chrono>

int main()
{


	GIS::Graph graph("graph0.txt");
	//graph.print();
	GIS::Algorithm algorithm(graph);

	std::cout << "-------------------ALGORYTM ZACHLANNY-------------------\n\n";

	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
	
	algorithm.SPNPGreedy(graph.firstNode, graph.lastNode);

	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();


	std::cout << std::endl << std::endl << "Czas wykonywania: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;

	algorithm.clearAll();

	std::cout << "\n\n----------------------NASZ ALGORYTM----------------------\n\n";

	start = std::chrono::high_resolution_clock::now();

	algorithm.SPNPMain(graph.firstNode, graph.lastNode);

	end = std::chrono::high_resolution_clock::now();

	std::cout << std::endl << std::endl << "Czas wykonywania: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;

	std::cout << std::endl << std::endl << "Koniec dzialania programu. Wcisnij dowolny klawisz..." << std::endl;

	std::cin.get();
	return 0;
}