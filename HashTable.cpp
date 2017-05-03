/*
 * Lillie Bahrami, Tanner Bobak
 * TAs: Camilla Lambrocco, Sunil 
 * CSCI 2270 Project
 */

#include "HashTable.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

// Constructor initializes the table to the specified size.
HashTable::HashTable(int size)
{
	table = new Player* [size];
	tableSize = size;
}

// Deconstructor
HashTable::~HashTable()
{
	delete[] table;
}

/*
 * Simple hash function for our table. Sums the value of the characters in the
 * given name and then mods by the table size to produce an index.
 *
 * Post-conditions:
 * - A hash code representing an index in the array is produced.
 */
int HashTable::hash(string name)
{
	int sum = 0;
	for (int x = 0; x < name.size(); x++)
		sum += name[x];

	sum = sum%tableSize;
	return sum;
}

/*
 * Adds the players contained in the given database file to the hash table using
 * open addressing.
 *
 * Preconditions:
 * - "string filename" represents a file name to read from. If it is not valid,
 *   the function will exit.
 *
 * Post-conditions:
 * - The table will be populated from the given data using open addressing.
 * - For each element that cannot be added to the table because it is full,
 *   "Table is full" will be printed once.
 */
void HashTable::addressingAdd(string filename)
{
	// Open the file
	ifstream reader;
	reader.open (filename.c_str());

	if (reader.fail()) // Tests to make sure file open was successful
	{
		cout << "Reader failed" << std::endl;
		reader.close();
		return;
	}

	// Variables to track the number of collisions and the number of searches.
	// Used for the report.
	int collisionCount = 0;
	int searchCount = 0;

	// Read in the data from the file line-by-line.
	string templine;
    getline (reader, templine);	// The first line will be descriptions of categories. Discard.

    while (getline (reader, templine))	// Now loop for every line in the file.
    {
    	// String stream for converting data.
    	istringstream iss(templine);

    	// Variables to store player data.
    	string temp, team, league, first, last, birthcountry, throws, bats;
    	int year, salary, birthyear, weight, height;

    	// Year
    	getline (iss, temp, ',');
    	stringstream(temp)>>year; // Convert to int.

    	// Team
    	getline (iss, temp, ',');
    	team = temp;

    	// League
    	getline (iss, temp, ',');
    	league = temp;

    	// Player ID, not saved.
    	getline (iss, temp, ',');

    	// Salary
    	getline (iss, temp, ',');
    	stringstream(temp)>>salary; // Convert to int.

    	// First name
    	getline (iss, temp, ',');
    	first = temp;

    	// Last name
    	getline (iss, temp, ',');
    	last = temp;

    	// Birth year
    	getline (iss, temp, ',');
    	stringstream(temp)>>birthyear; // Convert to int.

    	// Birth country
    	getline (iss, temp, ',');
    	birthcountry = temp;

    	// Weight (lbs)
    	getline (iss, temp, ',');
    	stringstream(temp)>>weight; // Convert to int.

    	// Height (in)
    	getline (iss, temp, ',');
    	stringstream(temp)>>height; // Convert to int.

    	// Batting handedness
    	getline (iss, temp, ',');
    	bats = temp;

    	// Throwing handedness
    	getline (iss, temp, ',');
    	throws = temp;

    	// Create the player.
    	Player* person = new Player(first, last, birthcountry, birthyear, weight, height, bats, throws);

    	// Making a string of information to be added to the player's info vector.
    	string data = generateInfoString(year, team, league, salary);

    	//Now that the player's information has all been logged, the table insertion can begin.
    	int hashcode = hash(person->key);

    	if (table[hashcode] == nullptr)	// True if the spot the player hashed to is empty. Add person to that spot.
    	{
    		person->info.push_back(data);
    		table[hashcode] = person;
    	}
    	else	// True if the spot the player hashed to is already taken, will have to find next open spot.
    	{
    		++collisionCount; // Increment the number of collisions.
    		bool isFound = false; // Keeps track if a record for this player is already in the table.
    		int current = hashcode; // Index of the current item to check for an open spot.

    		while (table[current] != nullptr) // Traverse to an open spot...
    		{
    			++searchCount; // Increment the counter for number of search operations.

    			// These conditions check if two players are the same on the basis of their key, birth year
    			// birth country, and weight.
    			if (table[current]->key == person->key && table[current]->yearBorn == person->yearBorn &&
    			    table[current]->countryBorn == person->countryBorn && table[current]->weight == person->weight)
    			{
    				// If the player is a duplicate, flag that a match is found and add the team info to the vector.
    				table[current]->info.push_back(data);
    				isFound = true;
    				break;
    			}

    			if (current == tableSize - 1) // Last node in table, loop back to start.
    			{
    				current = 0;
    			}
    			else if (current == hashcode - 1) // Table is full, program has looped all the way through the table.
    			{
    				cout << "Table is full" << endl;
    				break;
    			}
    			else // Neither at the end nor full, then increment the index.
    			{
    				current++;
    			}
    		}

    		// If an open spot found, then add the node to table as a new entry.
    		if (!isFound)
    		{
    			person->info.push_back(data);
    			table[current] = person;
    		}
    	}
    }

    // Print out data.
    cout << "Collisions using open addressing: " << collisionCount << endl;
    cout << "Search operations using open addressing: " << searchCount << endl;

    // Close the file.
    reader.close();

}

