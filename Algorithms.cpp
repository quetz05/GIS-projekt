#include "Algorithms.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

const static int INF = 100000;

namespace GIS
{

	bool allChecked(const std::vector<std::pair<int, bool>> &labels)
	{
		for (auto x : labels)
			if (x.second == false)
				return false;

		return true;
	}

	int getMinimal(const std::vector<std::pair<int, bool>> &labels)
	{
		int min = INF;
		int node = -1;
		for (int i = 0; i < labels.size(); i++)
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

	int markNextLabels(const Graph &graph, std::vector<std::pair<int, bool>> &labels, int node)
	{
		for (auto x : graph.getNode(node).connections)
		{
			if (labels[x.first].second != true)
			{
				labels[x.first].first = std::min(labels[x.first].first, labels[node].first + x.second.weight);

				//if (labels[x.first].first < min)
				//	min = x.first;
			}
		}

		int min = getMinimal(labels);
		if (min != -1)
			labels[min].second = true;

		return min;
		
	}

	void Dijkstra(const Graph &graph, int firstNode, int lastNode)
	{
		// przygotowanie tablicy etykiet
		std::vector<std::pair<int, bool>> labels(graph.getSize(), std::make_pair(INF,false));

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
			nextNode = markNextLabels(graph, labels, nextNode);

		} while (nextNode != -1);

		for (auto x : labels)
			std::cout << x.first << " ";
		std::cout << std::endl;
	}

	void DijkstraModified(const Graph &graph, int firstNode, int lastNode)
	{



	}

	void SPNP(const Graph &graph, int firstNode, int lastNode)
	{




	}

};