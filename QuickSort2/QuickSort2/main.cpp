#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK;
#endif

#include "QS.h" //#includes are primarily in BST.h

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
	string thirdCommand;
	QS<int> theArray(0);

	while (inputFile >> command) //continue
	{
		if (command == "QuickSort")
		{
			outputFile << command << " ";
			inputFile >> command;
			outputFile << command << " OK";
			outputFile << endl;

			theArray.createArray(std::stoi(command));
			//Create array function

		}
		else if (command == "Capacity")
		{
			outputFile << command << " " << theArray.capacity() << endl;
		}
		else if (command == "Clear")
		{
			theArray.clear();
			outputFile << command << " OK" << endl;
		}
		else if (command == "AddToArray")
		{
			outputFile << command << "  ";

			getline(inputFile, command);

			stringstream ss(command);
			int toAdd = 0;
			ss >> toAdd;
			outputFile << toAdd;
			theArray.addElement(toAdd);

			while (ss >> toAdd)
			{
				outputFile << "," << toAdd;
				theArray.addElement(toAdd);
			}

			outputFile << " OK" << endl;
		}
		else if (command == "Size")
		{
			outputFile << command << " ";
			outputFile << theArray.size() << endl;

		}
		else if (command == "PrintArray")
		{
			outputFile << command << " ";
			outputFile << theArray;
			outputFile << endl;

		}
		else if (command == "MedianOfThree")
		{
			outputFile << command << " ";
			inputFile >> command;
			inputFile >> secondCommand;
			outputFile << command << "," << secondCommand << " = ";
			outputFile << theArray.medianOfThree(std::stoi(command), std::stoi(secondCommand));
			outputFile << endl;

		}
		else if (command == "Partition")
		{
			outputFile << command << " ";
			inputFile >> command; //First
			inputFile >> secondCommand; //Last
			inputFile >> thirdCommand; //Pivot
			outputFile << command << "," << secondCommand
				<< "," << thirdCommand << " = ";
			outputFile << theArray.partition(std::stoi(command),
				std::stoi(secondCommand), std::stoi(thirdCommand));
			outputFile << endl;
		}
		else if (command == "SortAll")
		{
			outputFile << command << " OK" << endl;
			theArray.sortAll();
		}
		else if (command == "Sort")
		{
			outputFile << command << " ";
			inputFile >> command; //First
			inputFile >> secondCommand; //Last
			theArray.sort(std::stoi(command), std::stoi(secondCommand));
			outputFile << command << "," << secondCommand << " OK" << endl;
		}
		else if (command == "Stats")
		{
			outputFile << command << " " << theArray.stats() << endl;
		}

	}





	inputFile.close();
	outputFile.close();


	return 0;
}