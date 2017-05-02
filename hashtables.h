/*
 * Lillie Bahrami, Tanner Bobak
 * TAs: Camilla Lambrocco, Sunil
 * CSCI 2270 Project
 */

#ifndef HASHTABLES_H
#define HASHTABLES_H
#include <vector>
#include <string>

// Struct for holding player data for both chaining and addressing tables.
struct player
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
	player *next;
	player *previous;

	player ()
	{
		player("","","",-1,-1,-1,"","");
	}

	player (std::string f, std::string l, std::string cB, int y, int w, int h, std::string b, std::string t)
	{
		first = f;
		last = l;
		key = "";
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
};

/*
 * I thought it would be easier to create one class that can run both
 * addressing and chaining algorithms (we would only call one kind or the
 * other for any given instance of the class), but if you think it would be
 * better to create two separate classes we can make that work too
 */
class hashTable
{

	public:
		hashTable(int size);
		~hashTable();
		void addressingAdd (std::string filename );
		void chainingAdd (std::string filename );
		void addressingSearch( std::string key );
		bool chainingSearch( std::string key );
		int hash(std::string name);

	private:
		int tableSize;
		player ** table;
		std::string getSearchKey(std::string key);
		void printPlayerInfo(player* p);
		std::string generateInfoString(int year, std::string team, std::string league, int salary);

};

#endif // HASHTABLES_H
