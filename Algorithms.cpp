#include "Algorithms.h"
#include <algorithm>
#include <iostream>


const static int INF = 100000;

namespace GIS
{


	Algorithm::Algorithm(const Graph &g) : graph(g), originalGraph(g), backupGraph(g), labels(graph.getSize(), std::make_pair(INF, false))
	{
		


	}

	Algorithm::~Algorithm()
	{
		graph.clear();
		labels.clear();
	}

	bool Algorithm::allChecked() const
	{
		for (auto x : labels)
			if (x.second == false)
				return false;

		return true;
	}

	int Algorithm::getMinimal() const
	{
		int min = INF;
		int node = -1;
		for (unsigned int i = 0; i < labels.size(); i++)
			if (labels[i].second == false)
			{
				if (min > labels[i].first)
				{
					min = labels[i].first;
					node = i;
				}
			}

		return node;
	}

	int Algorithm::markNextLabels(int node)
	{
		for (auto x : graph.getNode(node).connectionsTo)
		{
			if (labels[x.first].second != true)
			{
				labels[x.first].first = std::min(labels[x.first].first, labels[node].first + x.second.weight);

				//if (labels[x.first].first < min)
				//	min = x.first;
			}
		}

		int min = getMinimal();
		if (min != -1)
			labels[min].second = true;

		return min;

	}

	int Algorithm::markNextLabels2(int node)
	{
		for (auto x : graph.getNode(node).connectionsTo)
		{
			labels[x.first].first = std::min(labels[x.first].first, labels[node].first + x.second.weight);
		}

		int min = getMinimal();
		if (min != -1)
			labels[min].second = true;

		return min;

	}

	void Algorithm::Dijkstra(int firstNode)
	{
		clearLabels();
		for (unsigned int i = 0; i < labels.size(); i++)
		{
			if (i == firstNode)
			{
				labels[i].first = 0;
				labels[i].second = true;
			}

		}

		int nextNode = firstNode;

		do
		{
			nextNode = markNextLabels(nextNode);

		} while (nextNode != -1);

		//std::cout << "DIJKSTRA TABLE: ";
		//for (auto x : labels)
		//	std::cout << x.first << " ";
		//std::cout << std::endl;
	}

	void Algorithm::DijkstraModified(int firstNode)
	{
		// przygotowanie tablicy etykiet
		clearLabels();
		for (unsigned int i = 0; i < labels.size(); i++)
		{
			if (i == firstNode)
			{
				labels[i].first = 0;
				labels[i].second = true;
			}

		}

		int nextNode = firstNode;

		do
		{
			nextNode = markNextLabels2(nextNode);

		} while (nextNode != -1);

		//std::cout << "DIJKSTRA TABLE: ";
		//for (auto x : labels)
		//	std::cout << x.first << " ";
		//std::cout << std::endl;
	}


	std::deque<int> Algorithm::GetRoute(int firstNode, int secondNode, std::deque<int> &weights)
	{
		std::deque<int> route;

		// dodajemy wierzcho³ek koñcowy
		route.push_front(secondNode);
		int node = secondNode;
		int lastNode = node;
		while (node != firstNode)
		{
			for (auto x : graph.find(node)->second.connectionsIn)
			{
				if (x.second.weight + labels[x.second.connectedNodeId].first == labels[node].first)
				{
					node = x.second.connectedNodeId;
					weights.push_front(x.second.weight);
					route.push_front(node);
					//lastNode = node;
					break;
				}

			}

			if (node == lastNode)
			{
				std::cout << "BRAK NAJKROTSZEJ SCIEZKI W GRAFIE!" << std::endl;
				std::deque<int> deq (0);
				return deq;
			}
			else
				lastNode = node;

		}

		std::cout << "SCIEZKA: ";
		for (auto x : route)
			std::cout << x << " ";
		std::cout << std::endl;

		return route;
	}

	void Algorithm::SPNPGreedy(int firstNode, int lastNode)
	{
		graph = originalGraph;
		std::deque<int> weights1;
		std::deque<int> weights2;

		// krok 1 - Dijkstra
		Dijkstra(firstNode);
		std::deque<int> path = GetRoute(firstNode, lastNode, weights1);

		if (weights1.size() == 0)
			return;

		// krok 2 - usuniêcie œcie¿ki
		for (unsigned int i = 0; i < path.size() - 1; i++)
			graph.deleteConnection(path[i], path[i + 1], weights1[i]);
			

		// krok 3 - kolejny Dijkstra
		Dijkstra(firstNode);
		std::deque<int> secondPath = GetRoute(firstNode, lastNode, weights2);
		int w1 = getPathWeight(weights1);
		int w2 = getPathWeight(weights2);



		std::cout << std::endl << "PIERWSZA SCIEZKA ("<< w1<<"): ";
		for (auto x : path)
			std::cout << x << " ";
		std::cout << std::endl;
		std::cout << "DRUGA SCIEZKA (" << w2<< "): ";
		for (auto x : secondPath)
			std::cout << x << " ";
		std::cout << std::endl;

	}

	int Algorithm::getPathWeight(const std::deque<int> &weights)
	{
		int w = 0;
		for (auto x : weights)
			w += x;

		return w;
	}