/*
 * Adds the players contained in the given database file to the hash table using
 * chaining.
 *
 * Preconditions:
 * - "string filename" represents a file name to read from. If it is not valid,
 *   the function will exit.
 *
 * Post-conditions:
 * - The table will be populated from the given data using chaining.
 */
void HashTable::chainingAdd (string filename)
{
	// Open the file
	ifstream reader;
	reader.open (filename.c_str());

	if (reader.fail()) // Tests to make sure file open was successful
	{
		cout << "Reader failed" << std::endl;
		reader.close();
		return;
	}

	// Variables to track the number of collisions and the number of searches.
	// Used for the report.
	int collisionCount = 0;
	int searchCount = 0;

	// Read in the data from the report line-by-line.
	string templine;
	getline (reader, templine);	// The first line will be descriptions of categories. Discard.

	while (getline (reader, templine))	// Now loop for every line in the file.
	{
		// String stream for converting data.
		istringstream iss(templine);

		// Variables to store player data.
		string temp, team, league, first, last, birthcountry, throws, bats;
		int year, salary, birthyear, weight, height;

		// Year
		getline (iss, temp, ',');
		stringstream(temp)>>year; // Convert to int.

		// Team
		getline (iss, temp, ',');
		team = temp;

		// League
		getline (iss, temp, ',');
		league = temp;

		// Player ID, not saved.
		getline (iss, temp, ',');

		// Salary
		getline (iss, temp, ',');
		stringstream(temp)>>salary; // Convert to int.

		// First name
		getline (iss, temp, ',');
		first = temp;

		// Last name
		getline (iss, temp, ',');
		last = temp;

		// Birth year
		getline (iss, temp, ',');
		stringstream(temp)>>birthyear; // Convert to int.

		// Birth country
		getline (iss, temp, ',');
		birthcountry = temp;

		// Weight (lbs)
		getline (iss, temp, ',');
		stringstream(temp)>>weight; // Convert to int.

		// Height (in)
		getline (iss, temp, ',');
		stringstream(temp)>>height; // Convert to int.

		// Batting handedness
		getline (iss, temp, ',');
		bats = temp;

		// Throwing handedness
		getline (iss, temp, ',');
		throws = temp;

		// Create the player.
		Player* person = new Player(first, last, birthcountry, birthyear, weight, height, bats, throws);

		// Making a string of information to be added to the player's info vector.
		string data = generateInfoString(year, team, league, salary);

		//Now that the player's information has all been logged, the table insertion can begin.
		int hashcode = hash(person->key);

		// Stores the value of the element in the chain currently being iterated over.
    	Player *current = table[hashcode];
    	if (current == nullptr)	// If there is nothing in the table where the player hashes to, just add it.
    	{
    		person->info.push_back(data);
    		table[hashcode] = person;
    	}
    	else // There is at least one node in spot, we will have to chain
    	{
    		++collisionCount; // Increment the number of collisions.
    		bool isFound = false; // Tracks if a matching player is already found in the table

    		//Search through chain to make sure the player isn't already in the table.
    		

    		while (current->next != nullptr)
    		{
    			++searchCount; // Increment search count.

    			// These conditions check if two players are the same on the basis of their key, birth year
				// birth country, and weight.
				if (current->key == person->key && current->yearBorn == person->yearBorn &&
					current->countryBorn == person->countryBorn && current->weight == person->weight)
    			{
    				current->info.push_back(data);	//add record of player's year
    				isFound = true;
    				break;
    			}

				// Move to the next element in the chain.
    			current = current->next;
    		}

    		//If the player isn't already in the chain, add them to the end
    		if (!isFound)
    		{
    			person->info.push_back(data);

    			// Add player to end of linked list.
    			current->next = person;
    			person->previous = current;
    		}
    	}
    }

	// Print data
    cout << "Collisions using chaining: " << collisionCount << endl;
    cout << "Search operations using chaining: " << searchCount << endl;

    // Close file reader.
    reader.close();
}

