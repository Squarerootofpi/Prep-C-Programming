
#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK;
#endif

#include <fstream>
#include <iostream>
#include <string>
#include "LinkedList.h"

using std::endl;
using std::string;

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


	LinkedList<string> sList; //creates a string list with name list
	LinkedList<int> iList; //Creates an integer list with name list
	int tempInt = -100; //creates the temp int (constructor is only called once in program)

	/*
	You might wonder why I instantiate both lists here, it's to illustrate that I could have constructed
	the code such that I created a list each time, using the if else's for the commands INT and STRING, but
	this would have resulted in it going out of scope every time I left that if statement, so I couldn't do
	this more logical format of the loop. I would be able to do that if I instantiated different functions 
	in the if's and else's, but I felt it would look a lot better to have it in this format, and let each 
	command do what it should with a smaller if-else.
	This is also what Prof. Roper said to do.
	*/

	string command;

	inputFile >> command;

	while (!inputFile.eof()) //Accepts commands to create linked lists
	{
		bool intList = true;
		if (command == "INT")
		{
			outputFile << command << " true" << endl;

		}
		else if (command == "STRING")
		{
			outputFile << command << " true" << endl;

			intList = false; //Lets program know to use else's that use list string functions
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
			if (command == "insertHead")
			{
				outputFile << command;
				
				if (intList) 
				{
					int tempInt;
					inputFile >> tempInt;
					if (iList.insertHead(tempInt))
					{
						outputFile << " " << tempInt << " true" << endl;
					}
					else
					{
						outputFile << " " << tempInt << " false" << endl;
					}
				}
				else
				{
					inputFile >> command;
					if (sList.insertHead(command))
					{
						outputFile << " " << command << " true" << endl;
					}
					else
					{
						outputFile << " " << command << " false" << endl;
					}
				}
			}
			else if (command == "insertTail")
			{
				outputFile << command;
				
				if (intList)
				{
					tempInt;
					inputFile >> tempInt;
					if (iList.insertTail(tempInt))
					{
						outputFile << " " << tempInt << " true" << endl;
					}
					else
					{
						outputFile << " " << tempInt << " false" << endl;
					}
				}
				else
				{
					inputFile >> command;
					if (sList.insertTail(command))
					{
						outputFile << " " << command << " true" << endl;
					}
					else
					{
						outputFile << " " << command << " false" << endl;
					}
				}
			}
			else if (command == "insertAfter")
			{
				outputFile << command;
				
				if (intList)
				{
					int matchThis;
					inputFile >> matchThis;
					outputFile << " " << matchThis;
					int insertThis;
					inputFile >> insertThis;
					if (iList.insertAfter(matchThis, insertThis))
					{

						outputFile << " " << insertThis << " true" << endl;
					}
					else
					{
						outputFile << " " << insertThis << " false" << endl;

					} 
				}
				else
				{
					inputFile >> command;
					std::string matchThis = command;
					outputFile << " " << matchThis;
					inputFile >> command;
					std::string insertThis = command;
					if (sList.insertAfter(matchThis, insertThis))
					{
						outputFile << " " << insertThis << " true" << endl;
					}
					else
					{
						outputFile << " " << insertThis << " false" << endl;

					}
				}
			}
			else if (command == "remove")
			{
				outputFile << command << " ";
				if (intList)
				{
					int iCommand;
					inputFile >> iCommand;

					if (iList.remove(iCommand))
					{
						outputFile << iCommand << " true" << endl;
					}
					else 
					{
						outputFile << iCommand << " false" << endl;
					}
				}
				else
				{
					inputFile >> command;
					if (sList.remove(command))
					{
						outputFile << command << " true" << endl;
					}
					else
					{
						outputFile << command << " false" << endl;
					}
				}
			}
			else if (command == "at")
			{
				outputFile << command;
				if (intList)
				{
					inputFile >> tempInt;
					try
					{
						outputFile << " " << tempInt << " " << iList.at(tempInt) << " true" << endl;
					}
					catch (...)
					{
						outputFile << " " << tempInt << " Invalid Index" << endl;
					}
				}
				else
				{
					inputFile >> tempInt;
					try
					{
						outputFile << " " << tempInt << " " << sList.at(tempInt) << " true" << endl;
					}
					catch (const std::out_of_range& oor)
					{
						outputFile << " " << tempInt << " Invalid Index" << endl;

					}
				}
			}
			else if (command == "size")
			{
				outputFile << command;
				if (intList)
				{
					outputFile << " " << iList.size() << endl;
				}
				else
				{
					outputFile << " " << sList.size() << endl;
				}
			}
			else if (command == "clear")
			{
				outputFile << command << " true" << endl;
				if (intList)
				{
					iList.clear();
				}
				else
				{
					sList.clear();
				}
			}
			else if (command == "printList")
			{
				outputFile << command;
				if (intList)
				{
					outputFile << iList.toString();
				}
				else
				{
					outputFile << sList.toString();
				}
			}
			else if (command == "iterateList")
			{
				if (intList)
				{
					outputFile << command << endl;
				}
				else
				{
					outputFile << command << endl;
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

			//inputFile >> command; //get next command for loop

		}
	}

	iList.~LinkedList();
	sList.~LinkedList();

	inputFile.close();
	outputFile.close();

	return 0;
}