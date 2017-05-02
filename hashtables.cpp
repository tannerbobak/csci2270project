/*
 * Lillie Bahrami, Tanner Bobak
 * TAs: Camilla Lambrocco, Tanner Bobak
 * CSCI 2270
 */

#include "hashtables.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

hashTable::hashTable(int size)
{
	table = new player *[size];
	tableSize = size;
}

//TODO: check this
hashTable::~hashTable()
{
	delete[] table;
}

//TODO: test this 
//TODO: add counters, output statements
void hashTable::addressingAdd(string filename)
{
	ifstream reader;
	reader.open (filename.c_str());

	if (reader.fail())          //tests to make sure connection was successful
	{
		cout << "Reader failed" << std::endl;
		reader.close();
		return;
	}

	string templine;
	getline (reader, templine);	//will be descriptions of categories
	while (getline (reader, templine))	//will loop for every line in the file.
	{

		//get in all data from file
		istringstream iss(templine);
		string temp, team, league, first, last, birthcountry, throws, bats;
		int year, salary, birthyear, weight, height;
		getline (iss, temp, ',');
		stringstream(temp)>>year;
		//string team;
		getline (iss, temp, ',');
		team = temp;
		//string league;
		getline (iss, temp, ',');
		league = temp;
		getline (iss, temp, ',');	//playerID
		//int salary;
		getline (iss, temp, ',');
		stringstream(temp)>>salary;
		//string first;
		getline (iss, temp, ',');
		first = temp;
		//string last;
		getline (iss, temp, ',');
		last = temp;
		//int birthyear;
		getline (iss, temp, ',');
		stringstream(temp)>>birthyear;
		//string birthcountry;
		getline (iss, temp, ',');
		birthcountry = temp;
		//int weight;
		getline (iss, temp, ',');
		stringstream(temp)>>weight;
		//int height;
		getline (iss, temp, ',');
		stringstream(temp)>>height;
		//string bats;
		getline (iss, temp, ',');
		bats = temp;
		//string throws;
		getline (iss, temp, ',');
		throws = temp;

		player * person = new player(first, last, birthcountry, birthyear, weight, height, bats, throws);

		//making a string of information to be added to the player's info vector
		string data = "";
		data += year;
		data += ",";
		data += team;
		data += ",";
		data += league;
		data += ",";
		data += salary;

		//Now that the player's information has all been logged, the insertion can begin.
		int hashcode = hash(person->key);

		player *current;
		current = table[hashcode];
		if (current->next == nullptr)	//nothing in spot
		{
			current->next = person;
			person->previous = current;
		}
		else	//spot already taken, will have to find next open spot
		{
			bool isFound = false;
			int current = hashcode + 1;
			while (table[current]->next != nullptr) //until we traverse to an open spot...
			{
				if (table[current]->key == person->key && table[current]->yearBorn == person->yearBorn && table[current]->countryBorn == person->countryBorn) //if duplicate found
				{
					cout << "duplicate";
					table[current]->next->info.push_back(data);	//add record of player's year
					isFound = true;
					break;
				}

				if (current == tableSize - 1)	//last node in table
				{
					current = 0;	//go back to top of array
				}
				else if (current == hashcode)	//table is full
				{
					cout << "Table is full" << endl;
					isFound = true;
					break;
				}
				else
				{
					current++;
				}
			}

			//open spot found: add node to table
			if (!isFound)
			{
				table[current]->next = person;
				person->previous = table[current]->next;
			}
		}
	}
}

