#pragma once
#include <string>
#include <map>

namespace GIS
{
	///
	/// \brief Klasa ścieżki grafu
	///
	struct Path 
	{
		int connectedNodeId;
		int weight;
	};

	///
	/// \brief Klasa węzła grafu posiadająca id węzła oraz mapę połączeń tego węzła z innymi
	///
	struct Node
	{
		///
		/// \brief Konstruktor węzła o podanym id
		/// \param id id węzła
		///
		Node(int id);

		int id;
		std::map<int, Path> connections;

		///
		/// \brief Konstruktor węzła o podanym id
		/// \param nodeId id węzła
		/// \return zwraca true lub false w zależności czy dany węzeł jest połączony z drugim
		///
		bool hasConnection(int nodeId) const;
	};

	///
	/// \brief Klasa grafu skierowanego, gdzie między tymi samymi węzłami może być maksymalnie jedno połączenie (w jednym kierunku)
	///
	class Graph : private std::map<int ,Node>
	{
	public:
		///
		/// \brief Konstruktor bezargumentowy
		///
		Graph();

		///
		/// \brief Konstruktor tworzący graf o danej ilości węzłów (bez połączeń)
		/// \param nodeAmount ilość węzłów
		///
		Graph(int nodeAmount);

		///
		/// \brief Konstruktor grafu wczytujący dane o węzłach i połączeniach z pliku
		/// \param fileName ścieżka do pliku
		///
		Graph(std::string fileName);
		///
		/// \brief Destruktor
		///
		~Graph();

		///
		/// \brief Funkcja zwracająca węzeł
		/// \param nodeId id węzła
		/// \return węzeł o danym id
		///
		const Node& getNode(int nodeId) const;
		
		///
		/// \brief Funkcja zwracająca ilość węzłów
		/// \return ilość węzłów
		///
		int getSize() const;
		
		///
		/// \brief Funkcja dodająca połączenie
		/// \param noteId id węzła początkowego
		/// \param connectedNodeId id węzła końcowego
		/// \param weight waga ścieżki
		///
		void addPath(int nodeId, int connectedNodeId, int weight);

		///
		/// \brief Funkcja dodająca połączenie
		/// \param noteId id węzła początkowego
		/// \param path nowa ścieżka
		///
		void addConnection(int nodeId, const Path& path);


		///
		/// \brief Funkcja dodająca węzeł z kolejnym numerem id
		///
		void addNode();

		///
		/// \brief Funkcja dodająca węzeł
		/// \param newNode nowy węzeł
		///
		void addNode(const Node& newNode);

		///
		/// \brief Funkcja dodająca węzeł
		/// \param id id nowego węzła
		///
		void addNode(int id);
	};








}
