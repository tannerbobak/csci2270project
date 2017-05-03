/*
 * Lillie Bahrami, Tanner Bobak
 * TAs: Camilla Lambrocco, Sunil
 * CSCI 2270 Project
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <vector>
#include <string>

// Structure for holding player data for both chaining and addressing tables.
struct Player
{
	// Basic player data retrieved from file.
	std::string key; 							// Key used in the table.
	int yearBorn; 								// Year that the player was born.
	std::string countryBorn; 					// Country that the player was born in.
	std::string first; 							// First Name
	std::string last;							// Last Name
	int weight;									// Player's weight
	int height;									// Player's height
	std::string bats;							// Batting handedness of the player
	std::string throws;							// Throwing handedness of the player
	std::vector <std::string> info;				// This will hold strings with data on year, league, team, and salary.

	// Variables used for chaining only.
	Player *next;
	Player *previous;

	// Basic constructor with default values.
	Player ()
	{
		first = "";
		last = "";
		key = "";
		countryBorn = "";
		yearBorn = -1;
		weight = -1;
		height = -1;
		bats = "";
		throws = "";
		next = nullptr;
		previous = nullptr;
	}

	// Polymorphic constructor with parameters for values.
	Player (std::string f, std::string l, std::string cB, int y, int w, int h, std::string b, std::string t)
	{
		first = f;
		last = l;
		key = first + last;
		countryBorn = cB;
		yearBorn = y;
		weight = w;
		height = h;
		bats = b;
		throws = t;
		next = nullptr;
		previous = nullptr;
	}

	// Deconstructor calls delete on the next item if it is chained.
	~Player() {
		if(next != nullptr)
		{
			delete next;
		}
	}
};

/*
 * I thought it would be easier to create one class that can run both
 * addressing and chaining algorithms (we would only call one kind or the
 * other for any given instance of the class), but if you think it would be
 * better to create two separate classes we can make that work too
 */
class HashTable
{

	public:
		HashTable(int size);
		~HashTable();
		void addressingAdd (std::string filename );
		void chainingAdd (std::string filename );
		void addressingSearch( std::string key );
		bool chainingSearch( std::string key );
		int hash(std::string name);

	private:
		int tableSize;
		Player ** table;
		std::string getSearchKey(std::string key);
		void printPlayerInfo(Player* p);
		std::string generateInfoString(int year, std::string team, std::string league, int salary);

};

#endif // HASHTABLE_H
