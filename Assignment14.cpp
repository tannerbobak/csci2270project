//Lillie Bahrami
//TA: Camilla Lambrocco
//CSCI 2270

//#include "hashtables.h"
#include <iostream>
#include <sstream>
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

	hashTable addressing (tableSize);
	hashTable chaining (tableSize);

	addressing.addressingAdd(filename);
	chaining.chainingAdd(filename);

	int answer = 0;
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
                bool found = chainingSearch(playerName);
                if (found)
                	addressingSearch(playerName);
                break;
            case 2: 
                answer = 2;
                break;
        }
    }

    return 0;
}


	