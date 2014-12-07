#include "Graph.h"
#include <fstream>
#include <iostream>

namespace GIS
{
	Path::Path(int connNodeId, int pathWeight) : connectedNodeId(connNodeId), weight(pathWeight)
	{
	}

	Node::Node(int id)
	{


	}

	bool Node::hasConnection(int nodeId) const
	{

		return false;
	}



	Graph::Graph()
	{


	}

	Graph::Graph(int nodeAmount)
	{


	}


	Graph::Graph(std::string fileName)
	{
		using namespace std;


		ifstream file;
		file.open(fileName);

		if (!file.good())
		{
			cout << "Error with file " << fileName << endl;
			return;
		}

		string line = "";
		while (getline(file, line))
		{
			size_t spacePos1 = line.find(" ");
			size_t spacePos2 = line.find(" ", spacePos1 +1);

			int nodeFirst = atoi(line.substr(0, spacePos1).c_str());
			int nodeSecond = atoi(line.substr(spacePos1, spacePos2).c_str());
			int pathWeight = atoi(line.substr(spacePos2).c_str());

			addConnection(nodeFirst, GIS::Path(nodeSecond, pathWeight));

			
			//cout << spacePos1 << " " << spacePos2 << " " << endl;
			//cout << nodeFirst << " " << nodeSecond << " " << pathWeight << " " << endl;
			//cout << "------------" << endl;

		}
	}

	Graph::~Graph()
	{


	}


	const Node& Graph::getNode(int nodeId) const
	{

		//return false;

		return this->at(0);
	}


	int Graph::getSize() const
	{

		//return false;
		return 0;

	}


	void Graph::addPath(int nodeId, int connectedNodeId, int weight)
	{


	}


	void Graph::addConnection(int nodeId, const Path& path)
	{
		//if ()

	}

	void Graph::addNode()
	{


	}

	void Graph::addNode(const Node& newNode)
	{


	}


	void Graph::addNode(int id)
	{


	}







}
