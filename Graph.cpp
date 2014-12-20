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
		}
	}

	Graph::~Graph()
	{


	}


	const Node& Graph::getNode(int nodeId) const
	{
		return find(nodeId)->second;
	}


	int Graph::getSize() const
	{
		return size();
	}


	void Graph::addPath(int nodeId, int connectedNodeId, int weight)
	{
		auto it = find(nodeId);
		if (it == end())
			it = addNode(nodeId);

		it->second.connections.insert(std::make_pair(connectedNodeId, Path(connectedNodeId,weight)));
	}


	void Graph::addConnection(int nodeId, const Path& path)
	{
		auto it = find(nodeId);
		if (it == end())
			it = addNode(nodeId);

		it->second.connections.insert(std::make_pair(path.connectedNodeId, path));

	}

	Graph::iterator Graph::addNode(const Node& newNode)
	{
		return insert(std::make_pair(newNode.id, newNode)).first;
	}


	Graph::iterator Graph::addNode(int id)
	{
		return insert(std::make_pair(id, Node(id))).first;
	}







}