	void Algorithm::changeDirection(int firstNode, int secondNode, int weight)
	{
		tempGraph.deleteConnection(firstNode, secondNode, weight);
		tempGraph.addConnection(firstNode, secondNode, -weight, false);
		tempGraph.addConnection(secondNode, firstNode, -weight, true);
	}

	void Algorithm::SPNPMain(int firstNode, int lastNode)
	{
		std::deque<int> weights1;
		std::deque<int> weights2;

		// krok 1 - zmodyfikowany Dijkstra
		DijkstraModified(firstNode);
		// wyznaczenie najkrótszej œcie¿ki
		std::deque<int> path = GetRoute(firstNode, lastNode, weights1);

		if (path.size() == 0)
			return;

		// krok 2 - zmiana po³¹czeñ na przeciwne
		tempGraph = graph;
		for (unsigned int i = 0; i < path.size() - 1; i++)
		{
			changeDirection(path[i], path[i + 1], weights1[i]);
		}

		// krok 3 - stworzenie podwêz³ów
		unsigned int newNodesCount;
		for (newNodesCount = 0; newNodesCount < path.size() - 2; newNodesCount++)
		{
			int weight = tempGraph.deleteConnection(path[newNodesCount + 1], path[newNodesCount], -weights1[newNodesCount]);
			int newNodeNo = tempGraph.getSize();
			tempGraph.addNode(newNodeNo);

			
			tempGraph.addConnection(newNodeNo, path[newNodesCount], weight, true);
			tempGraph.addConnection(path[newNodesCount], newNodeNo, weight, false);

			tempGraph.addConnection(path[newNodesCount + 1], newNodeNo, 0, true);
			tempGraph.addConnection(newNodeNo, path[newNodesCount + 1], 0, false);
		}	
		newNodesCount++;

		// krok 3.5 - storzenie dodatkowych ³uków
		for (unsigned int i = 1; i < path.size() - 1; i++)
		{
			int nodeNo = tempGraph.getSize() - newNodesCount + i;

			auto it = graph.find(path[i]);

			

			for (auto x : it->second.connectionsIn)
			{
				bool founded = false;

				for (auto y : path)
					if (x.second.connectedNodeId == y)
					{ 
						founded = true;
						break;
					}

				if (!founded)
				{
					//changeDirection(path[i], x.second.connectedNodeId);
					//tempGraph.addConnection(x.second.connectedNodeId, nodeNo, x.second.weight, true);
					//tempGraph.addConnection(nodeNo, x.second.connectedNodeId, x.second.weight, false);
					tempGraph.addConnection(x.second.connectedNodeId, nodeNo, x.second.weight, false);
					tempGraph.addConnection(nodeNo, x.second.connectedNodeId, x.second.weight, true);
				}
			}

		}

		// krok 4 - zmodyfikowany Dijkstra po raz 2
		graph = tempGraph;
		DijkstraModified(firstNode);
		std::deque<int> secondPath = GetRoute(firstNode, lastNode, weights2);


		// krok 5 - sprawdzenie czy œcie¿ki siê nie nachodz¹
		if(CheckDisjoint(path, secondPath, weights1, weights2))
			SPNPMain(firstNode, lastNode);
		
	}

	void Algorithm::clearLabels()
	{
		labels.clear();

		int i = 0;
		while (i < graph.getSize())
		{
			labels.push_back(std::make_pair(INF, false));
			i++;
		}
	}

	bool Algorithm::CheckDisjoint(std::deque<int> &path, std::deque<int> &secondPath, const std::deque<int> &weights1, const std::deque<int> &weights2)
	{

		if (path.size() != 0 && secondPath.size() != 0)
		{ 

			for (unsigned int i = 0; i< secondPath.size(); i++)
				if (secondPath[i] >= originalGraph.getSize())
					secondPath.erase(secondPath.begin() + i);

		

			for (unsigned int i = 0; i < secondPath.size()-1; i++)
				for (unsigned int j = 0; j < path.size() - 1; j++)
					if ((j + 1)<secondPath.size() && (i + 1) < path.size())
						if (secondPath[j] == path[i + 1] && secondPath[j + 1] == path[i])
						{
							// szukanie innej drogi
							//if ()
								std::cout << "Nachodzace na siebie sciezki!" << std::endl;

								backupGraph.deleteConnection(path[i], path[i + 1], weights1[i]);
								graph = backupGraph;
								//graph.deleteConnection(path[i], path[i + 1]);


								return true;
					
					
							//return true;
						}
		}

		int w1 = getPathWeight(weights1);
		int w2 = getPathWeight(weights2);


		std::cout << std::endl << "PIERWSZA SCIEZKA (" << w1 << "): ";
		for (auto x : path)
			std::cout << x << " ";
		std::cout << std::endl;
		std::cout << "DRUGA SCIEZKA (" << w2 << "): ";
		for (auto x : secondPath)
			std::cout << x << " ";
		std::cout << std::endl;

		return false;
	}

	void Algorithm::clearAll()
	{
		graph = originalGraph;
		backupGraph = originalGraph;
		clearLabels();
	}
};