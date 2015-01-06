#include "Algorithms.h"
#include <algorithm>
#include <iostream>


const static int INF = 100000;

namespace GIS
{


	Algorithm::Algorithm(const Graph &g) : graph(g), originalGraph(g), labels(graph.getSize(), std::make_pair(INF, false))
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

		for (auto x : labels)
			std::cout << x.first << " ";
		std::cout << std::endl;
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

		for (auto x : labels)
			std::cout << x.first << " ";
		std::cout << std::endl;
	}


	std::deque<int> Algorithm::GetRoute(int firstNode, int secondNode)
	{
		std::deque<int> route;

		// dodajemy wierzcho³ek koñcowy
		route.push_front(secondNode);
		int node = secondNode;

		while (node != firstNode)
		{
			for (auto x : graph.find(node)->second.connectionsIn)
			{
				if (x.second.weight + labels[x.second.connectedNodeId].first == labels[node].first)
				{
					node = x.second.connectedNodeId;
					route.push_front(node);
					break;
				}
			}
		}

		for (auto x : route)
			std::cout << x << " ";
		std::cout << std::endl;

		return route;
	}

	void Algorithm::SPNPGreedy(int firstNode, int lastNode)
	{





	}


	void Algorithm::changeDirection(int firstNode, int secondNode)
	{
		int weight = tempGraph.deleteConnection(firstNode, secondNode);
		tempGraph.addConnection(firstNode, secondNode, -weight, false);
		tempGraph.addConnection(secondNode, firstNode, -weight, true);
	}

	void Algorithm::SPNPMain(int firstNode, int lastNode)
	{
		// krok 1 - zmodyfikowany Dijkstra
		DijkstraModified(firstNode);
		// wyznaczenie najkrótszej œcie¿ki
		std::deque<int> path = GetRoute(firstNode, lastNode);

		// krok 2 - zmiana po³¹czeñ na przeciwne
		tempGraph = graph;
		tempGraph.print();
		for (unsigned int i = 0; i < path.size() - 1; i++)
		{
			changeDirection(path[i], path[i + 1]);
		}

		// krok 3 - stworzenie podwêz³ów
		unsigned int newNodesCount;
		for (newNodesCount = 0; newNodesCount < path.size() - 2; newNodesCount++)
		{
			int weight = tempGraph.deleteConnection(path[newNodesCount + 1], path[newNodesCount]);
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
					changeDirection(path[i], x.second.connectedNodeId);
					tempGraph.addConnection(x.second.connectedNodeId, nodeNo, x.second.weight, true);
					tempGraph.addConnection(nodeNo, x.second.connectedNodeId, x.second.weight, false);
				}
			}

		}

		// krok 4 - zmodyfikowany Dijkstra po raz 2
		graph = tempGraph;
		DijkstraModified(firstNode);
		std::deque<int> secondPath = GetRoute(firstNode, lastNode);


		// krok 5 - usuniêcie dodatkowych node'ów
		std::cout << std::endl << "KOONIEC!" << std::endl;
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
};