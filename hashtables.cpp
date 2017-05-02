/*
 * Lillie Bahrami, Tanner Bobak
 * TAs: Camilla Lambrocco, Sunil 
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
    	string temp, team, league, first, last, birthcountry, throws, bats, sal;
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
        sal = temp;
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
        cout << hashcode << endl;

    	player *current = table[hashcode];
    	if (current == nullptr)	//nothing in spot
    	{
    		table[hashcode] = person;
    	}
    	else	//at least one node in spot, will have to chain
    	{
    		collisionCount++;
    		bool isFound = false;

    		//Search through chain to make sure the player isn't already in the table.
    		searchCount++;
    		while (current->next != nullptr)
    		{
    			searchCount++;
    			if (current->key == person->key && current->yearBorn == person->yearBorn && current->countryBorn == person->countryBorn) //if they're the same
    			{
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
    	}
    }

    cout << "Collisions using chaining: " << collisionCount << endl;
    cout << "Search operations using chaining: " << searchCount << endl;
    reader.close();
}

/*This function takes in the name of a player and searches through a hash
table set up using addressing methods to locate the player's data, if they exist.
*/
void hashTable::addressingSearch (std::string key)
{
	int searchOps = 0; //counts number of searching operations

	// Convert key (format: "firstname lastname") to a key (format: "firstnamelastname")
	string searchKey = getSearchKey(key);
	
    int initialIdx = hash(searchKey);   //generate hashcode as index of array where search will begin
	int i = initialIdx;    //will be used to navigate through the array
	bool found = false;
	player* p = table[i];  //pointer to player at beginning index of search
	
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

/*This function takes in the name of a player and searches through a hash
table set up using chaining methods to locate the player's data, if they exist.
It returns a bool representing whether the player was found, so that if the
player was not found the addressing search method will not be performed.*/
bool hashTable::chainingSearch (std::string key)
{

	// Track number of searching operations.
	int searchOps = 0;

	// Convert key (format: "firstname lastname") to a key (format: "firstnamelastname")
	string searchKey = getSearchKey(key);

	// Search the table
	int hashcode = hash(searchKey);    //generate hash
    cout << hashcode << endl;
	player* t = table[hashcode];   
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

/*This function takes a key in the format "firstname lastname"
and changes it into the format "firstnamelastname" using getline.*/
std::string hashTable::getSearchKey(std::string key)
{
	istringstream stream(key);
	string first, last, searchKey;
	getline(stream, first, ' ');
	getline(stream, last);
	searchKey = first + last;
	return searchKey;
}

/*This function takes in a pointer to a player and outputs the information for that player*/
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
	for(unsigned int i = 0; i < p->info.size(); ++i)   //if player participated in multiple years, they will have multiple information strings stored
		cout << p->info[i] << endl;
}

string hashTable::generateInfoString(int year, std::string team, std::string league, int salary)
{
	return std::to_string(year) + "," + team + "," + league + "," + std::to_string(salary);
}
