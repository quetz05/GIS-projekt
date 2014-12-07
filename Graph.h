#pragma once
#include <string>
#include <map>

namespace GIS
{
	///
	/// \brief Klasa �cie�ki grafu
	///
	struct Path 
	{
		Path(int connNodeId, int pathWeight);
		int connectedNodeId;
		int weight;
	};

	///
	/// \brief Klasa w�z�a grafu posiadaj�ca id w�z�a oraz map� po��cze� tego w�z�a z innymi
	///
	struct Node
	{
		///
		/// \brief Konstruktor w�z�a o podanym id
		/// \param id id w�z�a
		///
		Node(int id);

		int id;
		std::map<int, Path> connections;

		///
		/// \brief Konstruktor w�z�a o podanym id
		/// \param nodeId id w�z�a
		/// \return zwraca true lub false w zale�no�ci czy dany w�ze� jest po��czony z drugim
		///
		bool hasConnection(int nodeId) const;
	};

	///
	/// \brief Klasa grafu skierowanego, gdzie mi�dzy tymi samymi w�z�ami mo�e by� maksymalnie jedno po��czenie (w jednym kierunku)
	///
	class Graph : private std::map<int ,Node>
	{
	public:
		///
		/// \brief Konstruktor bezargumentowy
		///
		Graph();

		///
		/// \brief Konstruktor tworz�cy graf o danej ilo�ci w�z��w (bez po��cze�)
		/// \param nodeAmount ilo�� w�z��w
		///
		Graph(int nodeAmount);

		///
		/// \brief Konstruktor grafu wczytuj�cy dane o w�z�ach i po��czeniach z pliku
		/// \param fileName �cie�ka do pliku
		///
		Graph(std::string fileName);
		///
		/// \brief Destruktor
		///
		~Graph();

		///
		/// \brief Funkcja zwracaj�ca w�ze�
		/// \param nodeId id w�z�a
		/// \return w�ze� o danym id
		///
		const Node& getNode(int nodeId) const;
		
		///
		/// \brief Funkcja zwracaj�ca ilo�� w�z��w
		/// \return ilo�� w�z��w
		///
		int getSize() const;
		
		///
		/// \brief Funkcja dodaj�ca po��czenie
		/// \param noteId id w�z�a pocz�tkowego
		/// \param connectedNodeId id w�z�a ko�cowego
		/// \param weight waga �cie�ki
		///
		void addPath(int nodeId, int connectedNodeId, int weight);

		///
		/// \brief Funkcja dodaj�ca po��czenie
		/// \param noteId id w�z�a pocz�tkowego
		/// \param path nowa �cie�ka
		///
		void addConnection(int nodeId, const Path& path);

		///
		/// \brief Funkcja dodaj�ca w�ze�
		/// \param newNode nowy w�ze�
		///
		void hasNode(const Node& newNode);

		///
		/// \brief Funkcja dodaj�ca w�ze� z kolejnym numerem id
		///
		void addNode();

		///
		/// \brief Funkcja dodaj�ca w�ze�
		/// \param newNode nowy w�ze�
		///
		void addNode(const Node& newNode);

		///
		/// \brief Funkcja dodaj�ca w�ze�
		/// \param id id nowego w�z�a
		///
		void addNode(int id);
	};


}