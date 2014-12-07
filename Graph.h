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
		std::map<int, Path> connections;

		///
		/// \brief Konstruktor wêz³a o podanym id
		/// \param nodeId id wêz³a
		/// \return zwraca true lub false w zale¿noœci czy dany wêze³ jest po³¹czony z drugim
		///
		bool hasConnection(int nodeId) const;
	};

	///
	/// \brief Klasa grafu skierowanego, gdzie miêdzy tymi samymi wêz³ami mo¿e byæ maksymalnie jedno po³¹czenie (w jednym kierunku)
	///
	class Graph : private std::map<int ,Node>
	{
	public:
		///
		/// \brief Konstruktor bezargumentowy
		///
		Graph();

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
		///
		void addPath(int nodeId, int connectedNodeId, int weight);

		///
		/// \brief Funkcja dodaj¹ca po³¹czenie
		/// \param noteId id wêz³a pocz¹tkowego
		/// \param path nowa œcie¿ka
		///
		void addConnection(int nodeId, const Path& path);

		///
		/// \brief Funkcja dodaj¹ca wêze³
		/// \param newNode nowy wêze³
		///
		void hasNode(const Node& newNode);

		///
		/// \brief Funkcja dodaj¹ca wêze³ z kolejnym numerem id
		///
		void addNode();

		///
		/// \brief Funkcja dodaj¹ca wêze³
		/// \param newNode nowy wêze³
		///
		void addNode(const Node& newNode);

		///
		/// \brief Funkcja dodaj¹ca wêze³
		/// \param id id nowego wêz³a
		///
		void addNode(int id);
	};


}