/*
 * This function takes in the name of a player and searches through a hash
 * table set up using addressing methods to locate the player's data, if they exist.
 */
void HashTable::addressingSearch (std::string key)
{
	int searchOps = 0; //counts number of searching operations

	// Convert key (format: "firstname lastname") to a key (format: "firstnamelastname")
	string searchKey = getSearchKey(key);
	
    int initialIdx = hash(searchKey);   //generate hashcode as index of array where search will begin
	int i = initialIdx;    //will be used to navigate through the array
	bool found = false;
	Player* p = table[i];  //pointer to player at beginning index of search
	
    while(!found)
	{
		if(p == nullptr) //no player registered at index, meaning no player w/ hashcode of initialIdx could have been placed there
			break;

		if(p->key == searchKey)   //player found
		{
			printPlayerInfo(p);
			found = true;
		}
		else
		{
			++i; //move to next index of array, constituting one search operation
			++searchOps; 

			if(i == tableSize) i = 0; // Loop back to start of array
			if(i == initialIdx - 1) break; // Entire table has been searched

			p = table[i];    //reset pointer
		}
	}

	if(found)
	{
		cout << "Search operations using open addressing: " << searchOps << endl;
	}
	else
		cout << "Player not found." << endl;
}

/*
 * This function takes in the name of a player and searches through a hash
 * table set up using chaining methods to locate the player's data, if they exist.
 * It returns a bool representing whether the player was found, so that if the
 * player was not found the addressing search method will not be performed.
 */
bool HashTable::chainingSearch (std::string key)
{

	// Track number of searching operations.
	int searchOps = 0;

	// Convert key (format: "firstname lastname") to a key (format: "firstnamelastname")
	string searchKey = getSearchKey(key);

	// Search the table
	int hashcode = hash(searchKey);    //generate hash
	Player* t = table[hashcode];
	bool found = false;

	while(!found)
	{
		if(t == nullptr)  //nothing has been stored at the designated index, or reached end of linked list
			break;

		if(t->key == searchKey)   //player located
		{
			found = true;
			printPlayerInfo(t);
		}
		else
		{
			t = t->next; //move along linked list (constitutes one search operation)
			++searchOps;
		}
	}

	if(found)
	{
		cout << "Search operations using chaining: " << searchOps << endl;
	}
	else
		cout << "Player not found." << endl;

	return found;  
}

/*
 * This function takes a key in the format "firstname lastname"
 * and changes it into the format "firstnamelastname" using getline.
 */
std::string HashTable::getSearchKey(std::string key)
{
	istringstream stream(key);
	string first, last, searchKey;
	getline(stream, first, ' ');
	getline(stream, last);
	searchKey = first + last;
	return searchKey;
}

/*
 * This function takes in a pointer to a player and outputs the information for that player
 */
void HashTable::printPlayerInfo(Player* p)
{
	cout << "First name: " << p->first << endl;
	cout << "Last name: " << p->last << endl;
	cout << "Year born: " << p->yearBorn << endl;
	cout << "Country born: " << p->countryBorn << endl;
	cout << "Weight: " << p->weight << endl;
	cout << "Height: " << p->height << endl;
	cout << "Bats: " << p->bats << endl;
	cout << "Throws: " << p->throws << endl;
	cout << "Teams and salary:" << endl;
	for(unsigned int i = 0; i < p->info.size(); ++i)   //if player participated in multiple years, they will have multiple information strings stored
		cout << p->info[i] << endl;
}

/* 
* This function concatentates various attributes of the player into an information
* string which will be stored in the player's info vector.
*/
string HashTable::generateInfoString(int year, std::string team, std::string league, int salary)
{
	return std::to_string(year) + "," + team + "," + league + "," + std::to_string(salary);
}
