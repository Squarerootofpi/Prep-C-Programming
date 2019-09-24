#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK;
#endif


#include "BST.h" //#includes are primarily in BST.h
#include "HashMap.h"
#include "Set.h"

using std::getline;
using std::cin;


int main(int argc, char* argv[])
{
	VS_MEM_CHECK
		
	std::ifstream inputFile(argv[1]);
	if (!inputFile)
	{
		std::cout << "input opening error" << std::endl;
		return 1;
	}
	std::ofstream outputFile(argv[2]);
	if (!outputFile)
	{
		std::cout << "output opening error" << std::endl;
		return 1;
	}

	string command;
	string secondCommand;

	HashMap<string, string> moves;
	HashMap<string, string> pokemon;
	HashMap<string, Set<string>> effectives;
	HashMap<string, Set<string>> ineffectives;



	while (inputFile >> command)
	{
		try
		{


			if (command == "Set:")
			{
				stringstream ssCommands(command); //So, putting this in the outside scope somehow
												  //made it go out of scope afte the first iteration. Interesting.  
				outputFile << command;
				string tempCommand;

				getline(inputFile, tempCommand);
				if (tempCommand.size() < 2)
				{
					throw std::string("No set to add");
				}
				ssCommands.str(tempCommand); //putting command in stringstream

				Set<string> oneString;

				while (ssCommands >> command) //parsing back into command
				{
					outputFile << " " << command;
					oneString.insert(command);
				}
				
				outputFile << endl << "  [" << oneString.toString() << "]" << endl;
				outputFile << endl;
			}
			else if (command == "Pokemon:")
			{
				outputFile << command;
				inputFile >> command;
				inputFile >> secondCommand;
				outputFile << " " << command << " " << secondCommand << endl;
				pokemon[command] = secondCommand;

			}
			else if (command == "Move:")
			{
				outputFile << command;
				inputFile >> command;
				inputFile >> secondCommand;
				outputFile << " " << command << " " << secondCommand << endl;
				moves[command] = secondCommand;

			}
			else if (command == "Effective:")
			{
				outputFile << command;

				stringstream ssCommands(command); //So, putting this in the outside scope somehow
												  //made it go out of scope afte the first iteration. Interesting.  
				string firstCommand;
				inputFile >> firstCommand;
				outputFile << " " << firstCommand;
				string tempCommand;

				getline(inputFile, tempCommand);
				if (tempCommand.size() < 2)
				{
					throw std::string("No set to add");
				}
				ssCommands.str(tempCommand); //putting command in stringstream

				//Set<string> oneString;
				while (ssCommands >> command)
				{
					outputFile << " " << command;
					effectives[firstCommand].insert(command);
				}
				/*while (ssCommands >> command) //parsing back into command
				{
					//oneString.insert(command);
				}*/
				//effectives[firstCommand] = oneString;

				outputFile << endl;

			}
			else if (command == "Ineffective:")
			{
				outputFile << command;

				stringstream ssCommands(command); //So, putting this in the outside scope somehow
												  //made it go out of scope afte the first iteration. Interesting.  
				string firstCommand;
				inputFile >> firstCommand;
				outputFile << " " << firstCommand;
				string tempCommand;

				getline(inputFile, tempCommand);
				if (tempCommand.size() < 2)
				{
					throw std::string("No set to add");
				}
				ssCommands.str(tempCommand); //putting command in stringstream

				//Set<string> oneString;
				while (ssCommands >> command)
				{
					outputFile << " " << command;
					ineffectives[firstCommand].insert(command);
				}
				/*while (ssCommands >> command) //parsing back into command
				{
					//oneString.insert(command);
				}*/
				//effectives[firstCommand] = oneString;

				outputFile << endl;
			}
			else if (command == "Pokemon")
			{
				outputFile << endl;

				outputFile << command;
				outputFile << ": " << pokemon.toString();

			}
			else if (command == "Moves")
			{
				outputFile << endl;

				outputFile << command;
				outputFile << ": " << moves.toString();

			}
			else if (command == "Effectivities")
			{
				outputFile << endl;

				outputFile << command;
				outputFile << ": " << effectives.toString();
			}
			else if (command == "Ineffectivities")
			{
				outputFile << endl;
				outputFile << command;
				outputFile << ": " << ineffectives.toString();
			}
			else if (command == "Battle:")
			{
				outputFile << endl;

				outputFile << command << " ";
				string poke1;
				string poke2;
				string move1;
				string move2;
				inputFile >> poke1;
				outputFile << poke1 << " ";
				inputFile >> move1;
				outputFile << move1 << " ";
				inputFile >> poke2;
				outputFile << poke2 << " ";
				inputFile >> move2;
				outputFile << move2 << " ";
				outputFile << endl;
				outputFile << poke1 << " (" << move1 << ") vs " << poke2 << " (" << move2 << ")" << endl;
				outputFile << poke1 << " is a " << pokemon[poke1] << " type Pokemon." << endl;
				outputFile << poke2 << " is a " << pokemon[poke2] << " type Pokemon." << endl;
				outputFile << move1 << " is a " << moves[move1] << " type move." << endl;
				outputFile << move2 << " is a " << moves[move2] << " type move." << endl;
				int damageAToB = 0;
				damageAToB = effectives[moves[move1]].count(pokemon[poke2])
					- ineffectives[moves[move1]].count(pokemon[poke2]);
				cout << ineffectives[moves[move1]].count(pokemon[poke2]) << endl;

				int damageBToA = 0;
				damageBToA = effectives[moves[move2]].count(pokemon[poke1])
					- ineffectives[moves[move2]].count(pokemon[poke1]);
				cout << ineffectives[moves[move2]].count(pokemon[poke1]) << endl;

				outputFile << move1 << " is super effective against [" << effectives[moves[move1]].toString() << "] type Pokemon." << endl;
				outputFile << move1 << " is ineffective against [" << ineffectives[moves[move1]].toString() << "] type Pokemon." << endl;
				//Charmander's flamethrower is ineffective against Squirtle
				outputFile << poke1 << "'s " << move1 << " is ";
				if (damageAToB > 0)
				{
					outputFile << "super effective against " << poke2 << endl;
				}
				else if (damageAToB < 0)
				{
					outputFile << "ineffective against " << poke2 << endl;
				}
				else
				{
					outputFile << "effective against " << poke2 << endl;
				}
				
				outputFile << move2 << " is super effective against [" << effectives[moves[move2]].toString() << "] type Pokemon." << endl;
				outputFile << move2 << " is ineffective against [" << ineffectives[moves[move2]].toString() << "] type Pokemon." << endl;
				outputFile << poke2 << "'s " << move2 << " is ";
				if (damageBToA > 0)
				{
					outputFile << "super effective against " << poke1 << endl;
				}
				else if (damageBToA < 0)
				{
					outputFile << "ineffective against " << poke1 << endl;
				}
				else
				{
					outputFile << "effective against " << poke1 << endl;
				}
				// If (damageAToB - damageBToA) is 0, then there is a tie.
				// If (damageAToB - damageBToA) > 0, then pokemonA wins.
				// If (damageAToB - damageBToA) < 0, then pokemonB wins.
				

				if (damageAToB - damageBToA == 0)
				{
					outputFile << "The battle between " << poke1 << " and " << poke2 << " is a tie." << endl;
				}
				else if (damageAToB - damageBToA > 0)
				{
					outputFile << "In the battle between " << poke1 << " and " << poke2 << ", ";
					outputFile << poke1 << " wins!" << endl;
				}
				else
				{
					outputFile << "In the battle between " << poke1 << " and " << poke2 << ", ";
					outputFile << poke2 << " wins!" << endl;
				}
				//outputFile << 
				/*
				Battle: Charmander flamethrower Squirtle water_gun
  Charmander (flamethrower) vs Squirtle (water_gun)
  Charmander is a fire type Pokemon.
  Squirtle is a water type Pokemon.
  flamethrower is a fire type move.
  water_gun is a water type move.
  flamethrower is super effective against [bug,grass,ice,steel] type Pokemon.
  flamethrower is ineffective against [fire,rock,water] type Pokemon.
  Charmander's flamethrower is ineffective against Squirtle
  water_gun is super effective against [fire,ground,rock] type Pokemon.
  water_gun is ineffective against [grass,water] type Pokemon.
  Squirtle's water_gun is super effective against Charmander
  In the battle between Charmander and Squirtle, Squirtle wins!
				*/
			}
			else
			{
				outputFile << "Unknown Command" << endl;
			}

		}
		catch (const string& error)
		{
			outputFile << " " << error;
		}

	}


	//debug - windows -callstack
	//watch - enter in expression to watch regularly

	inputFile.close();
	outputFile.close();

	return 0;
}
/*
Your Set class inherits from the SetInterface class (SetInterface.h).
Implements SetInterface.
No duplicates in Set container.
Set toString() returns ordered elements. (BST!!)

Implement a HashMap class that inherits from the HashMapInterface class (HashMapInterface.h).
Use a string hash function for accessing data as explained above with a HASH_CONSTANT equal to 3.
Use quadratic probing for collision resolution.

Dynamically allocate the array for your hash table.
Use DEFAULT_MAP_HASH_TABLE_SIZE as the initial hash table size.

Each Pokémon is stored in a HashMap<string,string>.
Each Move is stored in a HashMap<string,string>.
Each Efficiency is stored in a HashMap<string,Set<string>>.
Each Inefficiency is stored in a HashMap<string,Set<string>>.

Report who wins each battle.
*/