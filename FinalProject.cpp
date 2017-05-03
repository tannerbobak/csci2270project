/*
 * Lillie Bahrami, Tanner Bobak
 * TAs: Camilla Lambrocco, Sunil
 * CSCI 2270 Project
 *
 * Notes:
 * Unique entries by first and last name: 5072
 * Unique entries by playerID or (first + last + birth year + country + height + weight): 5147
 */

#include <iostream>
#include <sstream>
#include "HashTable.h"

using namespace std;

int main (int argc, char* argv[])
{
	// Checks if the user has entered enough arguments. I.e., they have entered a player database and a table size.
	if(argc != 3)
	{
		cout << "Invalid number of arguments.\nUsage: ./<program name> <player database> <table size>" << endl;
		return 0;
	}

	// Get filename from command line
	char *file = argv[1];
	string filename(file);

	// Get the table size from the command line and convert to an integer using a stringstream.
	char *ts = argv[2];
	string tSize(ts);
	int tableSize;
	stringstream(tSize)>>tableSize;

	// Print the hash table size.
	cout << "Hash table size: " << tableSize << endl;

	// Create two tables. One table uses open addressing, the other chaining in the event of collisions.
	HashTable addressing(tableSize);
	HashTable chaining(tableSize);

	/*
	 * These methods build each hash table from the database file. The first builds using chaining, the second
	 * using addressing. These methods will print the number of collisions and number of search operations
	 * required to build the table.
	 */
	chaining.chainingAdd(filename);
	addressing.addressingAdd(filename);

	// Stores the answer that a user enters at the main menu.
	int answer = 0;

	// Main program loop. Continues until the user quits by entering a "2".
	while (answer != 2)
    {

		// Display the main menu.
        cout << "======Main Menu======" << endl;
		cout << "1. Query hash table" << endl;
		cout << "2. Quit" << endl;

		// Get the answer from std::cin and extract to the answer variable.
		string ansStr;
        getline(cin, ansStr);
        stringstream(ansStr) >> answer;

        // Switch depending on the answer provided by the user.
        switch (answer)
        {
            case 1: // Query the hash table for a certain player.
            {
            	// Prompt the user for a player name (format: "firstname lastname")
                std::cout << "Enter a player:" << std::endl;

                // Get the player name and store into the variable.
                string playerName;
                getline (std::cin, playerName);

                /*
                 * Search the tables for the player and display the number of search operations required.
                 * This function returns true if the player was actually found, so that our program is
                 * more efficient by not performing an addressing search if the player is not in the table.
                 * Both tables have the same content, so if the player is not found in the chaining table
                 * it will not be found in the addressing one.
                 */
                bool found = chaining.chainingSearch(playerName);
                if (found)
                	addressing.addressingSearch(playerName);

                break;

            }
            case 2:  // Quit
            {
                answer = 2;

                break;
            }
            default: // Some kind of gibberish was entered.
            {
            	// Set answer to zero so the main menu will run again.
            	answer = 0;

            	break;
            }
        }
    }

    return 0;
}


	
