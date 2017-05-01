//Lillie Bahrami
//TA: Camilla Lambrocco
//CSCI 2270

#ifndef HASHTABLES_H
#define HASHTABLES_H
#include <vector>
#include <string>

struct player 	//holds all data for each player
{
	std::string key;
	int yearBorn;
	std::string countryBorn;
	std::string first;	//first name
	std::string last;	//last name
	int weight;
	int height;
	std::string bats;
	std::string throws;
	player *next;
	player *previous;
	std::vector <std::string> info;	//will hold strings of year, league, team, salary.
	player ()
	{
		next = NULL;
		previous = NULL;
	}
	player (std::string f, std::string l, std::string cB, int y, int w, int h, std::string b, std::string t)
	{
		first = f;
		last = l;
		key = "";
		key+= last;
		key+= first;
		countryBorn = cB;
		yearBorn = y;
		weight = w;
		height = h;
		bats = b;
		throws = t;
		next = NULL;
		previous = NULL;
	}
};

/*I thought it would be easier to create one class that can run both 
addressing and chaining algorithms (we would only call one kind or the 
other for any given instance of the class), but if you think it would be
better to create two separate classes we can make that work too*/
class hashTable
{
	public:
		hashTable(int size);
		~hashTable();
		void addressingAdd (std::string filename);
		void chainingAdd (std::string filename);
		void addressingSearch ();
		bool chainingSearch ();
		int hash(std::string name);

	private:
		int tableSize;
		player ** table;
};

//#include "hashtables.cpp" //was having trouble making this work
#endif // HASHTABLES_H