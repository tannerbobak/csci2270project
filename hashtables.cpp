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

int hashTable::hash(string name)
{
	int sum = 0;
	for (int x = 0; x < name.size(); x++)
	{
		//cout << name[x] << endl;
		sum += name[x];
	}
	sum = sum%tableSize;
	return sum;
}

void hashTable::addressingAdd(string filename)
{
	ifstream reader;
	reader.open (filename.c_str());
	int collisionCount = 0;
	int searchCount = 0;

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
    	//cout << "reading in a line" << endl;
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
    	string data = generateInfoString(year, team, league, salary);

    	//cout << "player created: " << person->first << "," << person->last << endl;
    	//cout << "table size: " << tableSize << endl;
    	
    	//Now that the player's information has all been logged, the insertion can begin. 
    	int hashcode = hash(person->key);

    	//cout << "hashed" << endl;
    	//cout << hashcode << endl;

    	if (table[hashcode] == nullptr)	//nothing in spot
    	{
    		//cout << "no collision" << endl;
    		table[hashcode] = person;
    	}
    	else	//spot already taken, will have to find next open spot
    	{
    		//cout << "collision" << endl;
    		collisionCount++;
    		bool isFound = false;
    		int current = hashcode;

    		while (table[current] != nullptr) //until we traverse to an open spot...
    		{
    			//cout << "traversing" << endl;
    			//cout << current << endl;
    			searchCount++;

    			if (table[current]->key == person->key && table[current]->yearBorn == person->yearBorn &&
    					table[current]->countryBorn == person->countryBorn && table[current]->weight == person->weight) //if duplicate found
    			{
    				//cout << "duplicate";
    				table[current]->info.push_back(data);	//add record of player's year
    				isFound = true;
    				break;
    			}

    			if (current == tableSize - 1)	//last node in table
    			{
    				//cout << "this" << endl;
    				current = 0;	//go back to top of array
    			}
    			else if (current == hashcode - 1)	//table is full
    			{
    				cout << "Table is full" << endl;
    				break;
    			}
    			else
    			{
    				current++;
    			}
    		}

    		//open spot found: add node to table
    		if (!isFound)
    			table[current] = person;
    	}
    }

    cout << "Collisions using open addressing: " << collisionCount << endl;
    cout << "Search operations using open addressing: " << searchCount << endl;

}

//TODO: Test this
//TODO: Counters and output statements.
void hashTable::chainingAdd (string filename)
{
	ifstream reader;
	reader.open (filename.c_str());
	int collisionCount = 0;
	int searchCount = 0;

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
    	string data = generateInfoString(year, team, league, salary);
    	
    	//Now that the player's information has all been logged, the insertion can begin. 
    	int hashcode = hash(person->key);
    	cout << "hash is: " << hashcode << endl;

    	player *current = table[hashcode];
    	if (current == nullptr)	//nothing in spot
    	{
    		cout << "no collision" << endl;
    		table[hashcode] = person;
    	}
    	else	//at least one node in spot, will have to chain
    	{
    		cout << "collision" << endl;
    		collisionCount++;
    		bool isFound = false;

    		//Search through chain to make sure the player isn't already in the table.
    		searchCount++;
    		while (current->next != nullptr)
    		{
    			searchCount++;
    			if (current->key == person->key && current->yearBorn == person->yearBorn && current->countryBorn == person->countryBorn) //if they're the same
    			{
    				cout << "duplicate";
    				current->info.push_back(data);	//add record of player's year
    				isFound = true;
    				break;
    			}
    			current = current->next;
    		}

    		//If the player isn't already in the chain, add them to the end
    		if (!isFound)
    		{
    			person->info.push_back(data);
    			current->next = person;
    			person->previous = current;
    		}


    		/*
    		person->info.push_back(data);
    		current = table[hashcode]->next;	//reset pointer
    		if (person->key > current->key && !isFound) //if player is alphabetically higher than the first node in the chain
    		{
    			searchCount++;
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
	    			searchCount++;
	    			if (person->key > current->next->key) //if player should be inserted between the current node and the next node
	    			{
	    				current->next->previous = person;
		    			person->next = current->next;
		    			person->previous = current;
		    			table[hashcode]->next = person;
		    			isFound = true;
		    			break;
	    			}

	    			current = current->next;
	    		}

	    		//player should be added after last node in the chains
				if (!isFound)
				{
					current->next = person;
					person->next = nullptr;
					person->previous = current;
				}
			}

		}
	}

	reader.close();
    		}*/
    	}
    }
    cout << "Collisions using chaining: " << collisionCount << endl;
    cout << "Search operations using chaining: " << searchCount << endl;
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
			printPlayerInfo(p);
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
	int hashcode = hash(searchKey);
	player* t = table[hashcode];
	bool found = false;
	while(!found)
	{
		if(t == nullptr)
			break;

		if(t->key == searchKey)
		{
			found = true;
			printPlayerInfo(t);
		}
		else
		{
			t = t->next;
			++collisions;
		}
	}

	if(found)
	{
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
	searchKey = last + first;
	return searchKey;
}

void hashTable::printPlayerInfo(player* p)
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
	for(unsigned int i = 0; i < p->info.size(); ++i)
		cout << p->info[i] << endl;
}

string hashTable::generateInfoString(int year, std::string team, std::string league, int salary)
{
	return std::to_string(year) + "," + team + "," + league + "," + std::to_string(salary);
}
