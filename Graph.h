#pragma once
#include <string>
#include <map>

namespace GIS
{
	///
	/// \brief Klasa œcie¿ki grafu
	///
	struct Path 
	{
		Path(int connNodeId, int pathWeight);
		int connectedNodeId;
		int weight;

	};

	///
	/// \brief Klasa wêz³a grafu posiadaj¹ca id wêz³a oraz mapê po³¹czeñ tego wêz³a z innymi
	///
	struct Node
	{
		///
		/// \brief Konstruktor wêz³a o podanym id
		/// \param id id wêz³a
		///
		Node(int id);

		int id;
		std::multimap<int, Path> connectionsTo;
		std::multimap<int, Path> connectionsIn;

		///
		/// \brief Konstruktor wêz³a o podanym id
		/// \param nodeId id wêz³a
		/// \return zwraca true lub false w zale¿noœci czy dany wêze³ jest po³¹czony z drugim
		///
		bool hasConnection(int nodeId) const;

		///
		/// \brief Funkcja usuwaj¹ca dane po³¹czenie wêz³a
		/// \param node id wêz³a
		/// \param out okreœla czy ma to byæ po³¹czenie wchodz¹ce czy wychodz¹ce z wêz³a
		/// \return zwraca wagê usuniêtego po³¹czenia
		///
		int deleteConnection(int node, bool out);
	};

	///
	/// \brief Klasa grafu skierowanego, gdzie miêdzy tymi samymi wêz³ami mo¿e byæ maksymalnie jedno po³¹czenie (w jednym kierunku)
	///
	class Graph : public std::map<int, Node>
	{
	public:
		///
		/// \brief Konstruktor bezargumentowy
		///
		Graph();

		///
		/// \brief Konstruktor kopiuj¹cy
		///
		Graph(const Graph& graph);

		///
		/// \brief Konstruktor tworz¹cy graf o danej iloœci wêz³ów (bez po³¹czeñ)
		/// \param nodeAmount iloœæ wêz³ów
		///
		Graph(int nodeAmount);

		///
		/// \brief Konstruktor grafu wczytuj¹cy dane o wêz³ach i po³¹czeniach z pliku
		/// \param fileName œcie¿ka do pliku
		///
		Graph(std::string fileName);

		///
		/// \brief Destruktor
		///
		~Graph();

		///
		/// \brief Operator przypisania
		///
		Graph & operator =(const Graph &graph);

		///
		/// \brief Funkcja zwracaj¹ca wêze³
		/// \param nodeId id wêz³a
		/// \return wêze³ o danym id
		///
		const Node& getNode(int nodeId) const;
		
		///
		/// \brief Funkcja zwracaj¹ca iloœæ wêz³ów
		/// \return iloœæ wêz³ów
		///
		int getSize() const;
		
		///
		/// \brief Funkcja dodaj¹ca po³¹czenie
		/// \param noteId id wêz³a pocz¹tkowego
		/// \param connectedNodeId id wêz³a koñcowego
		/// \param weight waga œcie¿ki
		///	\param nodeOut okreœla czy jest to krawêdŸ skierowana do czy od wêz³a
		///
		void addConnection(int nodeId, int connectedNodeId, int weight, bool nodeOut);

		///
		/// \brief Funkcja dodaj¹ca po³¹czenie
		/// \param noteId id wêz³a pocz¹tkowego
		/// \param path nowa œcie¿ka
		///	\param nodeOut okreœla czy jest to krawêdŸ skierowana do czy od wêz³a
		///
		void addConnection(int nodeId, const Path& path, bool nodeOut);

		///
		/// \brief Funkcja dodaj¹ca wêze³
		/// \param newNode nowy wêze³
		///
		void hasNode(const Node& newNode);


		///
		/// \brief Funkcja dodaj¹ca wêze³
		/// \param newNode nowy wêze³
		/// \return iterator dodanego wêz³a
		///
		Graph::iterator addNode(const Node& newNode);

		///
		/// \brief Funkcja dodaj¹ca wêze³
		/// \param id id nowego wêz³a
		/// \return iterator dodanego wêz³a
		///
		Graph::iterator addNode(int id);


		///
		/// \brief Funkcja usuwaj¹ca dane po³¹czenie w grafie
		/// \param nodeId1 id pierwszego wêz³a
		/// \param nodeId2 id drugiego wêz³a
		/// \return waga usuniêtego po³¹czenia
		///
		int deleteConnection(int nodeId1, int nodeId2);

		///
		/// \brief Funkcja drukuj¹ca na ekranie strukturê grafu
		///
		void print();
	};


}