//TODO: Test this
//TODO: Counters and output statements.
void hashTable::chainingAdd (string filename)
{
	ifstream reader;
	reader.open (filename.c_str());

	if (reader.fail())    //tests to make sure connection was successful
	{
		cout << "Reader failed" << std::endl;
		reader.close();
		return;
	}

	string templine;
	getline (reader, templine);	//will be descriptions of categories
	while (getline (reader, templine))	//will loop for every line in the file.
	{

		//get in all data from file
		istringstream iss(templine);
		string temp, team, league, first, last, birthcountry, throws, bats;
		int year, salary, birthyear, weight, height;
		getline (iss, temp, ',');
		stringstream(temp)>>year;
		//string team;
		getline (iss, temp, ',');
		team = temp;
		//string league;
		getline (iss, temp, ',');
		league = temp;
		getline (iss, temp, ',');	//playerID
		//int salary;
		getline (iss, temp, ',');
		stringstream(temp)>>salary;
		//string first;
		getline (iss, temp, ',');
		first = temp;
		//string last;
		getline (iss, temp, ',');
		last = temp;
		//int birthyear;
		getline (iss, temp, ',');
		stringstream(temp)>>birthyear;
		//string birthcountry;
		getline (iss, temp, ',');
		birthcountry = temp;
		//int weight;
		getline (iss, temp, ',');
		stringstream(temp)>>weight;
		//int height;
		getline (iss, temp, ',');
		stringstream(temp)>>height;
		//string bats;
		getline (iss, temp, ',');
		bats = temp;
		//string throws;
		getline (iss, temp, ',');
		throws = temp;

		player * person = new player(first, last, birthcountry, birthyear, weight, height, bats, throws);

		//making a string of information to be added to the player's info vector
		string data = "";
		data += year;
		data += ",";
		data += team;
		data += ",";
		data += league;
		data += ",";
		data += salary;

		//Now that the player's information has all been logged, the insertion can begin.
		int hashcode = hash(person->key);

		player *current = table[hashcode];
		if (current->next == nullptr)	//nothing in spot
		{
			current->next = person;
			person->previous = current;
		}
		else	//spot already taken, will have to chain
		{
			bool isFound = false;

			current = current->next;	//Search through chain to make sure the player isn't already in the table.
			while (current != nullptr)
			{
				if (current->key == person->key && current->yearBorn == person->yearBorn && current->countryBorn == person->countryBorn) //if they're the same
				{
					cout << "duplicate";
					current->info.push_back(data);	//add record of player's year
					isFound = true;
				}
				current = current->next;
			}

			//If the player isn't already in the chain, add them alphabetically
			person->info.push_back(data);
			current = table[hashcode]->next;	//reset pointer
			if (person->key > current->key && !isFound) //if player is alphabetically higher than the first node in the chain
			{
				table[hashcode]->next->previous = person;
				person->next = table[hashcode]->next;
				person->previous = table[hashcode];
				table[hashcode]->next = person;
				//isFound = true;
			}
			else
			{
				while (current->next != nullptr)	//until the last node in the chain
				{
					if (person->key > current->next->key) //if player should be inserted between the current node and the next node
					{
						current->next->previous = person;
						person->next = current->next;
						person->previous = current;
						table[hashcode]->next = person;
						isFound = true;
					}
				}

				//player should be added after last node in the chain
				if (!isFound)
				{
					current->next = person;
					person->next = NULL;
					person->previous = current;
				}
			}

		}
	}

	reader.close();
}

void hashTable::addressingSearch ( std::string key )
{

	int collisions = 0;

	// Convert key (format: "firstname lastname") to a key (format: "firstnamelastname")
	string searchKey = getSearchKey(key);

	int initialIdx = hash(searchKey);
	int i = initialIdx;
	bool found = false;
	player* p = table[i];
	while(!found)
	{
		if(p == nullptr) // hole
			break;

		if(p->key == searchKey)
		{
			found = true;
		}
		else
		{
			++i;
			++collisions;

			if(i == tableSize) i = 0; // Loop back to beginning
			if(i == initialIdx - 1) break; // Looped around the entire table

			p = table[i];
		}
	}

	if(found)
	{
		printPlayerInfo(t);
		cout << "Search operations using open addressing: " << collisions << endl;
	}
	else
		cout << "Player not found." << endl;

}

bool hashTable::chainingSearch ( std::string key )
{

	// Track number of collisions.
	int collisions = 0;

	// Convert key (format: "firstname lastname") to a key (format: "firstnamelastname")
	string searchKey = getSearchKey(key);

	// Search the table
	int hash = hash(searchKey);
	player* t = table[hash];
	bool found = false;
	while(!found)
	{
		if(t == nullptr)
			break;

		if(t->key == searchKey)
		{
			found = true;
		}
		else
		{
			t = t->next;
			++collisions;
		}
	}

	if(found)
	{
		printPlayerInfo(t);
		cout << "Search operations using chaining: " << collisions << endl;
	}
	else
		cout << "Player not found." << endl;

	return found;
}

std::string hashTable::getSearchKey(std::string key)
{
	istringstream stream(key);
	string first, last, searchKey;
	getline(stream, first, ' ');
	getline(stream, last);
	stream = "";
	stream << first << last;
	stream >> searchKey;
	return searchKey;
}

void hashTable::printPlayerInfo(player* p)
{

}
