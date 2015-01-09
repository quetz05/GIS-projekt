#pragma once
#include "Graph.h"
#include <vector>
#include <deque>

namespace GIS
{
	class Algorithm{
	public:
		Algorithm(const Graph &g);
		~Algorithm();


		void Dijkstra(int firstNode);
		void DijkstraModified(int firstNode);
		void SPNPGreedy(int firstNode, int lastNode);
		void SPNPMain(int firstNode, int lastNode);

		std::deque<int> GetRoute(int firstNode, int secondNode);

		const Graph originalGraph;

	private:
		bool CheckDisjoint(std::deque<int> &path, std::deque<int> &secondPath);
		void changeDirection(int firstNode, int secondNode);
		bool allChecked() const;
		int getMinimal() const;
		int markNextLabels(int node);
		int markNextLabels2(int node);
		void clearLabels();

		Graph backupGraph;
		Graph graph;	
		Graph tempGraph;
		std::vector<std::pair<int, bool>> labels;
	};



};