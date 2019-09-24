#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK;
#endif


#include "AVL.h" //#includes are primarily in AVL.h

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

	AVL<string> strTree;
	AVL<int> intTree;


	string command;

	inputFile >> command;

	while (!inputFile.eof()) //Accepts commands to create linked lists of certain type
	{
		bool intAVL = true;
		if (command == "INT")
		{
			outputFile << command << " true" << endl;
		}
		else if (command == "STRING")
		{
			outputFile << command << " true" << endl;
			intAVL = false; //Lets program know to use else's that use list string functions
		}
		else
		{
			outputFile << "I can't construct anything.";
			std::cerr << "I can't construct anything without an initial command.";
			return 1;
		}


		while (!inputFile.eof()) //Accepts commands to use said lists
		{
			inputFile >> command;
			if (command == "add")
			{
				outputFile << command;

				if (intAVL)
				{
					//int tempInt;
					inputFile >> command;
					if (intTree.insert(std::stoi(command)))
					{
						outputFile << " " << command << " true" << endl;
					}
					else
					{
						outputFile << " " << command << " false" << endl;
					}
				}
				else
				{
					inputFile >> command;
					if (strTree.insert(command))
					{
						outputFile << " " << command << " true" << endl;
					}
					else
					{
						outputFile << " " << command << " false" << endl;
					}
				}
			}
			else if (command == "remove")
			{
				outputFile << command << " ";
				if (intAVL)
				{
					
					inputFile >> command;

					if (intTree.removeNode(stoi(command)))
					{
						outputFile << command << " true" << endl;
					}
					else
					{
						outputFile << command << " false" << endl;
					}
				}
				else
				{
					inputFile >> command;
					if (strTree.removeNode(command))
					{
						outputFile << command << " true" << endl;
					}
					else
					{
						outputFile << command << " false" << endl;
					}
				}
			}
			else if (command == "find")
			{
				outputFile << command;
				if (intAVL)
				{
					int tempInt;
					inputFile >> tempInt;
					if (intTree.find(tempInt))
					{
						outputFile << " " << tempInt << " found" << endl;
					}
					else
					{
						outputFile << " " << tempInt << " not found" << endl;
					}
				}
				else
				{
					inputFile >> command;
					if (strTree.find(command))
					{
						outputFile << " " << command << " found" << endl;
					}
					else
					{
						outputFile << " " << command << " not found" << endl;
					}
				}
			}
			else if (command == "size")
			{
				outputFile << command;
				if (intAVL)
				{
					outputFile << " " << intTree.getSize() << endl; //valgrind??
				}
				else
				{
					outputFile << " " << strTree.getSize() << endl; //
				}
			}
			else if (command == "clear")
			{
				outputFile << command << " true" << endl;
				if (intAVL)
				{
					intTree.clearTree();
				}
				else
				{
					strTree.clearTree();
				}
			}
			else if (command == "print")
			{
				outputFile << command << ":";
				if (intAVL)
				{
					outputFile << intTree.toString();
				}
				else
				{
					outputFile << strTree.toString();
				}
			}
			else if (command == "tree")
			{
				if (intAVL)
				{
					outputFile << command << " " << intTree.inOrderToString() << endl;
				}
				else
				{
					outputFile << command << " " << strTree.inOrderToString() << endl;
				}
			}
			else if (command == "INT")
			{
				break;
			}
			else if (command == "STRING")
			{
				break;
			}
			else
			{
				outputFile << command << " false, no command " << endl;
			}
		}
	}




	inputFile.close();
	outputFile.close();


	return 0;
}