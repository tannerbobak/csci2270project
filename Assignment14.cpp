/*
 * Lillie Bahrami, Tanner Bobak
 * TAs: Camilla Lambrocco, Sunil
 * CSCI 2270
 */

#include "hashtable.h"
#include <iostream>
#include <sstream>
#include "hashtables.h"
using namespace std;

int main (int argc, char* argv[])
{
	//get filename from command line
	char *file = argv[1];
	string filename(file);
	char *ts = argv[2];
	string tSize(ts);
	int tableSize;
	stringstream(tSize)>>tableSize;
	cout << tableSize << endl;

	hashTable addressing(tableSize);
	hashTable chaining(tableSize);

	cout << "Hash table size: " << tableSize << endl;
	chaining.chainingAdd(filename);
	chaining.chainingSearch("Jerry Koosman");
	//chaining.chainingAdd(filename);

	/*int answer = 0;
	string playerName;

	while (answer != 2)
    {
        cout << "======Main Menu======" << endl;
		cout << "1. Query hash table" << endl;
		cout << "2. Quit" << endl;
        cin >> answer;

        switch (answer)
        {
            case 1:
            	cin.ignore();
                std::cout << "Enter a player:" << std::endl;
                getline (std::cin, playerName);
                bool found = chaining.chainingSearch(playerName);
                if (found)
                	addressing.addressingSearch(playerName);
                break;
            case 2: 
                answer = 2;
                break;
        }
    }*/

    return 0;
}


	
